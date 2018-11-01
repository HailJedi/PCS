/*
Created 2018-11-01
"Train Hard, Win Easy"
*/

#include <bits/stdc++.h>

using namespace std;

const int N = 300000 + 5;
const int M = 300000 + 5;

struct Coder {
	long long x, y;
	int id;
	bool operator < (const Coder &cd) const {
		return x + cd.y < cd.x + y;
	}
} coder[N];

int n, m;
pair<int, int> host[M];
long long ans[N];
int id[N];

int main() {
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; i++) {
		scanf("%lld %lld", &coder[i].x, &coder[i].y);
		coder[i].id = i;
	}
	sort(coder+1, coder+1+n);
	for (int i = 1; i <= n; i++) {
		id[coder[i].id] = i;
	}
	for (int i = 1; i <= m; i++) {
		scanf("%d %d", &host[i].first, &host[i].second);
		host[i].first = id[host[i].first];
		host[i].second = id[host[i].second];
	}
	long long sumx = 0;
	for (int i = 1; i <= n; i++) {
		ans[coder[i].id] += coder[i].y * (i-1) + sumx;
		sumx += coder[i].x;
	}
	long long sumy = 0;
	for (int i = n; i >= 1; i--) {
		ans[coder[i].id] += coder[i].x * (n-i) + sumy;
		sumy += coder[i].y;
	}
	for (int i = 1; i <= m; i++) {
		Coder &cd1 = coder[host[i].first], &cd2 = coder[host[i].second];
		long long score = min(cd1.x + cd2.y, cd1.y + cd2.x);
		ans[cd1.id] -= score;
		ans[cd2.id] -= score;
	}
	for (int i = 1; i <= n; i++) {
		printf("%lld ", ans[i]);
	}
	puts("");
	return 0;
}
