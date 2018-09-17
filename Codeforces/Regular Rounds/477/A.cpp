#include <bits/stdc++.h>

#define eb emplace_back
#define INF 1e9

using namespace std;

vector<int> stair, elev;
vector<int>::iterator it;

int n, m, cl, ce, l, e, q;
int px1, px2, py1, py2;
double v;

int main() {
	scanf("%d %d %d %d %lf", &n, &m, &cl, &ce, &v);
	for (int i = 0; i < cl; i++) {
		scanf("%d", &l);
		stair.eb(l);
	}
	for (int i = 0; i < ce; i++) {
		scanf("%d", &e);
		elev.eb(e);
	}
	scanf("%d", &q);
	while (q--) {
		double ans = INF;
		scanf("%d %d %d %d", &px1, &py1, &px2, &py2);
		if (px1 == px2) { printf("%d\n", abs(py1-py2)); continue; }
		it = lower_bound(stair.begin(), stair.end(), py2);
		if (it != stair.end()) {
			int sp = *it;
			ans = min(ans, (double)abs(py1-sp)+abs(px1-px2)+abs(py2-sp));
		}
		it = upper_bound(stair.begin(), stair.end(), py2);
		if (it != stair.begin()) {
			it--;
			int sp = *it;
			ans = min(ans, (double)abs(py1-sp)+abs(px1-px2)+abs(py2-sp));
		}
		it = lower_bound(elev.begin(), elev.end(), py2);
		if (it != elev.end()) {
			int ep = *it;
			ans = min(ans, abs(py1-ep)+(double)abs(px1-px2)/v+abs(py2-ep));
		}
		it = upper_bound(elev.begin(), elev.end(), py2);
		if (it != elev.begin()) {
			it--;
			int ep = *it;
			ans = min(ans, abs(py1-ep)+(double)abs(px1-px2)/v+abs(py2-ep));
		}
		printf("%d\n", (int)(ans+0.9999999));
	}

	return 0;
}