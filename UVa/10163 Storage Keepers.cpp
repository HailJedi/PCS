#include <iostream>
using namespace std;

const int INF = 1e9;
const int MAXN = 100+5;
const int MAXM = 30+5;
int P[MAXM];
int dp[MAXM][MAXN];
int N, M, L, Y;

bool read() {
	cin >> N >> M;
	if (!N) return false;
	for (int i = 1; i <= M; i++) cin >> P[i];
	return true;
}

void solve() {
	// find the maximum l
	for (int i = 0; i <= M; i++)
		dp[i][0] = INF;
	for (int i = 1; i <= N; i++)
		dp[0][i] = 0;

	for (int i = 1; i <= M; i++) 
		for (int j = 1; j <= N; j++) {
			dp[i][j] = dp[i-1][j];
			for (int k = 1; k <= j; k++) 
				dp[i][j] = max(dp[i][j], min(dp[i-1][j-k], P[i]/k));
		}
	if (!dp[M][N]) { cout << "0 0\n"; return; }
	cout << (L = dp[M][N]) << ' ';

	// find the minimum y
	for (int i = 0; i <= M; i++)
		dp[i][0] = 0;
	for (int i = 1; i <= N; i++)
		dp[0][i] = INF;

	for (int i = 1; i <= M; i++) 
		for (int j = 1; j <= N; j++) {
			dp[i][j] = dp[i-1][j];
			for (int k = 1; k <= j && P[i]/k >= L; k++)
				dp[i][j] = min(dp[i][j], dp[i-1][j-k] + P[i]); 
		}
	cout << dp[M][N] << endl;
}

int main() {
	while (read()) {
		solve();
	}
	return 0;
}