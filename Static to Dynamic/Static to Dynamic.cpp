#include <vector>
#include <algorithm>
using namespace std;

struct StaticToDynamic {
  // v is partitioned in O(log n) ordered subarrays
  // each length is a 1 in the binary representation of n
  vector<int> v;

  // O(log n) amortized
  void insert(int x) {
    v.push_back(x);
    for (size_t i = 1; !(i & v.size()); i *= 2) {
      inplace_merge(v.end() - 2 * i, v.end() - i, v.end());
    }
  }

  // count the elements in [a, b], O(log^2 n)
  int count(int a, int b) {
    int ans = 0;
    for (size_t n = v.size(); n; n &= n - 1) {
      size_t lsb = n & -n;
      auto l = lower_bound(v.begin() + n - lsb, v.begin() + n, a);
      auto u = upper_bound(v.begin() + n - lsb, v.begin() + n, b);
      ans += u - l;
    }
    return ans;
  }
};
