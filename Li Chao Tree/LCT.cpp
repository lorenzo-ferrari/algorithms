#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;
using LL = long long;

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
    qs.resize(unique(begin(qs), end(qs)) - begin(qs));
    n = qs.size();
    t.assign(4 * n, fn(0, 1e15));
  }
  explicit LCT_ZIP(int _n) {
    vector<LL> q(_n);
    iota(begin(q), end(q), 0);
    *this = LCT_ZIP(q);
  }
  void add_fn(fn f) {
    history.push_back(f);
    if (!qs.empty()) add_fn(f, 1, 0, n);
  }
  void add_fn(fn f, int i, int l, int r) {
    int m = (l + r) / 2;
    bool lf = f.eval(qs[l]) < t[i].eval(qs[l]);
    bool md = f.eval(qs[m]) < t[i].eval(qs[m]);
    if (md) {
      swap(t[i], f);
    }
    if (r - l <= 1) return;
    if (lf != md) {
      add_fn(f, 2*i, l, m);
    } else {
      add_fn(f, 2*i+1, m, r);
    }
  }
  LL get(int x, int i = 1, int l = 0, int r = -1) {
    if (r == -1) r = n;
    int m = (l + r) / 2;
    if (r - l <= 1) return t[i].eval(x);
    if (x < qs[m]) {
      return min(t[i].eval(x), get(x, 2*i, l, m));
    } else {
      return min(t[i].eval(x), get(x, 2*i+1, m, r));
    }
  }
};
