#include <bits/stdc++.h>
using namespace std;

struct Segment {
  int n;
  vector<int64_t> t;
  Segment() {}
  Segment(vector<int> v) : n(v.size()) {
    t.resize(2 * n);
    for (int i = 0; i < n; ++i) t[i + n] = v[i];
    for (int i = n-1; i > 0; --i) t[i] = max(t[2*i], t[2*i+1]);
  }
  void update(int p, int v) {
    for (t[p += n] = v; p > 1; p >>= 1) {
      t[p >> 1] = max(t[p], t[p ^ 1]);
    }
  }
  int64_t query(int l, int r) {
    int64_t ans = 0;
    for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
      if (l & 1) ans = max(ans, t[l++]);
      if (r & 1) ans = max(ans, t[--r]);
    }
    return ans;
  }
};

struct Hld {
  int n;
  int cur_pos = 0;
  vector<int> par;
  vector<int> pos;
  vector<int> size;
  vector<int> head;
  vector<int> depth;
  vector<vector<int>> adj;
  Segment seg;

  Hld(vector<vector<int>> adj, vector<int> v) : n(adj.size()), adj(adj) {
    par.assign(n, -1);
    pos.assign(n, -1);
    size.assign(n, 0);
    head.assign(n, -1);
    depth.assign(n, -1);

    dfs(0);
    decompose(0, 0);
    seg = Segment(vector<int>(n, 0));
    for (int i = 0; i < n; ++i) seg.update(pos[i], v[i]);
  }
  int dfs(int v) {
    for (int& u : adj[v]) {
      if (u == par[v]) continue;
      par[u] = v;
      depth[u] = depth[v] + 1;
      size[v] += dfs(u);
    }
    sort(adj[v].begin(), adj[v].end(), [&](int i, int j){return size[i] > size[j];});
    return size[v];
  }
  void decompose(int v, int h) {
    head[v] = h;
    pos[v] = cur_pos++;
    bool heavy_found = false;
    for (int u : adj[v]) {
      if (u == par[v]) continue;
      if (!heavy_found) {
        heavy_found = true;
        decompose(u, h);
      } else {
        decompose(u, u);
      }
    }
  }
  int64_t query(int a, int b) {
    int64_t ans = 0;
    while (head[a] != head[b]) {
      if (depth[head[a]] > depth[head[b]]) swap(a, b);
      ans = max(ans, seg.query(pos[head[b]], pos[b]+1));
      b = par[head[b]];
    }
    if (depth[a] > depth[b]) swap(a, b);
    ans = max(ans, seg.query(pos[a], pos[b]+1));
    return ans;
  }
  void update(int p, int v) {
    seg.update(pos[p], v);
  }
};
