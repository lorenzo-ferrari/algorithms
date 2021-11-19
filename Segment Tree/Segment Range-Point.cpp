// Usage:
// vector<int> a {1, 2, 3, 4, 5};
// auto t = segment<int>(a, [](int a, int b){return a+b;});
// t.update(0, 4, 2);
// cout << t.query(3) << "\n";

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
  }
  void update(int l, int r, T val) { // [l, r)
		for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
			if (l & 1) { tree[l] = choose(tree[l], val); l++; }
			if (r & 1) { --r; tree[r] = choose(tree[r], val); }
		}
	}
	T query(int p) {
    T ans(0);
		for (p += n; p > 0; p >>= 1)
			ans = choose(ans, tree[p]);
    return ans;
	}
};
