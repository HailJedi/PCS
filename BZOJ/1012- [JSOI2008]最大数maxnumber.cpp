#include <cstdio>
#include <algorithm>

using namespace std;

typedef long long ll;

const int root = 1;
const int maxm = 200010;
const ll inf = 1e12;
int l[maxm<<2], r[maxm<<2];
ll mx[maxm<<2];

void Build(int o, int L, int R) {
	l[o] = L; r[o] = R;
	if (L < R) {
		int mid = (L+R)>>1;
		Build(o<<1, L, mid);
		Build(o<<1|1, mid+1, R);
	}
}

void Change(int o, int pos, ll v) {
	if (pos == l[o] && pos == r[o]) {
		mx[o] = v;
	} else {
		if (pos <= r[o<<1]) Change(o<<1, pos, v);
		else Change(o<<1|1, pos, v);
		mx[o] = max(mx[o<<1], mx[o<<1|1]);
	}
}

ll QueryMax(int o, int L, int R) {
	if (L <= l[o] && r[o] <= R) 
		return mx[o];
	ll m1 = -inf, m2 = -inf;
	if (L <= r[o<<1]) m1 = QueryMax(o<<1, L, R);
	if (R >= l[o<<1|1]) m2 = QueryMax(o<<1|1, L, R);
	return max(m1, m2);
}

int main() {
	ll m, d, t = 0;
	scanf("%lld %lld", &m, &d);
	Build(root, 1, maxm);
	char op[10];
	ll x;
	int bck = 0;
	while (m--) {
		scanf("%s %lld", op, &x);
		if (op[0] == 'A') {
			x += t;
			Change(root, ++bck, x % d);
		} else {
			t = QueryMax(root, bck - x + 1, bck);
			printf("%lld\n", t);
		}
	}

	return 0;
}