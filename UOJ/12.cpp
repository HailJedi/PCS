/*
Created 2018-11-27
"UOJ Easy Round #1
 A. 【UER #1】猜数"
*/

#include <bits/stdc++.h>

using namespace std;

int main() {
	ios::sync_with_stdio(false);
	int T;
	cin >> T;
	while (T--) {
		long long g, l;
		cin >> g >> l;
		long long pq = l / g;
		long long p = sqrt(pq);
		long long q = pq / p;
		cout << g * (p + q) << ' ' << g * (1 + pq) << endl;
	}
	return 0;
}