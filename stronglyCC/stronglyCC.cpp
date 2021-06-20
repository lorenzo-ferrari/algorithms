#include <algorithm>
#include <vector>


class components_t {
    int n;
    std::vector<std::vector<int>> g;
    std::vector<std::vector<int>> r;
    int C = 0;
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
    components_t (int n, std::vector<std::vector<int>>& g) : n(n), g(g) {
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
                dfs2(i);
                C++;
            }
        }
    }

    int size() {
        return C;
    }

    std::vector<std::vector<int>> cgraph() {
        std::vector<std::vector<int>> cg(C);
        for (int i = 0; i < n; ++i)
            for (int j : g[i])
                cg[c[i]].push_back(c[j]);
        return cg;
    }

    std::vector<std::vector<int>> lists() {
        std::vector<std::vector<int>> ans(C);
        for (int i = 0; i < n; ++i)
            ans[c[i]].push_back(i);
        return ans;
    }

    int operator [](int i) { return c[i]; }
};

