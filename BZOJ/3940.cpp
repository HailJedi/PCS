/*
Created 2018-12-10
"[Usaco2015 Feb]Censoring Gold"
*/

#pragma C++ optimize(2)

#include <bits/stdc++.h>

using namespace std;

const int N = 100000 + 5;

char T[N], p[N];

class ACMata {
	public:
	struct Node {
		Node *tr[26], *suf;
		int len;
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

	void insert(char *s) {
		int n = strlen(s);
		Node *o = root;
		for (int i = 0; i < n; i++) {
			if (o->tr[s[i]-'a'] == root) {
				o->tr[s[i]-'a'] = new (root) Node;
			}
			o = o->tr[s[i]-'a'];
		}
		o->len = n;
	}

	void init() {
		root = new (0x0) Node;
		for (int i = 0; i < 26; i++) {
			root->tr[i] = root;
		}
		root->suf = root;
		int n;
		scanf("%s %d", T, &n);
		while (n--) {
			scanf("%s", p);
			insert(p);
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

	void solve() {
		init();
		build();
		stack<Node*> stk;
		stack<char> rans;
		stk.push(root);
		Node *o = root;
		int n = strlen(T);
		for (int i = 0; i < n; i++) {
			o = o->tr[T[i]-'a'];
			stk.push(o);
			rans.push(T[i]);
			if (o->len) {
				int len = o->len;
				while (len--) {
					stk.pop();
					rans.pop();
				}
				o = stk.top();
			}
		}
		stack<char> ans;
		while (!rans.empty()) {
			ans.push(rans.top());
			rans.pop();
		}
		while (!ans.empty()) {
			printf("%c", ans.top());
			ans.pop();
		}
		puts("");
	}
} ac;

int main() {
	ac.solve();
	return 0;
}