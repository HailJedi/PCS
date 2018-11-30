/*
Created 2018-11-30
"高斯消元"
*/

#include <bits/stdc++.h>

using namespace std;

int n;

vector<double> solve(vector<vector<double>> &func) {
	for (int i = 0; i < n; i++) {
		double mx = 0;
		for (int j = i; j < n; j++) {
			mx = max(mx, fabs(func[j][i]));
		}
		if (mx < 1e-9) {
			return vector<double>();
		}
		for (int j = i+1; j <= n; j++) {
			func[i][j] /= func[i][i];
		}
		func[i][i] = 1;
		for (int j = 0; j < n; j++) if (j != i) {
			for (int k = i+1; k <= n; k++) {
				func[j][k] -= func[i][k] * func[j][i];
			}
			func[j][i] = 0;
		}
	}
	vector<double> ans(n);
	for (int i = 0; i < n; i++) {
		ans[i] = func[i][n];
	}
	return ans;
}

int main() {
	scanf("%d", &n);
	vector<vector<double>> func(n, vector<double>(n+1, 0));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j <= n; j++) {
			scanf("%lf", &func[i][j]);
		}
	}
	vector<double> ans = solve(func);
	if (ans.empty()) {
		puts("No Solution");
	} else {
		for (double e: ans) {
			printf("%.2lf\n", e);
		}
	}
	return 0;
}
