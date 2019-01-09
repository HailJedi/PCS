/*
Created 2018-12-26
"NSUBSTR - Substrings"
*/

#include <bits/stdc++.h>

using namespace std;

const int N = 250000 + 5;

struct State {
	State *tr[26], *fa;
	int len, sz;
	State(int len) : len(len), sz(0), fa(0) {
		memset(tr, 0, sizeof tr);
	}
} *root, *last;

vector<State*> pool[N];

void extend(int w) {
	State *p = last;
	State *np = new State(p->len+1);
	pool[np->len].push_back(np);
	for (; p && p->tr[w] == 0; p->tr[w] = np, p = p->fa);
	if (p == 0) {
		np->fa = root;
	} else {
		State *q = p->tr[w];
		if (q->len == p->len+1) {
			np->fa = q;
		} else {
			State *nq = new State(p->len+1);
			pool[nq->len].push_back(nq);
			memcpy(nq->tr, q->tr, sizeof q->tr);
			nq->fa = q->fa;
			q->fa = nq;
			np->fa = nq;
			for (; p && p->tr[w] == q; p->tr[w] = nq, p = p->fa);
		}
	}
	last = np;
}

int n;
char str[N];
int f[N];

int main() {
	root = new State(0);
	last = root;
	scanf("%s", str+1);
	n = strlen(str+1);
	for (int i = 1; i <= n; i++) {
		extend(str[i]-'a');
	}
	State *p = root;
	for (int i = 1; i <= n; i++) {
		p = p->tr[str[i]-'a'];
		p->sz = 1;
	}
	for (int i = n; i >= 1; i--) {
		for (int j = 0; j < (int)pool[i].size(); j++) {
			pool[i][j]->fa->sz += pool[i][j]->sz;
			f[i] = max(f[i], pool[i][j]->sz);
		}
	}
	for (int i = n-1; i >= 1; i--) {
		f[i] = max(f[i], f[i+1]);
	}
	for (int i = 1; i <= n; i++) {
		printf("%d\n", f[i]);
	}
	return 0;
}