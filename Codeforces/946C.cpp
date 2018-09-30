#include <bits/stdc++.h>

using namespace std;

string str;

int main() {
	cin >> str;
	if (str.length() < 26) return puts("-1"), 0;
	char tar = 'a';
	for (int i = 0; i < str.length(); i++) {
		if (str[i] <= tar) str[i] = tar, tar++;
		if (tar > 'z') break;
	}		
	if (tar > 'z') cout << str << endl;
	else puts("-1");
	return 0;
}