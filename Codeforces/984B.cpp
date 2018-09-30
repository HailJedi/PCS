#include <bits/stdc++.h>

using namespace std;

int n, m;
char grid[110][110];

const int dx[] = {1, 1, 1, 0, -1, -1, -1, 0};
const int dy[] = {1, 0, -1, -1, -1, 0, 1, 1};

inline bool ismine(char c) {
	return c == '*';
}

inline bool isempty(char c) {
	return c == '.';
}

int main() {
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; i++)
		scanf("%s", grid[i]+1);
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (isdigit(grid[i][j])) {
				int val = grid[i][j] - '0';
				int cnt = 0;
				for (int k = 0; k < 8; k++) {
					int r = i + dx[k], c = j + dy[k];
					if (ismine(grid[r][c])) cnt++;
				}
				if (val != cnt) return puts("NO"), 0;
			} else 
			if (isempty(grid[i][j])) {
				for (int k = 0; k < 8; k++) {
					int r = i + dx[k], c = j + dy[k];
					if (ismine(grid[r][c])) return puts("NO"), 0;
				}
			}
		}
	}
	puts("YES");
	return 0;
}