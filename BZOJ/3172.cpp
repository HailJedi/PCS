/*
Created 2018-12-07
"[Tjoi2013]单词"
*/

#pragma C++ optimize(2)

#include <bits/stdc++.h>

using namespace std;

const int N = 1000000 + 5;

char str[N];

class ACMata {
public:
	struct Node {
		Node *tr[26], *suf;
		Node *head, *next;
		long long sz;
		bool inq;
		void *operator new(size_t, Node *o) {
			static Node pool[N], *p = pool;
			Node *ret = p++;
			for (int i = 0; i < 26; i++) {
				ret->tr[i] = o;
			}
			ret->suf = o;
			return ret;
		}
	} *root;

	int n;

	void init() {
		root = new (0x0) Node;
		for (int i = 0; i < 26; i++) {
			root->tr[i] = root;
		}
		root->suf = root;
		scanf("%d", &n);
		for (int i = 0; i < n; i++) {
			scanf("%s", str);
			insert(str);
		}
	}

	vector<Node*> vec;

	void insert(char *s) {
		int n = strlen(s);
		Node *o = root;
		for (int i = 0; i < n; i++) {
			if (o->tr[s[i]-'a'] == root) {
				o->tr[s[i]-'a'] = new (root) Node;
			}
			o = o->tr[s[i]-'a'];
		}
		o->sz++;
		vec.push_back(o);
	}

	void add_edge(Node *u, Node *v) {
		v->next = u->head;
		u->head = v;
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
			add_edge(o->suf, o);
			for (int i = 0; i < 26; i++) {
				if (o->tr[i] != root) {
					o->tr[i]->suf = o->suf->tr[i];
					q.push(o->tr[i]);
				} else {
					o->tr[i] = o->suf->tr[i];
				}
			}
		}
	}

	void dfs(Node *o) {
		for (int i = 0; i < 26; i++) {
			if (o->tr[i] != root) {
				dfs(o->tr[i]);
				o->sz += o->tr[i]->sz;
			}
		}
	}

	void dfs2(Node *u) {
		for (Node *v = u->head; v; v = v->next) {
			dfs2(v);
			u->sz += v->sz;
		}
	}

	void solve() {
		init();
		dfs(root);
		build();
		dfs2(root);
		for (int i = 0; i < n; i++) {
			printf("%lld\n", vec[i]->sz);
		}
	}
} ac;

int main() {
	ac.solve();
	return 0;
}