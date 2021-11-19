// Usage:
// vector<int> a {1, 2, 3, 4, 5};
// auto t = segment<int>(a, [](int a, int b){return a+b;});
// t.update(3, -3);
// cout << t.query(0, 5) << "\n";

#include <functional>
#include <vector>
using namespace std;

template<typename T>
struct segment {
	int n;
	vector<T> tree;
	function<T(T, T)> choose;

	segment(vector<T> a, function<T(T,T)> f) : choose(f), n(a.size()) {
		tree.resize(2 * n, T(0));
		for (int i = 0; i < n; ++i)
			tree[i + n] = a[i];
		for (int i = n - 1; i > 0; --i)
			tree[i] = choose(tree[i << 1], tree[i << 1 | 1]);
	}
	void update(int p, T val) {
		for (tree[p += n] = val; p > 1; p >>= 1)
			tree[p >> 1] = choose(tree[p], tree[p ^ 1]);
	}
	T query(int l, int r) { // [l, r)
		T ans(0);
		for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
			if (l & 1) ans = choose(ans, tree[l++]);
			if (r & 1) ans = choose(ans, tree[--r]);
		}
		return ans;
	}
};
