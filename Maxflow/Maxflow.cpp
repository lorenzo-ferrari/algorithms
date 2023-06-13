#include <stack>
#include <vector>
using namespace std;

const int INF = 1e9;
int dfs(int n, int s, int e, vector<vector<int>> &g, vector<vector<int>> &c, vector<int> &par) {
	par.assign(n, -1);
	stack<pair<int, int>> st;
	st.push({s, INF});
	while (!st.empty()) {
		int v = st.top().first;
		int flow = st.top().second;
        st.pop();

		for (int u : g[v])
			if (par[u] == -1 && c[v][u]) {
				int new_flow = min(flow, c[v][u]);
				par[u] = v;
				if (u == e)
					return new_flow;
				st.push({u, new_flow});
			}
	}

	return 0;
}

int maxflow(int n, int s, int e, vector<vector<int>> &g, vector<vector<int>> &c) {
	int flow = 0;
	int new_flow;
	vector<int> par;
	while (new_flow = dfs(n, s, e, g, c, par)) {
		flow += new_flow;
		int cur = e;
		while (cur != s) {
			int prv = par[cur];
			c[prv][cur] -= new_flow;
			c[cur][prv] += new_flow;
			cur = prv;
		}
	}

	return flow;
}
