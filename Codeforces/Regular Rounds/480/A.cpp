#include <bits/stdc++.h>

using namespace std;

int main() {
	string str;
	cin >> str;
	int p = 0, l = 0;
	for (int i = 0; i < str.length(); i++) {
		if (str[i] == 'o') p++;
		else l++;
	}
	if (p == 0 || l % p == 0) puts("YES");
	else puts("NO");
	return 0;
}