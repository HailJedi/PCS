/*
Created 2018-12-03
"[JSOI2007]文本生成器"
*/

#pragma GCC optimize(2)
#pragma G++ optimize(2)

#include <bits/stdc++.h>

using namespace std;

const int mod = 10007;

const int M = 10000 + 5;

class ACMata {
public:
	struct Node {
		Node *tr[26], *suf;
		int f[M];
		bool end;
		void *operator new(size_t, bool end) {
			static Node pool[M], *p = pool;
			Node *ret = p++;
			return ret;
		}
	} *root;

	void init() {
		root = new (false) Node;
		for (int i = 0; i < 26; i++) {
			root->tr[i] = root;
		}
		root->suf = root;
	}
	
	void insert(char *s) {
		int n = strlen(s);
		Node *o = root;
		for (int i = 0; i < n; i++) {
			if (o->tr[s[i]-'A'] == root) {
				o->tr[s[i]-'A'] = new (false) Node;
				for (int j = 0; j < 26; j++) {
					o->tr[s[i]-'A']->tr[j] = root;
				}
				o->tr[s[i]-'A']->suf = root;
			}
			o = o->tr[s[i]-'A'];
		}
		o->end = true;
	}

	Node* node[M];
	int idx;
	
	void build() {
		node[idx++] = root;
		static Node* q[M];
		int hd = 0, tl = 0;	
		for (int i = 0; i < 26; i++) {	
			if (root->tr[i] != root) {
				q[++tl] = root->tr[i];
			}
		}
		hd = 1;
		while (hd <= tl) {
			Node *o = q[hd++];
			node[idx++] = o;
			o->end |= o->suf->end;
			for (int i = 0; i < 26; i++) {
				if (o->tr[i] != root) {
					o->tr[i]->suf = o->suf->tr[i];
					q[++tl] = o->tr[i];
				} else {
					o->tr[i] = o->suf->tr[i];
				}
			}
		}
	}
	
	int solve(int m) {
		build();
		int ret = 0;
		root->f[0] = 1;
		for (int i = 0; i <= m; i++) {
			for (int k = 0; k < idx; k++) {
				Node *o = node[k];
				if (o->end) {
					continue;
				}
				if (i == m) {
					(ret += o->f[m]) %= mod;
				}
				for (int j = 0; j < 26; j++) {
					(o->tr[j]->f[i+1] += o->f[i]) %= mod;
				}
			}
		}
		return ret;
	}
} ac;

int main() {
	freopen("read.in", "r", stdin);
	int n, m;
	scanf("%d %d", &n, &m);
	ac.init();
	for (int i = 1; i <= n; i++) {
		char str[200];
		scanf("%s", str);
		ac.insert(str);
	}
	int ops = -ac.solve(m) + mod, pw = 1;
	for (int p = 1; p <= m; p++, (pw *= 26) %= mod);
	printf("%d\n", (ops + pw) % mod);
	return 0;
}
