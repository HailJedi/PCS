/*
Created 2018-12-04
"[HNOI2004]L语言"
*/

#pragma GCC optimize(2)
#pragma G++ optimize(2)

#include <bits/stdc++.h>

using namespace std;

const int N = 20 + 5;
const int M = 1000000 + 5;

class ACMata {
public:
	struct Node {
		Node *tr[26], *suf;
		int len;
		void *operator new(size_t, Node *o) {
			static Node pool[N*N], *pt = pool;
			Node *ret = pt++;
			for (int i = 0; i < 26; i++) {
				ret->tr[i] = o;
			}
			ret->suf = o;
			return ret;
		}
	} *root;

	void init() {
		root = new (NULL) Node;
		for (int i = 0; i < 26; i++) {
			root->tr[i] = root;
		}
		root->suf = root;
	}
	
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

	int f[M];

	void solve(char *s) {
		int ans = 0, n = strlen(s+1);
		memset(f, 0, sizeof f);
		f[0] = 1;
		Node *o = root;
		for (int i = 1; i <= n; i++) {
			o = o->tr[s[i]-'a'];
			Node *p = o;
			for (; p != root; p = p->suf) {
				f[i] |= f[i-p->len];
				ans = max(ans, i * f[i]);
			}
		}
		printf("%d\n", ans);
	}
} ac;

char dic[N], str[M];

int main() {
	int n, m;
	scanf("%d %d", &n, &m);
	ac.init();
	for (int i = 1; i <= n; i++) {
		scanf("%s", dic);
		ac.insert(dic);
	}
	ac.build();
	while (m--) {
		scanf("%s", str+1);
		ac.solve(str);
	}
	return 0;
}
