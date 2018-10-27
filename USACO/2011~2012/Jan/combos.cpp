/*
Created 2018-10-26
"USACO 2012 January Contest, Gold Division
Problem 1. Video Game"
*/

#include <bits/stdc++.h>

using namespace std;

const int N = 15 + 5;
const int K = 1000 + 5;
const int INF = 0x3f3f3f3f;

int n, k;

struct Node {
	Node *ch[3], *fail;
	int f[K];
	int cnt;
	void *operator new(size_t, int v) {
		static Node pool[1000], *p = pool;
		Node *ret = p++;
		memset(ret->f, v, sizeof ret->f);
		return ret;
	}
} *root;

int cnt = 0;

void insert(char *s) {
	int n = strlen(s);
	Node *o = root;
	for (int i = 0; i < n; i++) {
		if (o->ch[s[i]-'A'] == 0x0) {
			o->ch[s[i]-'A'] = new (-INF) Node;
		}
		o = o->ch[s[i]-'A'];
	}
	o->cnt++;
}

void build_fail() {
	queue<Node*> q;
	q.push(root);
	while (!q.empty()) {
		Node *o = q.front();
		q.pop();
		for (int i = 0; i < 3; i++) {
			if (o->ch[i] != 0x0) {
				for (Node *pt = o->fail; pt != 0x0; pt = pt->fail) {
					if (pt->ch[i] != 0x0) {
						o->ch[i]->fail = pt->ch[i];
						break;
					}
				}
				if (o->ch[i]->fail == 0x0) {
					o->ch[i]->fail = root;
				}
				o->ch[i]->cnt += o->ch[i]->fail->cnt;
				q.push(o->ch[i]);
			}
		}
	}
}

void update(int &x, int y) {
	x = max(x, y);
}

void solve() {
	queue<Node*> q;
	for (int i = 1; i <= k; i++) {
		q.push(root);
		while (!q.empty()) {
			Node *o = q.front();
			q.pop();
			o->f[i] += o->cnt;
			for (int j = 0; j < 3; j++) {
				if (o->ch[j] != 0x0) {
					update(o->ch[j]->f[i], o->f[i-1]);
					q.push(o->ch[j]);
				}
			}
			for (Node *pt = o->fail; pt != 0x0; pt = pt->fail) {
				update(pt->f[i], o->f[i]);
			}
		}
	}
}

int main() {
	freopen("combos.in", "r", stdin);
	freopen("combos.out", "w", stdout);
	root = new (0) Node;
	scanf("%d %d", &n, &k);
	for (int i = 1; i <= n; i++) {
		char str[20];
		scanf("%s", str);
		insert(str);
	}
	build_fail();
	solve();
	printf("%d\n", root->f[k]);
	return 0;
}
