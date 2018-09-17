#include <bits/stdc++.h>

using namespace std;

int cnt[256];
string rib;
pair<int, string> opt[3];
const string name[3] = { "Kuro", "Shiro", "Katie" };
int len, n;

int main() {
	cin >> n;
	for (int i = 0; i <= 2; i++) {
		cin >> rib;
		len = rib.length();
		memset(cnt, 0, sizeof(cnt));
		opt[i].second = name[i];
		for (char c: rib) cnt[c]++;
		int t = *max_element(cnt, cnt+256), rest = len - t;
		int s = n - rest;
		if (s == 1 && t == len) t--;
		t += min(n, rest);
		opt[i].first = max(opt[i].first, t);
	}
	sort(opt, opt+3);
	if (opt[1].first == opt[2].first) puts("Draw");
	else cout << opt[2].second << endl;
	return 0;
}