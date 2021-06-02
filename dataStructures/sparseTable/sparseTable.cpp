#include <vector>

// range min query
class sparseTable {
	int n;
	int LOG;
	std::vector<int> Log;
	std::vector<std::vector<int>> id;
	std::vector<std::vector<int>> st;

	public:
		sparseTable(std::vector<int> v) {
			n = v.size();
			Log.assign(n + 1, 0);
			for (int i = 2; i <= n; i++)
				Log[i] = 1 + Log[i >> 1];
			LOG = Log[n] + 1;
			id.assign(n, std::vector<int> (LOG));
			st.assign(n, std::vector<int> (LOG));
			for (int i = 0; i < n; i++) {
				id[i][0] = i;
				st[i][0] = v[i];
			}
			for (int i = 1; i < LOG; i++)
				for (int j = 0; j + (1 << i) <= n; j++) {
					if (st[j][i - 1] < st[j + (1 << (i - 1))][i - 1]) {
						id[j][i] = id[j][i - 1];
						st[j][i] = st[j][i - 1];
					} else {
						id[j][i] = id[j + (1 << (i - 1))][i - 1];
						st[j][i] = st[j + (1 << (i - 1))][i - 1];
					}
				}
		}
	
		int minQuery(int l, int r) {
			int lg = Log[r - l];
			return st[l][lg] < st[r - (1 << lg)][lg] ? id[l][lg] : id[r - (1 << lg)][lg];
		}
};
