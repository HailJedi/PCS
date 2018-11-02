#include <bits/stdc++.h>

using namespace std;

const int maxn = 1000010;

typedef long long ll;

ll x[maxn], p[maxn], c[maxn];
ll sp[maxn], s[maxn];
ll que[maxn<<1], dp[maxn];
int n;

ll Slope(int i, int j) {
	return (dp[i]-dp[j]+s[i]-s[j]) / (sp[i]-sp[j]);
}

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%lld %lld %lld", &x[i], &p[i], &c[i]);
		sp[i] = sp[i-1] + p[i];
		s[i] = s[i-1] + p[i]*x[i];
	}

	int head = 0, tail = 0;
	for (int i = 1; i <= n; i++) {
		while (head < tail 
			&& Slope(que[head], que[head+1]) < x[i])
			head++;
		int j = que[head];
		dp[i] = dp[j] + x[i]*(sp[i-1]-sp[j]) - (s[i-1]-s[j]) + c[i];
		while (head < tail 
			&& Slope(i, que[tail]) < Slope(que[tail], que[tail-1]))
			tail--;
		que[++tail] = i;
	}

	printf("%lld\n", dp[n]);

	return 0;
}