#include <bits/stdc++.h>

using namespace std;

int n;
int a[2000];

int main() {
	cin >> n;
	for (int i = 1; i <= n; i++)
		cin >> a[i];
	sort(a+1, a+1+n);
	int lp = 0, rp = n+1;
	for (int i = 1; i < n; i++) {
		if (i & 1) rp--;
		else lp++;
	}
	cout << a[rp-1] << endl;
	return 0;
}