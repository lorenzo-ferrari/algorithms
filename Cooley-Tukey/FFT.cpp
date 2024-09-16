#include <cmath>
#include <complex>
#include <cassert>
#include <vector>
using namespace std;

/// Verification:
/// Signal Processing (cses): https://cses.fi/problemset/result/10523162/
// beware of precision errors
using cx = complex<double>;
static constexpr double PI = acos(-1);

int reverse_bits(int n, int lg) {
	int ans = 0;
	for (int i = 0; i < lg; ++i)
		if (n & (1 << i))
			ans |= 1 << (lg - 1 - i);
	return ans;
}

// given z, compute y = Vz, where V is the Fourier matrix
void idft(vector<cx>& z) {	// evaluate
	int n = z.size();
	assert(!(n & (n - 1)) && "(wlog) n is a power of two");
	int lg = round(log2(z.size()));

	for (int i = 1; i < n; ++i)
		if (i < reverse_bits(i, lg))
			swap(z[i], z[reverse_bits(i, lg)]);

	for (int len = 2; len <= n; len *= 2) {
		cx w = exp(2i * PI / double(len));
		for (int k = 0; k < n; k += len) {
			cx p(1);
			for (int j = 0; j < len / 2; ++j) {
				cx u = z[k + j];
				cx v = z[k + len / 2 + j] * p;
				z[k + j] = u + v;
				z[k + len / 2 + j] = u - v;
				p *= w;
			}
		}
	}
}

// given y, compute z s.t. Vz = y, where V is the Fourier matrix
void dft(vector<cx>& y) {	// interpolate
	int n = y.size();
	for (cx& x : y) x /= n;
	for (int i = 1; i < n / 2; ++i) {
		swap(y[i], y[n - i]);
	}
	idft(y);
}

vector<int64_t> mul(vector<int> P, vector<int> Q) {
	int n = 1 << (int)ceil(log2(P.size() + Q.size() - 1));
    vector<cx> p(n), q(n);
    copy(P.begin(), P.end(), p.begin());
    copy(Q.begin(), Q.end(), q.begin());
	idft(p);
	idft(q);
    for (int i = 0; i < n; i++)
		p[i] *= q[i];
    dft(p);
    vector<int64_t> ans(n);
    for (int i = 0; i < n; i++)
		ans[i] = round(p[i].real());
    return ans;
}
