#include <bits/stdc++.h>

#define all(x) x.begin(), x.end()
#define sz(x) x.size()
#define eb emplace_back
#define t first
#define a second
#define N 200010

using namespace std;

typedef double db;
typedef pair<db, db> pdd;
vector<pdd> neg, pos;
db a[N], t[N];
db ans;
int n, T;

int main() {
	scanf("%d %d", &n, &T);
	for (int i = 1; i <= n; i++) scanf("%lf", &a[i]);
	db tap = 0, tan = 0;
	db ap = 0, an = 0;
	for (int i = 1; i <= n; i++) {
		scanf("%lf", &t[i]);
		t[i] -= T;
		if (t[i] == 0) ans += a[i];
		if (t[i] < 0) neg.eb(-t[i], a[i]), tan += -t[i] * a[i], an += a[i];
		if (t[i] > 0) pos.eb(t[i], a[i]), tap += a[i] * t[i], ap += a[i];
	}
	if (!sz(neg) || !sz(pos)) return printf("%.7lf\n", ans), 0;

	sort(all(pos));
	sort(all(neg));
	if (tap == tan) {
		ans += ap + an;
	} else 
	if (tap < tan) {
		ans += ap;
		db c = 0;
		for (auto e: neg) {
			if (c + e.t * e.a < tap) { c += e.t * e.a; ans += e.a; }
			else { ans += (tap-c)/e.t; break; }
		}
	} else 
	if (tap > tan) { 
		ans += an;	
		db c = 0;
		for (auto e: pos) {
			if (c + e.t * e.a < tan) { c += e.t * e.a; ans += e.a; }
			else { ans += (tan-c)/e.t; break; }
		}
	}
	printf("%.7lf\n", ans);
	return 0;
}