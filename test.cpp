/*
Created 2018-12-06
"[BeiJing2011]禁忌"
*/

#include <bits/stdc++.h>

using namespace std;

const int ST = 5 * 15 + 5;

int n, m, k, ct;

struct Matrix {
	long double a[ST][ST];
	Matrix() { 
		memset(a, 0, sizeof a);
	}
	void init() {
		for (int i = 0; i <= ct; i++) {
			a[i][i] = 1;
		}
	}
	Matrix operator* (const Matrix b) const {
		Matrix tmp;
		for (int i = 0; i <= ct; i++) {
			for (int j = 0; j <= ct; j++) {
				for (int k = 0; k <= ct; k++) {
					tmp.a[i][j] += a[i][k] * b.a[k][j];
				}
			}
		}
		return tmp;
	}
} mat, ans;

struct Node {
	Node *tr[26], *suf;
	bool end, vis;
	int id;
	void *operator new(size_t, Node *o, int id) {
		static Node pool[ST], *pt = pool;
		Node *ret = pt++;
		ret->id = id;
		ret->suf = o;
		for (int i = 0; i < k; i++) {
			ret->tr[i] = o;
		}
		return ret;
	}
} *root;

void insert(char *s) {
	int n = strlen(s);
	Node *o = root;
	for (int i = 0; i < n; i++) {
		if (o->tr[s[i]-'a'] == root) {
			o->tr[s[i]-'a'] = new (root, ++ct) Node;
		}
		o = o->tr[s[i]-'a'];
	}
	o->end = true;
}

void build() {
	queue<Node*> q;
	for (int i = 0; i < k; i++) {
		if (root->tr[i] != root) {
			q.push(root->tr[i]);
		}
	}
	while (!q.empty()) {
		Node *o = q.front();
		q.pop();
		for (int i = 0; i < k; i++) {
			if (o->tr[i] != root) {
				o->tr[i]->suf = o->suf->tr[i];
				q.push(o->tr[i]);
			} else {
				o->tr[i] = o->suf->tr[i];
			}
		}
	}
	ct++;
}

void make() {
	queue<Node*> q;
	q.push(root);
	root->vis = true;
	long double dt = 1LL * 1 / k;
	while (!q.empty()) {
		Node *o = q.front();
		q.pop();
		for (int i = 0; i < k; i++) {
			if (!o->tr[i]->vis) {
				o->tr[i]->vis = true;
				q.push(o->tr[i]);
			}
			if (o->tr[i]->end) {
				mat.a[o->id][ct] += dt;
				mat.a[o->id][0] += dt;
			} else {
				mat.a[o->id][o->tr[i]->id] += dt;
			}
		}
	}
	mat.a[ct][ct] = 1;
}

int main() {
	freopen("read.in", "r", stdin);
	scanf("%d %d %d", &n, &m, &k);
	root = new (0x0, 0) Node;
	root->suf = root;
	for (int i = 0; i < m; i++) {
		root->tr[i] = root;
	}
	for (int i = 1; i <= n; i++) {
		char str[20];
		scanf("%s", str);
		insert(str);
	}
	build();
	make();
	ans.init();
	while (m) {
		if (m & 1) {
			ans = ans * mat;
		}
		mat = mat * mat;
		m >>= 1;
	}
	printf("%.7Lf\n", ans.a[0][ct]);
	return 0;
}