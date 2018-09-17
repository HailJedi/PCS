#include <bits/stdc++.h>
#define pb push_back
#define INF 2147483647

using namespace std;

const int N = 100010;
int w, l, c;
int cnt[N], cap[N];

int main() {
	cin >> w >> l;
	for (int i = 1; i <= l; i++) {
		cin >> cnt[i];
	}
	int lp = 1, rp = l;
	while (lp < rp && !cnt[lp]) lp++;
	for (int rp = l+1; rp <= w-1; rp++) {
		cin >> cap[rp];
		if (cap[rp]) {
			lp = max(rp - l, lp);
			while (cnt[rp] < cap[rp] && lp < rp) {
				int jump = min(cnt[lp], cap[rp]-cnt[rp]);
				cnt[lp] -= jump;
				cnt[rp] += jump;
				while (lp < rp && !cnt[lp]) lp++;
			}
		}
	}
	int ans = 0;
	for (int i = w-l; i <= w; i++) ans += cnt[i];	
	cout << ans << endl;
	return 0;
}