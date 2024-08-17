using edge_t = pair<int, int>;
// Returns (articulations points, bridges) ($\mathcal{O}(N + M)$)
pair<vector<int>, vector<edge_t>>
artpoints_bridges(vector<vector<int>>& adj) {
	int n = adj.size();
	pair<vector<int>, vector<edge_t>> ans;
	vector<int> par(n), ord(n), low(n);
	int dfs_cnt, dfs_src, src_children;
	auto dfs = [&](auto&& self, int v) -> void {
		bool is_artpoint = false;
		ord[v] = low[v] = ++dfs_cnt;
		for (int u : adj[v]) {
			if (!ord[u]) {
				par[u] = v;
				src_children += (v == dfs_src);
				self(self, u);
				if (low[u] >= ord[v] && v != dfs_src)
					is_artpoint = true;
				if (low[u] > ord[v])
					ans.second.push_back({v, u});
				low[v] = min(low[v], low[u]);
			} else if (par[v] != u)
				low[v] = min(low[v], ord[u]);
		}
		if (is_artpoint)
			ans.first.push_back(v);
	};
	for (dfs_src = 0; dfs_src < n; ++dfs_src) {
		if (!ord[dfs_src]) {
			dfs_cnt = src_children = 0;
			par[dfs_src] = dfs_src;
			dfs(dfs, dfs_src);
			if (src_children > 1) {
				ans.first.push_back(dfs_src);
			}
		}
	}
	return ans;	// works also on disconnected graphs
}
