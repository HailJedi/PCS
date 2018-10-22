/*
Created 2018-10-22
"BerOS File Suggestion"
*/

#include <bits/stdc++.h>

using namespace std;

map<string, int> cnt;
map<string, string> mot;

int n, q;
string str;

int main() {
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> str;
		int len = str.length();
		map<string, bool> mark;
		for (int j = 0; j < len; j++) {
			string sub = "";
			for (int k = j; k < len; k++) {
				sub += str[k];
				if (!mark[sub]) {
					mark[sub] = true;
					cnt[sub]++;
					mot[sub] = str;
				}
			}
		}
	}
	cin >> q;
	while (q--) {
		cin >> str;
		cout << cnt[str] << ' ' << (cnt[str] ? mot[str] : "-") << endl;
	}
	return 0;
}
		
