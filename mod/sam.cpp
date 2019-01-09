/*
Created 2018-12-24
*/

#include <bits/stdc++.h>

using namespace std;

const int N = 1000000 + 5;

char s[N];

struct State {
    State *tr[26], *par;
    int sz, len;
    State(int len) : sz(0), par(0), len(len) {
        memset(tr, 0, sizeof tr);
    }
} *root, *last;

struct cmp {
    bool operator () (const State *st1, const State *st2) const {
        return st1->len > st2->len;
    }
};

vector<State*> st[N];

void extend(int w) {
    State *p = last;
    State *np = new State(p->len + 1);
    st[np->len].push_back(np);
    while (p && p->tr[w] == 0) {
        p->tr[w] = np, p = p->par;
    }
    if (p == 0) {
        np->par = root;
    } else {
        State *q = p->tr[w];
        if (p->len + 1 == q->len) {
            np->par = q;
        } else {
            State *nq = new State(p->len + 1);
            st[nq->len].push_back(nq);
            memcpy(nq->tr, q->tr, sizeof q->tr);
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

long long ans;

int main() {
    scanf("%s", s);
    int n = strlen(s);
    root = new State(0);
    last = root;
    for (int i = 0; i < n; i++) {
        extend(s[i]-'a');
    }
    State *p = root;
    for (int i = 0; i < n; i++) {
        p = p->tr[s[i]-'a'];
        p->sz = 1;
    }
    for (int i = n; i >= 1; i--) {
			for (int j = 0; j < (int)st[i].size(); j++) {
				st[i][j]->par->sz += st[i][j]->sz;
				if (st[i][j]->sz != 1) {
					ans = max(ans, 1LL * st[i][j]->sz * i);
				}
			}
		}
    printf("%lld\n", ans);
    return 0;
}
