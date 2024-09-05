/// Verification:
/// https://judge.yosupo.jp/submission/233109
/// https://codeforces.com/contest/932/submission/279864130
/* compressed Li Chao Tree for minimum.
 * LCT_ZIP($n$) creates a tree on $0, \ldots, n-1$
 * LCT_ZIP({$x_1, \ldots, x_n$}) creates a tree on $x_1, \ldots, x_n$
 * add_fn(f): upd the whole tree with f in $\mathcal{O}(\log{n})$
 * upd(f, l, r): upd the interval $[l, r)$ with f in $\mathcal{O}({{\log}^2}{n})$
 * get(x): return min{f(x) : f in tree} in $\mathcal{O}(\log{n})$*/
struct fn {
  LL m, q;
  explicit fn(LL _m, LL _q) : m(_m), q(_q) {}
  LL eval(LL x) const { return m*x + q; }
};
struct LCT_ZIP {
  int n;
  vector<fn> t;
  vector<LL> qs;
  vector<fn> history;
  explicit LCT_ZIP(vector<LL> _qs) : qs(_qs) {
    sort(begin(qs), end(qs));
    qs.erase(unique(begin(qs), end(qs)), end(qs));
    while (qs.size() & (qs.size() - 1))
      qs.push_back(qs.back() + 1);
    n = qs.size();
    t.assign(2 * n, fn(0, 2e18));
  }
  explicit LCT_ZIP(int _n) {
    vector<LL> q(_n);
    iota(begin(q), end(q), 0);
    *this = LCT_ZIP(q);
  }
  void add_fn(fn f, int i, int a, int b) {
    int m = (a + b) / 2;
    bool lef = f.eval(qs[a]) < t[i].eval(qs[a]);
    bool mid = f.eval(qs[m]) < t[i].eval(qs[m]);
    if (mid) {
      swap(t[i], f);
    }
    if (b - a == 1) return;
    if (lef != mid)
      add_fn(f, 2*i  , a, m);
    else
      add_fn(f, 2*i+1, m, b);
  }
  void upd(fn f, int i, int a, int b, int l, int r) {
    if (b <= l || r <= a) return;
    if (l <= a && b <= r) add_fn(f, i, a, b);
    else {
      upd(f, 2*i  , a, (a + b)/2, l, r);
      upd(f, 2*i+1, (a + b)/2, b, l, r);
    }
  }
  LL get(int x, int i = 1, int a = 0, int b = -1) {
    if (b == -1) b = n;
    int m = (a + b) / 2;
    if (b - a == 1) return t[i].eval(x);
    if (x < qs[m]) {
      return min(t[i].eval(x), get(x, 2*i  , a, m));
    } else {
      return min(t[i].eval(x), get(x, 2*i+1, m, b));
    }
  }
  void add_fn(fn f) {
    history.push_back(f);
    if (!qs.empty()) add_fn(f, 1, 0, n);
  }
  void range_add_fn(fn f, int l, int r) {
    upd(f, 1, 0, n, l, r);
  }
};
