#include <bits/stdc++.h>

using namespace std;

const int N = 100 + 5;

int n;
char chess[N][N];
int w[N][N];
int Left[N];
bool S[N], T[N];
int col[N][N];

bool match(int i) {
	S[i] = true;
	for (int j = 0; j < n; j++) {
		if (w[i][j] && !T[j]) {
			T[j] = true;
			if (Left[j] == -1 || match(Left[j])) {
				Left[j] = i;
				return true;
			}
		}
	}
	return false;
}

void KM() {
	memset(Left, -1, sizeof Left);
	for (int i = 0; i < n; i++) {
		memset(S, false, sizeof S);
		memset(T, false, sizeof T);
		assert(match(i));
	}
}

int inrow[N], incol[N];

int main() {
//	freopen("read", "r", stdin);
//	freopen("write", "w", stdout);
	
	int T;
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		memset(w, 0, sizeof w);
		memset(inrow, 0, sizeof inrow);
		memset(incol, 0, sizeof incol);
		for (int i = 0; i < n; i++) {
			scanf("%s", chess[i]);
			for (int j = 0; j < n; j++) {
				if (chess[i][j] == '*') {
					w[i][j]++;
					inrow[i]++;
					incol[j]++;
				}
			}
		}
		int m = 0;
		for (int i = 0; i < n; i++) {
			m = max(m, inrow[i]);
			m = max(m, incol[i]);
		}
		printf("%d\n", m);
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				while (inrow[i] < m && incol[j] < m) {
					w[i][j]++;
					inrow[i]++;
					incol[j]++;
				}
			}
		}
		memset(col, 0, sizeof col);
		for (int c = 1; c <= m; c++) {
			KM();
			for (int i = 0; i < n; i++) {
				if (Left[i] != -1) {
					w[Left[i]][i]--;
					if (chess[Left[i]][i] == '*') {
						col[Left[i]][i] = c;
					}
				}
			}
		}
		for (int i = 0; i < n; i++) {
			printf("%d", col[i][0]);
			for (int j = 1; j < n; j++) {
				printf(" %d", col[i][j]);
			}
			puts("");
		}
	}
	return 0;
}
