#include <vector>
using namespace std;

// min range query, point update
class segment {
	struct node {
		int mn;
		int id;
		node(int a = 1e9, int b = -1) : mn(a), id(b) {}
	};
	node choose(node &a, node &b) {
		if (a.mn < b.mn || (a.mn == b.mn && a.id < b.id))
			return a;
		return b;
	}

	int n;
	vector<node> st;

	public:
		// build the segment
		segment(vector<int> a) {
			n = a.size();
			st.resize(2 * n);
			for (int i = 0; i < n; i++) {
				st[i + n] = node(a[i], i);
			}
			for (int i = n - 1; i > 0; i--) {
				st[i] = choose(st[i << 1], st[i << 1 | 1]);
			}
		}

		// set v[p] = val
		void update(int p, int val) {
			for (st[p += n] = val; p > 1; p >>= 1) {
				st[p >> 1] = choose(st[p], st[p ^ 1]);
			}
		}

		// return idx min element [l, r)
		int query(int l, int r) {
			node ans(1e9, -1);
			for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
				if (l & 1) ans = choose(ans, st[l++]);
				if (r & 1) ans = choose(ans, st[--r]);
			}

			return ans.id;
		}
};
