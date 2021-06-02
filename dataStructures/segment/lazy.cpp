#include <bits/stdc++.h>

const long long N = (1 << 20);

class lazySegment {
	struct node {
		long long sum = 0;
		long long lazy = 0;
		node (long long _sum = 0) : sum(_sum) {}
	};

	node join(node &a, node &b) {
		return node(a.sum + b.sum);
	}

	// actual segment tree
	node st[2 * N];

	public:
		lazySegment () {}
		lazySegment (std::vector<long long> a) {
			for (int i = 0; i < a.size(); ++i)
				st[i + N] = node(a[i]);
			for (int i = N - 1; i > 0; --i)
				st[i] = join(st[i << 1], st[i << 1 | 1]);
		}

		void prop(int i, int a, int b) {
			if (st[i].lazy) {
				st[i].sum += (b - a) * st[i].lazy;
				if (i < N) {
						st[i << 1    ].lazy += st[i].lazy;
						st[i << 1 | 1].lazy += st[i].lazy;
				}
				st[i].lazy = 0;
			}
		}

		void _add(int i, int l, int r, int a, int b, long long val) {
			prop(i, a, b);
			if (r <= a || b <= l) return;
			if (l <= a && b <= r) {
				st[i].lazy += val;
				prop(i, a, b);
			}
			else {
				_add(i << 1    , l, r, a, (a + b) >> 1, val);
				_add(i << 1 | 1, l, r, (a + b) >> 1, b, val);
				st[i] = join(st[i << 1], st[i << 1 | 1]);
			}
		}

		long long _sum(int i, int l, int r, int a, int b) {
			prop(i, a, b);
			if (r <= a || b <= l) return 0;
			if (l <= a && b <= r) return st[i].sum;
			return _sum(i << 1    , l, r, a, (a + b) >> 1) +
						 _sum(i << 1 | 1, l, r, (a + b) >> 1, b);
		}

		long long get_sum(int l, int r) { return _sum(1, l, r, 0, N); }
		void add(int l, int r, long long x) { _add(1, l, r, 0, N, x); }
};
