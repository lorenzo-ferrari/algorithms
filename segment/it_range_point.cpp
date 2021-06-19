#include <vector>

// point query, range sum update
class segment {
	int n;
	std::vector<int> st;

public:
	// initialize the tree
	segment(std::vector<int> a) {
		n = a.size();
		st.resize(2 * n);
		for (int i = 0; i < n; i++) {
			st[i + n] = a[i];
		}
	}

	// add val to elements in interval [l, r)
	void update(int l, int r, int val) {
		for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
			if (l & 1) st[l++] += val;
			if (r & 1) st[--r] += val;
		}
	}

	// return v[p]
	int query(int p) {
		int ans = 0;
		for (p += n; p > 0; p >>= 1) {
			ans += st[p];
		}
			return ans;
	}
};
