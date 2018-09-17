#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const int N = 1000010;
const ll p = 1009;
const ll mod = 1e18+3;
ll hsh[N], pw[N];
char s[N];
int ans[N], ml[N];
int n;

inline ll norm(ll a) {
	while (a >= mod) a -= mod;
	while (a < 0) a += mod;
	return a;
}

inline ll mul(ll a, ll b) {
	ll m = ((long double)(a)*b) / mod;
	return norm(a*b-m*mod);
}

ll _hash(int l, int r) {
	return norm(hsh[r]-mul(hsh[l], pw[r-l]));
}

bool match(int i, int j, int l) {
	if (i == j) return true;
	return _hash(i, i+l) == _hash(j, j+l);
}

int main() {
	scanf("%d %s", &n, s);
	hsh[0] = 0, pw[0] = 1;
	for (int i = 0; i < n; i++) 
		hsh[i+1] = norm(mul(hsh[i], p) + s[i] - 'a' + 1);
	for (int i = 1; i < N; i++)
		pw[i] = mul(pw[i-1], p);
	for (int i = 0; i < n/2; i++) {
		int c1 = i, c2 = n-1-i;
		if (s[c1] != s[c2]) {
			ml[i] = -1;
			continue;
		}
		int l = 0, r = i + 1;
		while (r - l > 1) {
			int mid = (l+r)>>1;
			if (match(c1-mid, c2-mid, 2*mid+1)) l = mid;
			else r = mid;
		}
		ml[i] = l;
	}
	for (int i = 0; i < n/2; i++) {
		if (~ml[i]) {
			ans[i-ml[i]] = max(ans[i-ml[i]], 2*ml[i]+1);
		}
	}
	for (int i = 1; i < n/2; i++)
		ans[i] = max(ans[i], ans[i-1]-2);
	for (int i = 0; i < (n+1)/2; i++) {
		if (!ans[i]) ans[i] = -1;
		printf("%d ", ans[i]);
	}
	puts("");
	return 0;
}