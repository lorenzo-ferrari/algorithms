#include "bits/stdc++.h"
using namespace std;
 
static constexpr int N{512};
static constexpr int INF{1 << 30};
 
struct Edge {
    int b;
    int w;
    int c;
    int oth;
};
 
static vector<Edge> adj[N];
static int dist[N];
static int from[N];
static int flow[N];
 
static void add_edge(int a, int b, int w, int c) {
    int idxa = adj[a].size();
    int idxb = adj[b].size();
    adj[a].push_back({b, w, c, idxb});
    adj[b].push_back({a, -w, 0, idxa});
}
 
static bool spfa(int s, int e) {
    fill(dist, dist+N, INF);
    dist[s] = 0;
    flow[s] = INF;
    flow[e] = 0;
    queue<array<int, 2>> Q;
    Q.push({s, dist[s]});
    while (!Q.empty()) {
        auto [v, d] = Q.front();
        Q.pop();
        if (dist[v] < d) {
            continue;
        }
        for (auto [u, w, c, oth] : adj[v]) {
            if (!c) continue;
            int new_dist = d + w;
            int new_flow = min(flow[v], c);
            if (dist[u] > new_dist) {
                dist[u] = new_dist;
                flow[u] = new_flow;
                from[u] = oth;
                Q.push({u, dist[u]});
            }
        }
    }
    return flow[e] != 0;
}
 
static int MinCostMaxFlow(int s, int e, int k) {
    int cost = 0;
    while (k && spfa(s, e)) {
        int new_flow = min(k, flow[e]);
        cost += dist[e] * new_flow;
        k -= new_flow;
        int cur = e;
        while (cur != s) {
            int idx_ba = from[cur];
            int prv = adj[cur][idx_ba].b;
            int idx_ab = adj[cur][idx_ba].oth;
            adj[prv][idx_ab].c -= new_flow;
            adj[cur][idx_ba].c += new_flow;
            cur = prv;
        }
    }
    return k ? -1 : cost;
}
 
int main() {
    int n; cin >> n;
    int m; cin >> m;
    int k; cin >> k;
    for (int i = 0, a, b, c, w; i < m; ++i) {
        cin >> a >> b >> c >> w;
        add_edge(a, b, w, c);
    }
 
    int ans = MinCostMaxFlow(1, n, k);
    cout << ans << "\n";
}
