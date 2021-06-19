class st {
	st * l = nullptr;
	st * r = nullptr;
	int sum = 0;
	int a, b;

public:
	st(int a, int b) :
	a(a), b(b) {}

	~st() {
		if (l) delete l;
		if (r) delete r;
	}

	friend void update(st * &N, int pos) { // upd = +1
		N->sum++;
		if (N->a + 1 == N->b) return;
		if (2 * pos < (N->a + N->b)) {
			if (!N->l) N->l = new st(N->a, (N->a + N->b) / 2);
			update(N->l, pos);
		} else {
			if (!N->r) N->r = new st((N->a + N->b) / 2, N->b);
			update(N->r, pos);
		}
	}

	friend int query(st * &N, int L, int R) {
		if (!N) return 0;
		if (N->b <= L || R <= N->a) return 0;
		if (L <= N->a && N->b <= R) return N->sum;
		return query(N->l, L, R) + query(N->r, L, R);
	}
};
