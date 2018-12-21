/*
Created 2018-12-19
"[Thu Summer Camp 2015]解密运算"
*/

#include <bits/stdc++.h>

using namespace std;

const int N = 5000000 + 5;

int n, m;
pair<int, int> p[N];

int main() {
	scanf("%d %d", &n, &m);
	for (int i = 0; i <= n; i++) {
		scanf("%d", &p[i].first);
		p[i].second = i;
	}
	sort(p, p+1+n);
	for (int i = 1, t = p[0].second; i <= n; i++) {
		printf("%d ", p[t].first);
		t = p[t].second;
	}
	puts("");
	return 0;
}