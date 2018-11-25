#include <cstdio>  
#include <cmath>  
#include <cstring>  
#include <string>  
#include <cstdlib>  
#include <algorithm> 
using namespace std;

const int INF = 1e9;
const int maxn = 100+5;
char unfold[maxn];
int type[maxn][maxn]; 
int vis[maxn][maxn];
int shortest[maxn][maxn];
int kase;

inline int digit(int x) {
	return x <= 9 ? 1 : x <= 99 ? 2 : 3;
}

int solve(int l, int r);

int check(int l, int r, int &piece) {
	int res = INF, totlen = r-l+1;
	for (int len = 1; len < totlen; len++) {
		if (totlen % len) continue;
		bool ok = true;
		for (int i = l; i + len <= r; i++)
			if (unfold[i] != unfold[i+len]) { ok = false; break; }
		if (ok) {
			int cmp = digit(totlen/len) + 2 + shortest[l][l+len-1];
			if (cmp < res) {
				res = cmp;
				piece = len;
			}
		}
	}
	return res;
}

int solve(int l, int r) {
	int &res = shortest[l][r];
	if (vis[l][r] == kase) return res;
	vis[l][r] = kase;
	if (l == r) { 
		type[l][r] = 0;
		return res = 1; 
	}
	res = r-l+1; type[l][r] = 0;
	for (int i = l; i < r; i++) {
		int cmp = solve(l, i) + solve(i+1, r);
		if (cmp < res) { res = cmp; type[l][r] = -i; }
	}
	int piece, lenth = check(l, r, piece);
	if (lenth < res) {
		res = lenth;
		type[l][r] = piece;
	}
	return res;
}

void print(int l, int r) {
	if (type[l][r] == 0) {
		for (int i = l; i <= r; i++) 
			putchar(unfold[i]);
		return;
	} else if (type[l][r] > 0) {
		printf("%d", (r-l+1)/type[l][r]);
		putchar('(');
		print(l, l+type[l][r]-1);
		putchar(')');
		return;
	} else {
		print(l, -type[l][r]); 
		print(-type[l][r]+1, r);
		return;
	}
}

int main() {
	while (gets(unfold+1)) {
		kase++;
		int lenth = strlen(unfold+1);
		solve(1, lenth);
		print(1, lenth);
		puts("");
	}
	return 0;
}