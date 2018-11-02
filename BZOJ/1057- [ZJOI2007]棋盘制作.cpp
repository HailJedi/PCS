#include <bits/stdc++.h>

using namespace std;

const int N = 2e3+5;
int g[N][N];
int n, m;
int ans1, ans2;
int s[N];
stack<int> id, h;

int sqr(int x) {
	return x * x;
}
	
void push(int hh, int i) {
	int nid = i;
	while (!h.empty() && hh < h.top()) {
		ans1 = max(ans1, sqr(min(i - id.top(), h.top())));
		ans2 = max(ans2, (i - id.top()) * h.top());
		nid = id.top();
		id.pop(); h.pop();
	}
	id.push(nid);
	h.push(hh);
}

void calc() {
	for (int i = 1; i <= n; i++) {
		s[i] = 0;
	}
	for (int j = 1; j <= m; j++) {
		for (int i = 1; i <= n; i++) {
			s[i] = g[i][j] == 0 ? s[i] + 1 : 0;
			push(s[i], i);
		}
		push(0, n + 1);
		while (!id.empty()) {
			id.pop();
		}
		while (!h.empty()) {
			h.pop();
		}
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			cin >> g[i][j];
			if ((i + j) & 1) {
				g[i][j] ^= 1;
			}
		}
	}
	calc();
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			g[i][j] ^= 1;
		}
	}
	calc();
	cout << ans1 << endl << ans2 << endl;
	return 0;
}