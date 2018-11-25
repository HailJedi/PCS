#include <bits/stdc++.h>

using namespace std;

const int N = 500 + 5;
const int INF = 0x3f3f3f3f;

int W[N][N];
int Lx[N], Ly[N];
int mn[N];
int Left[N];
bool S[N], T[N];
int n;

bool match(int i) {
	S[i] = true;
	for (int j = 1; j <= n; j++) if (!T[j]) {
		int diff = Lx[i] + Ly[j] - W[i][j];
		if (diff == 0) {
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
	int a = INF;
	for (int j = 1; j <= n; j++) if (!T[j]) {
		a = min(a, mn[j]);
	}
	for (int i = 1; i <= n; i++) {
		if (S[i]) Lx[i] -= a;
		if (T[i]) Ly[i] += a;
		else mn[i] -= a;
	}
}

void KM() {
	for (int i = 1; i <= n; i++) {
		Lx[i] = Ly[i] = Left[i] = 0;
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
			for (int j = 1; j <= n; j++) {
				scanf("%d", &W[i][j]);
			}
		}
		KM();
		int sum = 0;
		for (int i = 1; i <= n; i++) {
			if (i > 1) {
				cout << ' ';
			}
			cout << Lx[i];
			sum += Lx[i];
		}
		cout << endl;
		for (int j = 1; j <= n; j++) {
			if (j > 1) {
				cout << ' ';
			}
			cout << Ly[j];
			sum += Ly[j];
		}
		cout << endl << sum << endl;
	}
	return 0;
}
