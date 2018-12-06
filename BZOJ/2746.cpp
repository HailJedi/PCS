/*
Created 2018-12-06
"[HEOI2012]旅行问题"
*/

#include <bits/stdc++.h>

using namespace std;

const int N = 1000000 + 5;
const int mod = 1000000007;

char str[2*N];

struct Node {
	Node *tr[26], *suf[21];
	int id, hsh, dep;
	void *operator new(size_t, Node *o, int id, int hsh) {
		static Node pool[N], *p = pool;
		Node *ret = p++;
		for (int i = 0; i < 26; i++) {
			ret->tr[i] = o;
		}
		for (int i = 0; i < 21; i++) {
			ret->suf[i] = o;
		}
		ret->id = id;
		ret->hsh = hsh;
		return ret;
	}
} *root;

vector<Node*> nodes;
vector<int> pos[N];

void insert(char *s, int r) {
	int n = strlen(s);
	Node *o = root;
	for (int i = 0; i < n; i++) {
		if (o->tr[s[i]-'a'] == root) {
			o->tr[s[i]-'a'] = new (root, nodes.size(), (1ll * o->hsh * 26 + s[i]-'a') % mod) Node;
			nodes.push_back(o->tr[s[i]-'a']);
		}
		o = o->tr[s[i]-'a'];
		pos[r].push_back(o->id);
	}
}

void build() {
	queue<Node*> q;
	for (int i = 0; i < 26; i++) {
		if (root->tr[i] != root) {
			q.push(root->tr[i]);
		}
	}
	while (!q.empty()) {
		Node *o = q.front();
		q.pop();
		o->dep = o->suf[0]->dep + 1;
		for (int i = 1; i < 21; i++) {
			o->suf[i] = o->suf[i-1]->suf[i-1];
		}
		for (int i = 0; i < 26; i++) {
			if (o->tr[i] != root) {
				o->tr[i]->suf[0] = o->suf[0]->tr[i];
				q.push(o->tr[i]);
			} else {
				o->tr[i] = o->suf[0]->tr[i];
			}
		}
	}
}

Node *LCA(Node *u, Node *v) {
	if (u->dep < v->dep) {
		swap(u, v);
	}
	for (int i = 20; i >= 0; i--) {
		if (u->suf[i]->dep >= v->dep) {
			u = u->suf[i];
		}
	}
	if (u == v) {
		return u;
	}
	for (int i = 20; i >= 0; i--) {
		if (u->suf[i] != v->suf[i]) {
			u = u->suf[i], v = v->suf[i];
		}
	}
	return u->suf[0];
}

int n, q;
int sum[N];

int main() {
	root = new (0x0, 0, 0) Node;
	for (int i = 0; i < 26; i++) {
		root->tr[i] = root;
	}
	for (int i = 0; i < 21; i++) {
		root->suf[i] = root;
	}
	nodes.push_back(root);
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%s", str);
		insert(str, i);
		sum[i] = sum[i-1] + strlen(str);
	}
	build();
	scanf("%d", &q);
	while (q--) {
		int i, j, k, l;
		scanf("%d %d %d %d", &i, &j, &k, &l);
		j--, l--;
		Node *lca = LCA(nodes[pos[i][j]], nodes[pos[k][l]]);
		printf("%d\n", lca->hsh);
	}
	return 0;
}