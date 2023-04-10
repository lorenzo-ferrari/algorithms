/*
 *  spfa with Tarjan's trick (subtree disassembling):
 *
 *  core idea:
 *      - when updating a node, detach its subtree in the shortest-path tree.
 *
 *  implementation:
 *      - store the tree as 3 pointer for each node:
 *          - left sibling (points to parent if I'm the first sibling)
 *          - right sibling
 *          - first child
 *  
 *  note: it is also possible to detect and find negative cycles
 *      (not currently implemented)
 */

#include <array>
#include <stack>
#include <queue>
#include <vector>
using namespace std;
using LL = long long;
 
vector<LL> spfa(int n, int s, const vector<vector<array<LL, 2>>>& adj) {
    static constexpr LL INF = 1e18;
 
    struct nd {
        LL d;   // distance
        int l;  // left sibling
        int r;  // right sibling
        int f;  // first child
        bool act;
 
        nd() : d(INF), l(-1), r(-1), f(-1), act(false) {}
        nd(LL _d, int _l, int _r, int _f, bool _act)
            : d(_d), l(_l), r(_r), f(_f), act(_act) {}
    };
 
    vector<nd> nodes(n);
 
    stack<int> st;
    auto reset_subtree = [&](int i) -> void {
        if (nodes[i].l == -1) return;   // i has never been touched
        if (nodes[nodes[i].l].f == i) { // i is first child
            nodes[nodes[i].l].f = nodes[i].r;
            if (nodes[i].r != -1) {
                nodes[nodes[i].r].l = nodes[i].l;
            }
        } else {                        // i has a left sibling
            nodes[nodes[i].l].r = nodes[i].r;
            if (nodes[i].r != -1) {
                nodes[nodes[i].r].l = nodes[i].l;
            }
        }
 
        nodes[i].r = -1;
        st.push(i);
        while (!st.empty()) {
            int v = st.top();
            st.pop();
 
            if (nodes[v].f != -1) st.push(nodes[v].f);
            if (nodes[v].r != -1) st.push(nodes[v].r);
 
            nodes[v].l = nodes[v].r = nodes[v].f = -1;
            nodes[v].act = false;
        }
    };
 
    queue<int> Q;
    Q.push(s);
    nodes[s] = nd(0, -1, -1, -1, true);
 
    while (!Q.empty()) {
        int v = Q.front();
        Q.pop();
 
        if (!nodes[v].act) {
            continue;
        }
        nodes[v].act = false;
 
        for (auto [u, w] : adj[v]) {
            if (nodes[u].d > nodes[v].d + w) {
                reset_subtree(u);
 
                nodes[u].d = nodes[v].d + w;
                nodes[u].l = v;
                nodes[u].r = nodes[v].f;
                nodes[u].f = -1;
                if (nodes[u].r != -1) {
                    nodes[nodes[u].r].l = u;
                }
                nodes[v].f = u;
 
                Q.push(u);
                nodes[u].act = true;
            }
        }
    }
 
    vector<LL> ans(n);
    for (int i = 0; i < n; ++i) {
        ans[i] = nodes[i].d;
    }
 
    return ans;
}
