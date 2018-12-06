/*
Created 2018-12-06
"[Usaco2012 Jan]Video Game"
*/

#include <bits/stdc++.h>

using namespace std;

const int N = 20 + 5;
const int L = 15 + 5;
const int K = 1000 + 5;
const int INF = 0x3f3f3f3f;

struct Node {
	Node *tr[3], *suf;
	int f[K];
	int end;
	void *operator new(size_t, Node *o) {
		static Node pool[N*L], *pt = pool;
		Node *ret = pt++;
		for (int i = 0; i < 3; i++) {
			ret->tr[i] = o;
		}
		ret->suf = o;
		memset(ret->f, -INF, sizeof ret->f);
		return ret;
	}
} *root;

void insert(char *s) {
	int n = strlen(s);
	Node *o = root;
	for (int i = 0; i < n; i++) {
		if (o->tr[s[i]-'A'] == root) {
			o->tr[s[i]-'A'] = new (root) Node;
		}
		o = o->tr[s[i]-'A'];
	}
	o->end++;
}

vector<Node*> nodes;

void build() {
	nodes.push_back(root);
	queue<Node*> q;
	for (int i = 0; i < 3; i++) {
		if (root->tr[i] != root) {
			q.push(root->tr[i]);
		}
	}
	while (!q.empty()) {
		Node *o = q.front();
		q.pop();
		nodes.push_back(o);
		o->end += o->suf->end;
		for (int i = 0; i < 3; i++) {
			if (o->tr[i] != root) {
				o->tr[i]->suf = o->suf->tr[i];
				q.push(o->tr[i]);
			} else {
				o->tr[i] = o->suf->tr[i];
			}
		}
	}
}

int n, k;

void update(int &x, int y) {
	x = max(x, y);
}

void solve() {
	for (int i = 0; i <= k; i++) {
		for (int j = 0; j < (int)nodes.size(); j++) {
			Node *o = nodes[j];
			for (int k = 0; k < 3; k++) {
				if (o->tr[k] != root) {
					update(o->tr[k]->f[i+1], o->f[i] + o->tr[k]->end);
				}
			}
			for (Node *suf = o->suf; ; suf = suf->suf) {
				update(suf->f[i], o->f[i]);
				if (suf == root) {
					break;
				}
			}
		}
	}
}

int main() {
	root = new (0x0) Node;
	for (int i = 0; i < 3; i++) {
		root->tr[i] = root;
	}
	root->suf = root;
	root->f[0] = 0;
	scanf("%d %d", &n, &k);
	for (int i = 1; i <= n; i++) {
		char str[20];
		scanf("%s", str);
		insert(str);
	}
	build();
	solve();
	printf("%d\n", root->f[k]);
	return 0;
}