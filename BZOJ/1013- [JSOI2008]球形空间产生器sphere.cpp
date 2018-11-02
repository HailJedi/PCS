#include <cstdio>
#include <cmath>
#include <algorithm>

using namespace std;

const double eps = 1e-10;
const int maxn = 15;

double B[maxn][maxn], ans[maxn];
int n;

void GuassElim() {
	for (int i = 1; i <= n; i++) { // processing #i factor
		// moving coeff with greatest abs value to row i
		int pivot = i;
		for (int j = i; j <= n; j++) 
			if (abs(B[j][i]) > abs(B[pivot][i])) pivot = j;
		swap(B[i], B[pivot]);

		if (abs(B[i][i]) < eps) return; // no solution

		// calc i's coeff
		for (int j = i + 1; j <= n+1; j++) B[i][j] /= B[i][i];
		for (int j = 1; j <= n; j++) 
			if (i != j) 
				for (int k = i + 1; k <= n+1; k++) B[j][k] -= B[j][i] * B[i][k];
	}
	
	for (int i = 1; i <= n; i++) ans[i] = B[i][n+1];
}

double v[maxn][maxn];
double sqr[maxn];

int main() {
	scanf("%d", &n);

	for (int i = 1; i <= n+1; i++)
		for (int j = 1; j <= n; j++) {
			scanf("%lf", &v[i][j]);
			sqr[i] += v[i][j] * v[i][j];
		}

	for (int i = 1; i <= n; i++) 
		for (int j = 1; j <= n; j++) 
			B[i][j] = (2*(v[1][j]-v[i+1][j]));

	for (int i = 1; i <= n; i++)
		B[i][n+1] = (sqr[1]-sqr[i+1]);

	GuassElim();

	for (int i = 1; i < n; i++)
		printf("%.3lf ", ans[i]);
	printf("%.3lf\n", ans[n]);

	return 0;
}