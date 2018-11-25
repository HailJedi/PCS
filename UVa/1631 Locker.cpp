#include <iostream>
#include <cstring>
using namespace std;

inline int Upto(int bt, int tp) {
	return (tp - bt + 10) % 10;
}

inline int Downto(int tp, int bt) {
	return Upto(bt, tp);
}

inline int Upby(int bt, int by) {
	return (bt + by) % 10;
}

inline int Downby(int tp, int by) {
	return (tp - by + 10) % 10;
}

const int INF = 1e9;
const int maxn = 1000+10;
int code1[maxn], code2[maxn];
int d[maxn][10][10][10];
int vis[maxn][10][10][10];
int n, kase;

int dp(int cur, int x1, int x2, int x3) {
	if (cur == n+1) return 0;
	int &res = d[cur][x1][x2][x3];
	int &mark = vis[cur][x1][x2][x3];
	if (mark == kase) return res;
	mark = kase; res = INF;
	int down = Downto(x1, code2[cur]);
	int up = Upto(x1, code2[cur]);
	for (int i = 0; i <= up; i++)
		for (int j = 0; j <= i; j++) 
			res = min(res, up+dp(cur+1, Upby(x2, i), 
				Upby(x3, j), code1[cur+3]));
	for (int i = 0; i <= down; i++)
		for (int j = 0; j <= i; j++) 
			res = min(res, down+dp(cur+1, Downby(x2, i), 
				Downby(x3, j), code1[cur+3]));
	return res;
}

void solve() {
	++kase;
	cout << dp(1, code1[1], code1[2], code1[3]) << endl;
}

string s1, s2;

int main() {
	ios::sync_with_stdio(false);
	while (cin >> s1 >> s2) {
		n = s1.length();
		for (int i = 1; i <= n; i++) { 
			code1[i] = s1[i-1]-'0'; 
			code2[i] = s2[i-1]-'0';
		}
		solve();
	}
	return 0;
}