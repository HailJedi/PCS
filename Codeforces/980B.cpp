#include <bits/stdc++.h>

using namespace std;

char grid[5][200];

int main() {
	int n, k;
	cin >> n >> k;
	for (int i = 1; i <= 4; i++)
		for (int j = 1; j <= n; j++) grid[i][j] = '.';
	for (int i = 2; i <= 3; i++)
		for (int j = 2; j <= n/2; j++) {
			if (k >= 2) grid[i][j] = grid[i][n-j+1] = '#', k -= 2;
		}
	for (int i = 2; i <= 3; i++) 
		if (k) grid[i][n/2+1] = '#', k--;

	bool ok = true;
	for (int i = 1; i <= 4; i++)
		for (int j = 1; j <= n; j++) 
			if (grid[i][j] != grid[i][n-j+1]) 
				return puts("NO"), 0;
	puts("YES");
	for (int i = 1; i <= 4; i++) {
		for (int j = 1; j <= n; j++)
			cout << grid[i][j];
		puts("");
	}

	return 0;
}