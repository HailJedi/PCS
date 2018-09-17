#include <bits/stdc++.h>
#define N 600010
typedef long long ll;

using namespace std;

int n;
ll x1, x2;

struct server {
	ll c;
	int id;
	server() {}
	bool operator < (const server &s) const {
		return c < s.c;
	}
} s[N];

int main() {
	scanf("%d %lld %lld", &n, &x1, &x2);
	for (int i = 1; i <= n; i++) {
		scanf("%lld", &s[i].c);
		s[i].id = i;
	}
	sort(s+1, s+1+n);
	for (int i = n-1; i >= 1; i--) {
		server mn = s[i];
		// try use smallest server for service #1
		int num1 = (x1 + mn.c - 1) / mn.c;
		int num2 = max(0, n+1-i-num1);
		if (num1 + i <= n && num2 * s[num1+i].c >= x2) {
			puts("Yes");
			printf("%d %d\n", num1, num2);
			for (int j = i; j <= num1+i-1; j++)
				printf("%d ", s[j].id);
			puts("");
			for (int j = num1+i; j <= n; j++) 
				printf("%d ", s[j].id);
			puts("");
			return 0;
		}
		// try use smallest server for service #2
		num2 = (x2 + mn.c - 1) / mn.c;
		num1 = max(0, n+1-i-num2);
		if (num2 + i <= n && num1 * s[num2+i].c >= x1) {
			puts("Yes");
			printf("%d %d\n", num1, num2);
			for (int j = num2+i; j <= n; j++)
				printf("%d ", s[j].id);
			puts("");
			for (int j = i; j <= num2+i-1; j++) 
				printf("%d ", s[j].id);
			puts("");
			return 0;
		}
	}
	puts("No");

	return 0;
}