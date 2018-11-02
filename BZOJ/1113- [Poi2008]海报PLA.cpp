#include <bits/stdc++.h>

using namespace std;

const int N = 2.5e5+5;
int w, h, n, top;
int stk[N];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> n;
	int ans = n;
	for (int i = 1; i <= n; i++) {
		cin >> w >> h;
		while (h <= stk[top]) {
			if (h == stk[top]) {
				ans--;
			}
			top--;
		}
		stk[++top] = h;
	}
	cout << ans << endl;
	return 0;
}