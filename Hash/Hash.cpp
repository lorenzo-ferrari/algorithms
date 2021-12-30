/*
 *	Rabin-Karp rolling hash
 */

#include <string>
#include <vector>

class Hash {
 private:
  long long N;
  long long P;
  long long MOD;
  std::string S;
  std::vector<long long> pw;
  std::vector<long long> prf;

 public:
  Hash(int n, int p, long long mod, std::string s)
      : N(n), P(p), MOD(mod), S(s) {
    pw.resize(N + 1);
    prf.resize(N + 1);

    pw[0] = 1;
    for (int i = 0; i < N; i++) {
      pw[i + 1] = pw[i] * P % MOD;
      prf[i + 1] = (prf[i] + (S[i] - 'a') * pw[i] % MOD) % MOD;
    }
  }

  bool same(int i, int j, int len) {  // [i, i+len)
    if (i > j) std::swap(i, j);
    long long h1 = ((prf[i + len] - prf[i] + MOD) % MOD) * pw[j - i] % MOD;
    long long h2 = ((prf[j + len] - prf[j] + MOD) % MOD);
    return h1 == h2;
  }

  bool less(int i, int len_i, int j, int len_j) {
    if (len_i == len_j && same(i, j, len_i)) {
      return false;
    }
    if (S[i] != S[j]) {  // average case
      return S[i] < S[j];
    }
    int l = 0;
    int r = std::min(len_i, len_j) + 1;
    while (r - l > 1) {
      int mid = (l + r) / 2;
      if (same(i, j, mid))
        l = mid;
      else
        r = mid;
    }
    return S[i + l] < S[j + l];
  }

  bool greater(int i, int len_i, int j, int len_j) {
    if (len_i == len_j && same(i, j, len_i)) {
      return false;
    }
    return !less(i, len_i, j, len_j);
  }
};
