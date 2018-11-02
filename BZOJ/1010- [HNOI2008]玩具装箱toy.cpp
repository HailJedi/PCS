#include <cstdio>
#include <algorithm>

using namespace std;

typedef long long ll;

const int maxn = 50010;
ll s[maxn], que[maxn], f[maxn];

double x(ll i) {
	return s[i];
}

double y(ll i) {
	return f[i] + s[i]*s[i];
}

double Slope(ll i, ll j) {
	return (y(j)-y(i))/(x(j)-x(i));
}

int main() {
	ll n, L, hd, tl;
	scanf("%lld %lld", &n, &L);
	L++; s[0] = 0;
	for (int i = 1; i <= n; i++) {
		scanf("%lld", &s[i]); 
		s[i] += s[i-1];
	}
	for (int i = 1; i <= n; i++)
		s[i] += i;
	hd = tl = 1; que[1] = 0;
	for (int i = 1; i <= n; i++) {
		while (hd < tl && Slope(que[hd], que[hd+1]) <= 2 * (s[i]-L)) hd++;
		int j = que[hd];
		f[i] = f[j] + (s[i]-s[j]-L)*(s[i]-s[j]-L);
		while (hd < tl && Slope(que[tl-1], que[tl]) > Slope(que[tl], i)) tl--;
		que[++tl] = i;
	}
	printf("%lld\n", f[n]);
	return 0;
}