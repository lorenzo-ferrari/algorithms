#include <algorithm>
#include <functional>
#include <iostream>
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


std::vector<bool> twoSat(int n, int m, std::vector<int> negx,
std::vector<int> x, std::vector<int> negy, std::vector<int> y) {
    std::vector<std::vector<int>> g(2 * m);
    for (int i = 0, tx, ty; i < n; ++i) {
        tx = (x[i] << 1) ^ negx[i];
        ty = (y[i] << 1)  ^ negy[i];
        g[tx^1].push_back(ty);
        g[ty^1].push_back(tx);
    }

    components_t components(2 * m, g);
    
    int cnt = components.size();
    auto cgraph = components.cgraph();
    auto lists = components.lists();

    for (int i = 0; i < 2 * m; i += 2) {
        if (components[i] == components[i ^ 1]) {
            std::cout << "IMPOSSIBLE" << "\n";
            exit(0);
        }
    }

    std::vector<bool> vis(cnt);
    std::vector<int> o;

    std::function<void(int)> toposort = [&](int v) {
        vis[v] = true;
        for (int& u : cgraph[v])
            if (!vis[u])
                toposort(u);
        o.push_back(v);
    };

    for (int i = 0; i < cnt; ++i)
        if (!vis[i])
            toposort(i);
    vis.assign(m, false);
    std::vector<bool> ans(m);
    for (int i : o) {
        for (int j : lists[i]) {
            if (!vis[j >> 1]) {
                ans[j >> 1] = (j & 1) ^ 1;
                vis[j >> 1] = true;
            }
        }
    }

    return ans;
}
