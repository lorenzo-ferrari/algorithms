#include <string>
#include <vector>

std::vector<int> z_algo(std::string s) {
	int n = s.size();
	std::vector<int> Z(n);
	for (int i = 1, L = 0, R = 0; i < n; i++) {
		if (i > R) {
			L = R = i;
			while (R < n && s[R - L] == s[R])
				R++;
			Z[i] = R - L;
			R--;
		}
		else {
			if (i + Z[i - L] <= R)
				Z[i] = Z[i - L];
			else {
				L = i; // s[R] != s[R-L+1], sarei andato avanti
				while (R < n && s[R - L] == s[R])
					R++;
				Z[i] = R - L; R--;
			}
		}
	}

	return Z;
}
