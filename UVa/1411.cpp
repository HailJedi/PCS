#include <bits/stdc++.h>

using namespace std;

const int N = 100 + 5;
const int M = N * N;
const double eps = 1e-8;
const double INF = 1e30;

double antX[N], antY[N];
double treeX[N], treeY[N];

double mn[N];
double W[N][N];
double Lx[N], Ly[N];
bool S[N], T[N];
int Left[N];
int n;

double dist(int i, int j) {
	return sqrt(pow(treeX[i]-antX[j], 2) + pow(treeY[i]-antY[j], 2));
}

bool match(int i) {
	S[i] = true;
	for (int j = 1; j <= n; j++) if (!T[j]) {
		double diff = Lx[i]+Ly[j]-W[i][j];
		if (fabs(diff) < eps) {
			T[j] = true;
			if (!Left[j] || match(Left[j])) {
				Left[j] = i;
				return true;
			}
		} else {
			mn[j] = min(mn[j], diff);
		}
	}
	return false;
}

void update() {
	double a = INF;
	for (int i = 1; i <= n; i++) if (!T[i]) {
		a = min(a, mn[i]);
	}
	for (int i = 1; i <= n; i++) {
		if (S[i]) Lx[i] -= a;
		if (T[i]) Ly[i] += a;
		else mn[i] -= a;
	}
}

void KM() {
	for (int i = 1; i <= n; i++) {
		Left[i] = Lx[i] = Ly[i] = 0;
		for (int j = 1; j <= n; j++) {
			Lx[i] = max(Lx[i], W[i][j]);
		}
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			mn[j] = INF;
		}
		while (true) {
			for (int j = 1; j <= n; j++) {
				S[j] = T[j] = false;
			}
			if (match(i)) {
				break;
			} else {
				update();
			}
		}
	}
}

int main() {
//	freopen("read.in", "r", stdin);
//	freopen("write.out", "w", stdout);
	
	while (scanf("%d", &n) == 1) {
		for (int i = 1; i <= n; i++) {
			scanf("%lf %lf", &antX[i], &antY[i]);
		}
		for (int i = 1; i <= n; i++) {
			scanf("%lf %lf", &treeX[i], &treeY[i]);
		}
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				W[i][j] = -dist(i, j);
			}
		}
		KM();
		for (int i = 1; i <= n; i++) {
			printf("%d\n", Left[i]);
		}
	}
	return 0;
}
