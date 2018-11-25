#include <bits/stdc++.h>

using namespace std;

const int N = 200 + 5;
const int L = 100 + 5;

string lok[N];
string f[N][L];
int len[N];
int pos[L*2], pre[L];

int main() {
//	freopen("read", "r", stdin);
//	freopen("write", "w", stdout);
	
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	
	int T;
	cin >> T;
	while (T--) {
		string str;
		cin >> str;
		str.push_back(';');
		int n = 0;
		while (str.length() > 1) {
			int idx = str.find(";");
			lok[++n] = str.substr(0, idx);
			len[n] = lok[n].length();
			lok[n] = lok[n] + lok[n];
			str = str.substr(idx+1);
		}
		for (int i = 1; i <= n; i++) {
			for (int j = 0; j < len[n]; j++) {
				f[i][j] = "-";
			}
		}
		for (int i = 0; i < len[n]; i++) {
			f[n][i] = lok[n].substr(i, len[n]);
		}
		for (int i = n; i >= 2; i--) {
			for (int j = 0; j < len[i]; j++) {
				string p = f[i][j].substr(0, len[i-1]);
				pre[0] = -1;
				int pt = -1;
				for (int k = 1; k < len[i-1]; k++) {
					while (pt != -1 && p[pt+1] != p[k]) {
						pt = pre[pt];
					}
					if (p[pt+1] == p[k]) {
						pt++;
					}
					pre[k] = pt;
				}
				string t = lok[i-1];
				pt = -1;
				for (int k = 0; k < 2*len[i-1]; k++) {
					while (pt != -1 && t[k] != p[pt+1]) {
						pt = pre[pt];
					}
					if (t[k] == p[pt+1]) {
						pt++;
					}
					pos[k] = pt+1;
					if (pt == len[i-1]-1) {
						pt = pre[pt];
					}
				}
				for (int k = 0; k < len[i-1]; k++) {
					int r = k+len[i-1]-1;
					string cand = lok[i-1].substr(k, len[i-1]-pos[r]) + f[i][j];
					if (f[i-1][k] == "-" || cand.length() < f[i-1][k].length()
						|| (cand.length() == f[i-1][k].length() && cand < f[i-1][k])) {
						f[i-1][k] = cand;
					}
				}
			}
		}
		string ans = "-";
		for (int i = 0; i < len[1]; i++) {
			if (ans == "-" || f[1][i].length() < ans.length() 
				|| (f[1][i].length() == ans.length() && f[1][i] < ans)) {
				ans = f[1][i];
			}
		}
		cout << ans << endl;
	}
	return 0;
}