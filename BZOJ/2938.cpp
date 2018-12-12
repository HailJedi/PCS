/*
Created 2018-12-07
"[Poi2000]病毒"
*/

#include <bits/stdc++.h>

using namespace std;

const int N = 30000 + 5;

char str[N];

class ACMata {
public:
	struct Node {
		Node *tr[2], *suf;
		bool end, vis, in;
		int id;
		void *operator new(size_t, Node *o, int id) {
			static Node pool[N], *p = pool;
			Node *ret = p++;
			ret->tr[0] = ret->tr[1] = ret->suf = o;
			ret->id = id;
			return ret;
		}
	} *root;

	int cnt;

	void init() {
		cnt = 0;
		root = new (0x0, ++cnt) Node;
		root->tr[0] = root->tr[1] = root->suf = root;
		int n;
		scanf("%d", &n);
		for (int i = 1; i <= n; i++) {
			scanf("%s", str);
			insert(str);
		}
	}

	void insert(char *s) {
		int n = strlen(s);
		Node *o = root;
		for (int i = 0; i < n; i++) {
			if (o->tr[s[i]-'0'] == root) {
				o->tr[s[i]-'0'] = new (root, ++cnt) Node;
			}
			o = o->tr[s[i]-'0'];
		}
		o->end = true;
	}

	void build() {
		queue<Node*> q;
		for (int i = 0; i < 2; i++) {
			if (root->tr[i] != root) {
				q.push(root->tr[i]);
			}	
		}
		while (!q.empty()) {
			Node *o = q.front();
			q.pop();
			o->end |= o->suf->end;
			for (int i = 0; i < 2; i++) {
				if (o->tr[i] != root) {
					o->tr[i]->suf = o->suf->tr[i];
					q.push(o->tr[i]);
				} else {
					o->tr[i] = o->suf->tr[i];
				}
			}
		}
	}

	bool dfs(Node *o) {
		o->in = true;
		for (int i = 0; i < 2; i++) {
			if (o->tr[i]->in) {
				return true;
			}
			if (!o->tr[i]->end && !o->tr[i]->vis) {
				o->tr[i]->vis = true;
				if (dfs(o->tr[i])) {
					return true;
				}
			}
		}
		o->in = false;
		return false;
	}

	void solve() {
		build();
		if (dfs(root)) {
			puts("TAK");
		} else {
			puts("NIE");
		}
	}
} ac;

int main() {
	ac.init();
	ac.solve();
	return 0;
}