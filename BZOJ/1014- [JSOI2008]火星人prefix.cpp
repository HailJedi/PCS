#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long LL;

const int INF = (1<<30);
const int N = 100010;

int n, m, ans, ct, rt, ql, qr;
char s[N], ch[2];
LL p[N], hsh[N];
int son[N][2], sz[N], fa[N];

#define lch son[x][0]
#define rch son[x][1]

void Update(int x) {
	sz[x] = sz[lch] + sz[rch] + 1;
	hsh[x] = hsh[rch] + (s[x]-'a'+1)*p[sz[rch]];
	hsh[x] += hsh[lch]*p[sz[rch]+1];
}

void Rotate(int x, int &rt) {
	int y = fa[x], z = fa[y];
	int d = (son[y][1] == x);
	if (y == rt) rt = x;
	else son[z][son[z][1] == y] = x;
	son[y][d] = son[x][d^1];
	son[x][d^1] = y;
	fa[x] = z;
	fa[y] = x;
	fa[son[y][d]] = y;
	Update(y);
	Update(x);
}

void Splay(int x, int &rt) {
	while (x != rt) {
		int y = fa[x], z = fa[y];
		if (y != rt) {
			if ((son[z][0] == y) ^ (son[y][0] == x)) 
				Rotate(x, rt);
			else Rotate(y, rt);
		}
		Rotate(x, rt);
	}
}

void Build(int l, int r, int f) {
	if (l > r) return;
	int mid = (l+r)>>1;
	if (l == r) {
		hsh[l] = s[l]-'a'+1;
		sz[l] = 1;
	} else {
		Build(l, mid-1, mid);
		Build(mid+1, r, mid);
	}
	son[f][mid>f] = mid;
	fa[mid] = f;
	Update(mid);
}

int Rank(int x, int k) {
	while (true) {
		if (sz[lch] + 1 == k) {
			return x;
		}
		else if (k <= sz[lch])
			x = lch;
		else {
			k -= (sz[lch]+1);
			x = rch;
		}
	}
}

bool Check(int len) {
	int x = Rank(rt, ql);
	Splay(x, rt);
	x = Rank(rt, ql+len+1);
	Splay(x, son[rt][1]);
	x = son[son[rt][1]][0];
	int hsh1 = hsh[x];
	x = Rank(rt, qr);
	Splay(x, rt);
	x = Rank(rt, qr+len+1);
	Splay(x, son[rt][1]);
	x = son[son[rt][1]][0];
	int hsh2 = hsh[x];
	return hsh1 == hsh2;
}

void Query() {
	scanf("%d %d", &ql, &qr);
	ans = 0;
	int l = 1, r = ct - 1 - max(ql, qr);
	while (l <= r) {
		int mid = (l+r)>>1;
		if (Check(mid)) {
			l = mid+1;
			ans = mid;
		} else {
			r = mid-1;
		}
	}
	printf("%d\n", ans);
}

void Insert() {
	int pos;
	scanf("%d %s", &pos, ch);
	s[++ct] = ch[0];
	hsh[ct] = ch[0]-'a'+1;
	int x = Rank(rt, pos+1);
	Splay(x, rt);
	x = Rank(rt, pos+2);
	Splay(x, son[rt][1]);
	x = son[rt][1]; 
	fa[ct] = x;
	sz[ct] = 1;
	son[x][0] = ct;
	Update(x);
	Update(rt);
}

void Change() {
	int pos;
	scanf("%d %s", &pos, ch);
	int x = Rank(rt, pos+1);
	Splay(x, rt);
	s[x] = ch[0];
	Update(x);
}

int main() {
	scanf("%s", s+2);
	n = strlen(s+2);
	scanf("%d", &m);
	p[0] = 1;
	for (int i = 1; i < N; i++)
		p[i] = p[i-1] * 27;
	s[1] = s[n+2] = 'a';
	Build(1, n+2, 0);
	ct = n+2;
	rt = (1+n+2)/2;
	while (m--) {
		scanf("%s", ch);
		if (ch[0] == 'Q') Query();
		if (ch[0] == 'I') Insert();
		if (ch[0] == 'R') Change();
	}
	return 0;
}