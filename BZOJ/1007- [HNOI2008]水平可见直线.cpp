#include <bits/stdc++.h>

using namespace std;

const int maxn = 50010;
const double INF = 1e9;

struct Line {
	double A, B;
	int id;
	bool operator < (const Line &rhs) const {
		if (A != rhs.A) 
			return A < rhs.A;
		return B > rhs.B;
	}
} line[maxn];

int n;
int stk[maxn], it;
int ans[maxn];

double IntersecX(int i, int j) {
	double A1 = line[i].A, B1 = line[i].B;
	double A2 = line[j].A, B2 = line[j].B;
	if (A1 == A2) return -INF;
	return (B2-B1) / (A1-A2);
}

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%lf %lf", &line[i].A, &line[i].B);
		line[i].id = i;
	}
	sort(line+1, line+1+n);

	it = 0;
	for (int i = 1; i <= n; i++) {
		if (i != 1 && line[i].A == line[i-1].A) continue;
		while (it >= 2 && IntersecX(i, stk[it]) <= IntersecX(stk[it], stk[it-1]))
			it--;
		stk[++it] = i;
	}

	for (int i = 1; i <= it; i++)
		ans[i] = line[stk[i]].id;
	sort(ans+1, ans+1+it);

	for (int i = 1; i <= it; i++)
		printf("%d ", ans[i]);
	return 0;
}