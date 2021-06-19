#include <vector>

class dsu {
	std::vector<int> p;
public:
	dsu(int n) {
		p.assign(n, 0);
		while (n--)
			p[n] = n;
	}

	int find_set(int v) {
		return p[v] == v ? v : p[v] = find_set(p[v]);
	}

	bool union_set(int a, int b) {
		a = find_set(a);
		b = find_set(b);
		p[b] = a;
		return a ^ b;
	}		
};
