#include <bits/stdc++.h>

using namespace std;

#define pb push_back
#define mp make_pair
#define fr first
#define sc second
#define sz(x) (int(x.size()))
#define all(x) (x).begin(), (x).end()
#define lb(v, x) lower_bound(all(v), x)

typedef vector<int> Array;
typedef pair<int, int> Pair;

const int N = 500010;

struct node {
	node *go[30], *pa;
	vector<node*> son;
	vector<Pair> q;
	int val, pos;
} pool[N], *cur = pool, *rt;

char s[N], t[N];
int n;

node *newnode() {
	node *p = cur++;
	p->val = p->pos = 0;
	p->pa = 0;
	p->son.clear();
	return p;
}

node *append(node *p, int w) {
	node *np = newnode();
	np->val = p->val + 1;
	while (p && !p->go[w]) {
		p->go[w] = np;
		p = p->pa;
	}
	if (!p) np->pa = rt;
	else {
		node *q = p->go[w];
		if (q->val == p->val + 1) np->pa = q;
		else {
			node *nq = newnode();
			nq->val = p->val + 1;
			memcpy(nq->go, q->go, sizeof(q->go));
			nq->pa = q->pa;
			np->pa = q->pa = nq;
			while (p && p->go[w] == q) {
				p->go[w] = nq;
				p = p->pa;
			}
		}
	}
	return np;
}

void init() {
	cur = pool;
	rt = newnode();
	node *np = rt;
	for (int i = 1; i <= n; i++) {
		np = append(np, s[i]-'a');
		np->pos = i;
	}
	for (node *p = pool; p != cur; p++)
		if (p->pa) p->pa->son.pb(p);
}

int q, c, ans[N];
int ct = 0;
vector<Pair> seq;

void dfs(node *p) {
	int id = ct++;
	if (p->pos) seq.pb(mp(id, p->pos));
	for (auto v: p->son) dfs(v);
	if (!p->q.empty()) {
		Array c;
		for (auto it = lb(seq, mp(id, -1)); it != seq.end(); ++it) c.pb(it->sc);
		sort(all(c));
		map<int, int> val;
		for (auto w: p->q) {
			if (w.fr > sz(c)) ans[w.sc] = -1;
			else {
				if (val.count(w.fr)) {
					ans[w.sc] += val[w.fr];
					continue;
				}
				int mv = 1e9;
				for (int i = 0; i < sz(c) && i+w.fr-1 < sz(c); i++)
					mv = min(mv, c[i+w.fr-1]-c[i]);
				val[w.fr] = mv;
				ans[w.sc] += mv;
			}
		}
	}
}

int main() {
	scanf("%s", s+1);
	n = strlen(s+1);
	init();
	scanf("%d", &q);
	for (int i = 1; i <= q; i++) {
		scanf("%d %s", &c, t);
		int m = strlen(t);
		node *p = rt;
		for (int j = 0; j < m; j++) {
			int w = t[j]-'a';
			if (!p->go[w]) { ans[i] = -1; break; }
			else p = p->go[w];
		}
		if (~ans[i]) {
			ans[i] = m;
			p->q.pb(mp(c, i));
		}
	}
	dfs(rt);
	for (int i = 1; i <= q; i++) 
		printf("%d\n", ans[i]);
	return 0;
}