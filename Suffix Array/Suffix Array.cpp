#include <array>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
using namespace std;

void count_sort(vector<int>& p, vector<int>& c) {
    // sort indexes in p by the values in array c
    int n = p.size();
    vector<int> cnt(n);
    for (int x : c) {
        ++cnt[x];
    }
    vector<int> new_p(n);
    vector<int> pos(n);
    for (int i = 1; i < n; ++i) {
        pos[i] = pos[i - 1] + cnt[i - 1];
    }
    for (int i : p) {
        int v = c[i];
        new_p[pos[v]] = i;
        ++pos[v];
    }
    p = new_p;
}

struct Suffarr {
    vector<int> arr;
    Suffarr(string s) {
        s += "$"; // minimal character
        int n = s.size();
        vector<int> p(n); // suffix array
        vector<int> c(n); // equivalence classes
        {
            // k = 0
            vector<pair<char, int>> a(n);
            for (int i = 0; i < n; ++i) {
                a[i] = {s[i], i};
            }
            sort(begin(a), end(a));

            for (int i = 0; i < n; ++i) p[i] = a[i].second;
            c[p[0]] = 0;
            for (int i = 1; i < n; ++i) {
                if (a[i].first == a[i-1].first) {
                    c[p[i]] = c[p[i-1]];
                } else {
                    c[p[i]] = c[p[i-1]] + 1;
                }
            }
        }

        for (int k = 0; (1 << k) < n; ++k) {
            // k -> k+1;
            // sort the substr of length 2^{k+1} based on those of length 2^k
            // -> radix sort in O(n)
            //
            // additional optimizazion:
            // p already contains the substr of length 2^k in increasing order
            // -> if we shift each index by 2^k, the second half is already sorted
            // -> one counting sort is enough
            for (int i = 0; i < n; ++i) {
                p[i] = (p[i] - (1 << k) + n) % n;
            }
            count_sort(p, c);

            vector<int> new_c(n);
            new_c[p[0]] = 0;
            for (int i = 1; i < n; ++i) {
                array<int, 2> now{c[p[i  ]], c[(p[i  ] + (1 << k)) % n]};
                array<int, 2> prv{c[p[i-1]], c[(p[i-1] + (1 << k)) % n]};
                if (now == prv) {
                    new_c[p[i]] = new_c[p[i-1]];
                } else {
                    new_c[p[i]] = new_c[p[i-1]] + 1;
                }
            }
            c = new_c;
        }

        p.erase(begin(p));
        arr = p;
    }

    int operator[](int i) const { return arr[i]; }
};
