#include <bits/stdc++.h>
#define mod 1000000007
#define N 10010

using namespace std;

typedef long long ll;

struct Matrix {
	ll A[3][3];
	Matrix() { memset(A, 0, sizeof(A)); }
	ll *operator [](int i) { return A[i]; }
	const ll *operator [](int i) const { return A[i]; }
};

Matrix unit() {
	Matrix r;
	for (int i = 0; i < 3; i++) r[i][i] = 1;
	return r;
}

Matrix operator *(const Matrix &A, const Matrix &B) {
	Matrix ret;
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			for (int k = 0; k < 3; k++)
				(ret[i][j] += A[i][k] * B[k][j]) %= mod;
	return ret;
}

void pow(Matrix &A, Matrix x, ll n) {
	while (n) {
		if (n & 1) A = A * x;
		x = x * x;
		n >>= 1;
	}
}

int C[3];

Matrix build() {
	Matrix R;
	if (!C[0]) R[0][0] = R[1][0] = 1;
	if (!C[1]) R[0][1] = R[1][1] = R[2][1] = 1;
	if (!C[2]) R[1][2] = R[2][2] = 1;
	return R;
}

struct opt { ll p; int a, f; } A[N<<1];
bool operator < (const opt &a, const opt &b) { return a.p < b.p; }

int n, ct, a;
ll m, l, r;

int main() {
	Matrix R = unit();
	scanf("%d %lld", &n, &m);
	A[ct++] = {2, 0, 0};
	while (n--) {
		scanf("%d %lld %lld", &a, &l, &r);
		A[ct++] = {l, a-1, 1};
		A[ct++] = {r+1, a-1, -1};
	}
	sort(A, A+ct);
	A[ct] = {m+1, 0, 0};
	for (int i = 0; i < ct; i++) {
		C[A[i].a] += A[i].f;
		pow(R, build(), A[i+1].p-A[i].p);
	}
	printf("%lld\n", R[1][1]);

	return 0;
}