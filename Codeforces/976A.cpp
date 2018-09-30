#include <bits/stdc++.h>

using namespace std;

int n;
char str[200];

int main() {
	cin >> n;
	scanf("%s", str);
	bool f = true;
	for (int i = 0; i < n; i++) {
		if (str[i] == '0') printf("%c", str[i]);
		if (str[i] == '1' && f) f = false, printf("%c", str[i]);
	}
	return 0;
}
