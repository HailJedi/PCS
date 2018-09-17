#include <bits/stdc++.h>

using namespace std;

const int N = 1010;
int n;
string word;
set<string> lib;

int main() {
	ios::sync_with_stdio(false);
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> word;
		sort(word.begin(), word.end());
		word.erase(unique(word.begin(), word.end()), word.end());
		lib.insert(word);
	}
	cout << lib.size() << endl;
	return 0;
}