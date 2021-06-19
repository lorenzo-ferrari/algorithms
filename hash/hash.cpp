/*
 *
 *	Rabin-Karp rolling hash
 *
 *	To be implemented:
 *		string comparison (< >):
 *			binary search until they match, then check last char
 *
 */

#include <string>
#include <vector>

class Hash {
private:
	long long N, P, MOD;
	std::string S;
	std::vector<long long> pw;
	std::vector<long long> prf;

public:
	Hash(int n, int p, long long mod, std::string s) : N(n), S(s), P(p), MOD(mod) {
		pw.resize(N+1);
		prf.resize(N+1);

		pw[0] = 1;
		for (int i = 0; i < N; i++) {
			pw[i + 1] = pw[i] * P % MOD;
			prf[i + 1] = (prf[i] + (S[i] - 'a') * pw[i] % MOD) % MOD;
		}
	}

	bool cmpr(int i, int j, int len) { // [i, i+len)
		if (i > j) std::swap(i, j);
		long long h1 = ((prf[i + len] - prf[i] + MOD) % MOD) * pw[j - i] % MOD;
		long long h2 = ((prf[j + len] - prf[j] + MOD) % MOD);

		return h1 == h2;
	}
};
