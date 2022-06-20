/*
Implementation of an infinite array v, initially v[i] = 0 for each i.
 * update(i, val), set v[i] = val
 * query(l, r), return v[l] + ... + v[r]

Time complexity: O(n log n) with a high constant
Space complexity: O(n), which is why it can be preferable in place of a sparse segment tree

*/

#include <random>
#include <iostream>
using namespace std;
using LL = long long;

mt19937 rng{42};

class ImplicitTreap {
private:
  struct treap {
    int x, y;
    int a, b; // range [a, b]
    LL val;
    LL sum;
    treap* l = nullptr;
    treap* r = nullptr;
    treap() {}
    treap(int x, LL val) : x(x), y(rng()), a(x), b(x), val(val), sum(val) {}
    ~treap() {
      if (l) delete l;
      if (r) delete r;
    }
  };
  inline void clean(treap* const t) {
    if (t) {
      t->l = t->r = nullptr;
      delete t;
    }
  }

  inline LL sum(const treap* const t) {
    return t ? t->sum : 0LL;
  }

  inline void upd(treap* const t) {
    // assume t->l and t->r are already updated
    if (t) {
      t->sum = t->val + sum(t->l) + sum(t->r);
      t->a = t->l ? t->l->a : t->x;
      t->b = t->r ? t->r->b : t->x;
    }
  }

  void split(treap* const t, const int x, treap*& l, treap*& r) {
    // split t in [-inf, x], [x+1, +inf]
    if (!t) {
      l = r = nullptr;
    } else if (t->x <= x) {
      split(t->r, x, t->r, r); l = t;
    } else {
      split(t->l, x, l, t->l); r = t;
    }
    upd(l);
    upd(r);
  }

  void merge(treap*& t, treap* l, treap* r) {
    if (!l || !r) {
      t = l ? l : r;
    } else if (l->y > r->y) {
      merge(l->r, l->r, r); t = l;
    } else {
      merge(r->l, l, r->l); t = r;
    }
    upd(t);
  }

  void insert(treap*& t, treap* const nw) {
    // assume nw->x is not present in t
    if (!t) {
      t = nw;
    } else if (nw->y > t->y) {
      split(t, nw->x, nw->l, nw->r);
      t = nw;
    } else {
      insert(nw->x <= t->x ? t->l : t->r, nw);
    }
    upd(t);
  }

  void erase(treap*& t, const int x) {
    if (!t) return;
    if (t->x == x) {
      treap* tmp = t;
      merge(t, t->l, t->r);
      clean(tmp);
    } else {
      erase(x <= t->x ? t->l : t->r, x);
    }
    upd(t);
  }

  LL sum(treap* const t, int l, int r) {
    upd(t);
    if (!t || r < t->a || t->b < l) return 0LL;
    if (l <= t->a && t->b <= r) return t->sum;
    return (l <= t->x && t->x <= r ? t->val : 0LL) + sum(t->l, l, r) + sum(t->r, l, r);
  }

  // actual treap
  treap* t = nullptr;
public:
  ImplicitTreap() {}
  ~ImplicitTreap() {
    delete t;
  }
  void update(int x, LL val) {
    // set v[x] = val
    erase(t, x);
    insert(t, new treap(x, val));
  }
  LL query(int l, int r) {
    // return sum [l, r]
    return sum(t, l, r);
  }
};
