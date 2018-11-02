#include <bits/stdc++.h>

using namespace std;

const int N = 2e3+5;
const int P = 1e9;

struct INT {
	int num[N], len;
	friend istream& operator >> (istream &in, INT &x) {
		static char s[N];
		scanf("%s", s+1);
		x.len = strlen(s+1);
		for (int i = 1; i <= x.len; i++) {
			x.num[i] = s[x.len-i+1] - '0';
		}
		return in;
	}
	int operator % (int p) {
		int ret = 0;
		for (int i = len; i > 0; i--) {
			((ret *= 10) += num[i]) %= p;
		}
		return ret;
	}
	void operator /= (int x) {
		for (int i = len; i > 0; i--) {
			num[i-1] += (num[i] % x) * 10;
			num[i] /= x;
		}
		num[0] = 0;
		while (len > 0 && !num[len]) {
			len--;
		}
	}
} n;

typedef pair<int, int> pii;
#define fs first
#define sc second
int digit[N];
int ct;
pii f[N], g[N];

void tension(pii &x, pii &y, int z) {
	if (x.fs > y.fs + z) {
		x.fs = y.fs + z;
		x.sc = 0;
	}
	if (x.fs == y.fs + z) {
		(x.sc += y.sc) %= P;
	}
}

int main() {
	cin >> n;
	while (n.len) {
		digit[++ct] = n % 4;
		n /= 4;
	}
	memset(f, 0x3f, sizeof(f));
	memset(g, 0x3f, sizeof(g));
	f[ct+1] = make_pair(0, 1);
	g[ct+1] = make_pair(1, 1);
	for (int i = ct; i > 0; i--) {
		if (digit[i] == 0) {
			tension(f[i], f[i+1], 0);
			tension(g[i], f[i+1], 1);
		} else
		if (digit[i] == 1) {
			tension(f[i], f[i+1], 1);
			tension(g[i], f[i+1], 2);
			tension(g[i], g[i+1], 2);
		} else 
		if (digit[i] == 2) {
			tension(f[i], f[i+1], 2);
			tension(f[i], g[i+1], 2);
			tension(g[i], g[i+1], 1);
		} else 
		if (digit[i] == 3) {
			tension(f[i], g[i+1], 1);
			tension(g[i], g[i+1], 0);
		}
	}
	cout << f[1].sc << endl;
	return 0;
}