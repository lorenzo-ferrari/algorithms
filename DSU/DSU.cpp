#include <vector>

class dsu {
	std::vector<int> p;
	std::vector<int> s;
public:
	dsu(int n) : p(n), s(n, 1) {
		while (n--)
			p[n] = n;
	}

	int find_set(int v) {
		return p[v] == v ? v : p[v] = find_set(p[v]);
	}

	bool union_set(int a, int b) {
		a = find_set(a);
		b = find_set(b);
		if (a == b)	return false;
		if (s[a] < s[b]) std::swap(a, b);
		p[b] = a;
		return true;
	}		
};
