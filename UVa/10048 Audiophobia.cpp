#include <cstdio>
#include <algorithm>
using namespace std;

const int maxn = 100+5;
int C, S, Q;
int audio[maxn][maxn];

int main() {
	int kase = 0;
	while (scanf("%d %d %d", &C, &S, &Q) == 3 && C) {
		for (int i = 1; i <= C; i++)
			for (int j = 1; j <= C; j++)
				audio[i][j] = audio[j][i] = 1e9;
		for (int i = 1; i <= S; i++) {
			int u, v, a;
			scanf("%d %d %d", &u, &v, &a);
			audio[u][v] = audio[v][u] = a;
		}
		for (int k = 1; k <= C; k++)
			for (int i = 1; i <= C; i++)
				for (int j = 1; j <= C; j++)
					audio[i][j] = audio[j][i] = min(audio[i][j], max(audio[i][k], audio[k][j]));
		if (kase) puts("");
		printf("Case #%d\n", ++kase);
		for (int i = 1; i <= Q; i++) {
			int u, v;
			scanf("%d %d", &u, &v);
			if (audio[u][v] == 1e9) puts("no path");
			else printf("%d\n", audio[u][v]);
		}
	} 
	return 0;
}