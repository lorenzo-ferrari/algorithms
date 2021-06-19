#include <vector>

struct centroidDecomposition {
	int root;
	std::vector<std::vector<int>> g;
	std::vector<int> dad;
	std::vector<int> sub;
	std::vector<bool> cen;

	centroidDecomposition(std::vector<std::vector<int>> &g) : g(g) {
		int n = g.size();
		dad.resize(n);
		sub.resize(n);
		cen.resize(n);
		root = decompose(0, -1); // 0-based
	}

	int sz(int v, int p) { // dfs, size of subtree
		sub[v] = 1;
		for (int u : g[v])
			if (u ^ p && !cen[u])
				sub[v] += sz(u, v);
		return sub[v];
	}

	int centroid(int v, int p, int sz) { // centroid of subtree
		for (int u : g[v])
			if (u ^ p && !cen[u] && sub[u] > sz / 2)
				return centroid(u, v, sz);
		return v;
	}

	int decompose(int v, int p) {
		int size = sz(v, p);
		int c = centroid(v, p, size);
		cen[c] = true;
		if (p == -1) {
			root = c;
			p = c;
		}
		dad[c] = p;
		for (int u : g[c])
			if (!cen[u])
				decompose(u, c); // appendi u, e' nel subtree di centroid

		return c;
	}

	int operator [](int i) { return dad[i]; }
};
