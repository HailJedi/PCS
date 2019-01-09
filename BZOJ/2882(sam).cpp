/*
Created 2018-12-24
"工艺"
*/

#pragma C++ optimize(2)

#include <bits/stdc++.h>

using namespace std;

const int N = 300000 + 5;

struct State {
	map<int, State*> tr;
	State *par;
	int len;
	State(int len) : par(0x0), len(len) {}
} *root, *last;

void extend(int w) {
	State *p = last;
	State *np = new State(p->len + 1);
	while (p && p->tr[w] == 0) {
		p->tr[w] = np;
		p = p->par;
	}
	if (p == 0) {
		np->par = root;
	} else {
		State *q = p->tr[w];
		if (q->len == p->len + 1) {
			np->par = q;
		} else {
			State *nq = new State(p->len + 1);
			nq->tr = q->tr;
			nq->par = q->par;
			q->par = nq;
			np->par = nq;
			while (p && p->tr[w] == q) {
				p->tr[w] = nq;
				p = p->par;
			}
		}
	}
	last = np;
}

int w[N];

int main() {
	freopen("read.in", "r", stdin);
	int n;
	root = new State(0);
	last = root;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &w[i]);
		extend(w[i]);
	}
	for (int i = 1; i <= n; i++) {
		extend(w[i]);
	}
	State *p = root;
	while (n--) {
		printf("%d ", p->tr.begin()->first);
		p = p->tr.begin()->second;
	}
	puts("");
	return 0;
}