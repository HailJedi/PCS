#include <bits/stdc++.h>

using namespace std;

#define pb push_back
#define mp make_pair
#define sz(x) x.size()
#define all(x) x.begin(), x.end()
#define fs first
#define sc second
#define ll long long 
#define ull unsigned ll
#define db double
#define pii pair<int, int>
#define vi vector<int>
#define INF 1e9+7

typedef vector< vector<int> > matrix;

const int N = 1e9+7;
const int M = 20+5;
vector<int> unlucky;
int n, m, P;
string num;
matrix mat;

int main() {
	cin >> n >> m >> P;
	unlucky.resize(m);
	cin >> num;
	mat.resize(m);
	for (int i = 0; i < m; i++) {
		mat[i].resize(m);
	}
	for (int i = 0; i < m; i++) {
		unlucky[i] = num[i] - '0';
	}
	vector<int> tst;
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < 10; j++) {
			tst.push_back(j);
			bool one = false;
			for (int k = tst.size(); k >= 1; k--) {
				bool ok = true;
				for (int lp = 0, rp = tst.size()-k; rp < tst.size(); lp++, rp++) {
					if (unlucky[lp] != tst[rp]) {
						ok = false;
						break;
					}
				}
				if (ok) {
					one = true;
					if (k < m) {
						mat[i][k]++;
					}
					break;
				}
			}
			if (!one) mat[i][0]++;
			tst.pop_back();
		}
		tst.push_back(unlucky[i]);
	}
	// for (auto e: mat) {
	// 	for (auto f: e) {
	// 		cout << f << ' ';
	// 	}
	// 	cout << endl;
	// }
	matrix mat2 = matrix(m, vector<int>(m, 0));
	for (int i = 0; i < m; i++) {
		mat2[i][i] = 1;
	}
	while (n) {
		if (n & 1) {
			// (mat2 *= mat) %= k
			matrix mat3 = matrix(m, vector<int>(m, 0));
			for (int i = 0; i < m; i++) {
				for (int j = 0; j < m; j++) {
					for (int k = 0; k < m; k++) {
						(mat3[i][j] += mat2[i][k] * mat[k][j]) %= P;
					}
				}
			}
			mat2 = mat3;
		}
		n >>= 1;
		// (mat *= mat) %= k
		matrix mat4 = matrix(m, vector<int>(m, 0));
		for (int i = 0; i < m; i++) {
			for (int j = 0; j < m; j++) {
				for (int k = 0; k < m; k++) {
					(mat4[i][j] += mat[i][k] * mat[k][j]) %= P;
				}
			}
		}
		mat = mat4;
	}
	int ans = 0;
	// for (auto e: mat2[0]) {
		// (ans += e) %= P;
	// }
	for (int i = 0; i < mat2[0].size(); i++) {
		(ans += mat2[0][i]) %= P;
	}
	cout << ans << endl;
	return 0;
}