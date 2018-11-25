#include <cstdio>
#include <algorithm>
using namespace std;

const int maxn = 40000+5;
const int maxm = 10000+5;
const int maxd = 10000+5;
const int INF = 1e9;

int N, M, D;
int ming[maxm], maxg[maxm]; // min and max index of tail garland
int dp[maxm][maxn]; // current segment m, starting at n, d garlands after
int weight[maxn], sum[maxn];

inline int calc(int i, int j) {
	int mid = (i+j)/2;
	return max(sum[mid]-sum[i-1], sum[j]-sum[mid]);
}

int main() {
	int T; scanf("%d", &T);
	while (T--) {
		scanf("%d%d%d", &N, &M, &D); D *= 2;
		for (int i = 1; i <= N; i++)
			scanf("%d", &weight[i]);
		if ((M-1) * D < N || N & 1 || 2 * (M-1) > N) { puts("BAD"); continue; }

		for (int seg = 2; seg < M; seg++) {
			ming[seg] = max(2*seg, N-(M-1-seg)*D);
			maxg[seg] = min(seg*D, N-(M-1-seg)*2);
		} ming[1] = 2; maxg[1] = D;

		for (int i = 1; i <= N; i++)
			sum[i] = sum[i-1] + weight[i];

		for (int seg = 1; seg < M; seg++) {
			for (int gar = ming[seg]; gar <= maxg[seg]; gar += 2) {
				int &res = dp[seg][gar];
				res = INF;
				int lseg = seg-1;
				for (int lgar = max(ming[seg-1], gar-D); lgar <= min(gar-2, lseg*D); lgar += 2) {
					res = min(res, max(dp[lseg][lgar], calc(lgar+1, gar)));
				}
			}
		}

		printf("%d\n", dp[M-1][N]);
	}
	return 0;
}