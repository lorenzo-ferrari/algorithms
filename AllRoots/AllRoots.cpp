#include <vector>
using namespace std;

class AllRoots {
  // determine for each node the sum of the distances from the node to all other
  // nodes
  using LL = long long;
  int n;
  vector<LL> ans;
  vector<LL> sum, cnt;
  vector<vector<int>> adj;

  void dfs(int v, int p) {
    for (int u : adj[v]) {
      if (u == p) continue;
      dfs(u, v);
      sum[v] += sum[u] + cnt[u];
      cnt[v] += cnt[u];
    }
  }

  void moveRoot(int root, int child) {
    LL new_root_sum = sum[root] - sum[child] - cnt[child];
    LL new_child_sum = sum[root] - cnt[child] + (n - cnt[child]);
    LL new_root_cnt = n - cnt[child];
    LL new_child_cnt = n;
    sum[root] = new_root_sum;
    cnt[root] = new_root_cnt;
    sum[child] = new_child_sum;
    cnt[child] = new_child_cnt;
  }

  void getAllRoots(int v, int p) {
    ans[v] = sum[v];
    for (int u : adj[v]) {
      if (u == p) continue;
      moveRoot(v, u);
      getAllRoots(u, v);
      moveRoot(u, v);
    }
  }

public:
  explicit AllRoots(int _n, const vector<vector<int>>& _adj) : n(_n), adj(_adj) {
    ans.assign(n, -1);
    sum.assign(n, 0);
    cnt.assign(n, 1);

    dfs(0, -1);
    getAllRoots(0, -1);
  }
  LL getans(int i) { return ans[i]; }
};
