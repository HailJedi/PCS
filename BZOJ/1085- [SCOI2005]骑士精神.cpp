#include <bits/stdc++.h>

using namespace std;

const int target[5][5] = {
	{1, 1, 1, 1, 1}, 
	{0, 1, 1, 1, 1},  
	{0, 0, -1, 1, 1}, 
	{0, 0, 0, 0, 1},
	{0, 0, 0, 0, 0}
};
const int dx[] = {2, 2, 1, -1, -2, -2, -1, 1};
const int dy[] = {1, -1, -2, -2, -1, 1, 2, 2};

int T;
char in[5];
int bd[5][5];

int prec(int b[5][5]) {
	int ret = 0;
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			ret += (b[i][j] != target[i][j] ? 1 : 0);
		}
	}
	return ret;
}

bool inbound(int x, int y) {
	return 0 <= x && x < 5 && 0 <= y && y < 5;
}

bool dfs(int d, int lim, int b[5][5], int x, int y) {
	if (d == lim) {
		return prec(b) == 0;
	}
	for (int i = 0; i < 8; i++) {
		int nx = x + dx[i], ny = y + dy[i];
		if (inbound(nx, ny)) {
			swap(b[x][y], b[nx][ny]);
			if (prec(b) + d <= lim && dfs(d+1, lim, b, nx, ny)) {
				return true;
			}
			swap(b[x][y], b[nx][ny]);
		}
	}
	return false;
}

int main() {
	scanf("%d", &T);
	while (T--) {
		int bx, by;
		for (int i = 0; i < 5; i++) {
			scanf("%s", in);
			for (int j = 0; j < 5; j++) {
				if (in[j] != '*') {
					bd[i][j] = in[j] - '0';
				} else {
					bd[i][j] = -1;
					bx = i, by = j;
				}
			}
		}
		bool ok = false;
		for (int lim = 0; lim <= 15; lim++) {
			if (dfs(0, lim, bd, bx, by)) {
				cout << lim << endl;
				ok = true;
				break;
			}
		}
		if (!ok) {
			cout << -1 << endl;
		}
	}
	return 0;
}