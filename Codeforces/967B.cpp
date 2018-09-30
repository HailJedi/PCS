#include <bits/stdc++.h>

#define N 100010

using namespace std;

struct hole {
	double sz;
	int id;
	hole() {}
	hole(int s, int id) : sz(s), id(id) {}
	bool operator < (const hole &h) const {
		return sz > h.sz;
	}
} h[N];

int n;
double A, B, S;

int main() {
	scanf("%d %lf %lf", &n, &A, &B);
	for (int i = 0; i < n; i++) {
		scanf("%lf", &h[i].sz);
		h[i].id = i;
		S += h[i].sz;
	}
	double R = h[0].sz * A / B;
	sort(h, h+n);
	int ans = 0;
	double T = 0;
	for (int i = 0; i < n; i++) { 
		if (T >= S - R) break;
		if (h[i].id == 0) continue;
		T += h[i].sz;
		ans++;
	}
	printf("%d\n", ans);
	return 0;
}