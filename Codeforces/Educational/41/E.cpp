#include <bits/stdc++.h>
#define pb push_back

using namespace std;

typedef long long ll;

const int N = 200010;

int a[N], bits[N];
vector<int> rec[N];
int n;

void add(int pos, int v) {
	while (pos < n) {
		bits[pos] += v;
		pos |= pos+1;
	}
}

int query(int pos) {
	int ans = 0;
	while (pos >= 0) {
		ans += bits[pos];
		(pos &= (pos+1)) -= 1;
	}
	return ans;
}

int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%d", &a[i]);
		a[i]--;
		if (a[i] < N) rec[a[i]].pb(i);
		add(i, 1);
	}
	ll ans = 0;
	for (int i = 0; i < n; i++) {
		int g = min(n-1, a[i]);
		ans += query(g);
		for (auto x: rec[i]) 
			add(x, -1);
	}
	for (int i = 0; i < n; i++)
		if (i <= a[i]) --ans;
	printf("%lld\n", ans/2);
	return 0;
}