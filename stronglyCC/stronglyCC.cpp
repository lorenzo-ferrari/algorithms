#include <algorithm>
#include <vector>

class cc {
    int n;
    std::vector<std::vector<int>> g;
    std::vector<std::vector<int>> r;
    std::vector<bool> vis;
    std::vector<int> c;
    std::vector<int> o;

    void dfs1(int v) {
        vis[v] = true;
        for (int u : g[v])
            if (!vis[u])
                dfs1(u);
        o.push_back(v);
    }

    void dfs2(int v) {
        vis[v] = true;
        c[v] = C;
        for (int u : r[v])
            if (!vis[u])
                dfs2(u);
    }

public:
    int C = 0;
    cc (int n, std::vector<std::vector<int>>& g) : n(n), g(g) {
        r.resize(n);
        for (int i = 0; i < n; ++i)
            for (int u : g[i])
                r[u].push_back(i);

        vis.assign(n, false);
        for (int i = 0; i < n; ++i)
            if (!vis[i])
                dfs1(i);
        c.resize(n);
        vis.assign(n, false);
        reverse(o.begin(), o.end());
        for (int i : o) {
            if (!vis[i]) {
                C++;
                dfs2(i);
            }
        }
    }

    int operator [](int i) { return c[i]; }
};
