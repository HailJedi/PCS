/*
Created 2018-12-18
"[Apio2014]回文串"
*/

#include <bits/stdc++.h>

using namespace std;

const int N = 300000 + 5;

int n;
char str[N];

class PalMata {
	public:
	struct Node {
		Node *tr[26], *suf;
		int len;
		long long cnt;
		void *operator new(size_t, int len, Node *o) {
			static Node pool[N], *p = pool;
			Node *ret = p++;
			ret->len = len;
			for (int i = 0; i < 26; i++) {
				ret->tr[i] = o;
			}
			return ret;
		}
	} *root0, *root1, *suff;

	stack<Node*> stk;

	Node *getSuf(Node *o, int i) {
		while (str[i-o->len-1] != str[i]) {
			o = o->suf;
		}
		return o;
	}

	void init() {
		root0 = new (0, 0x0) Node;
		for (int i = 0; i < 26; i++) {
			root0->tr[i] = root0;
		}
		root1 = new (-1, root0) Node;
		root0->suf = root1->suf = root1;
		suff = root0;
		for (int i = 1; i <= n; i++) {
			Node *cur = getSuf(suff, i);
			int v = str[i]-'a';
			if (cur->tr[v] == root0) {
				Node *now = new (cur->len + 2, root0) Node;
				Node *tmp = getSuf(cur->suf, i);
				now->suf = tmp->tr[v];
				cur->tr[v] = now;
				stk.push(now);
			}
			suff = cur->tr[v];
			suff->cnt++;
		}
	}

	long long solve() {
		long long ans = 0;
		while (!stk.empty()) {
			Node *o = stk.top();
			stk.pop();
			o->suf->cnt += o->cnt;
			ans = max(ans, 1LL * o->cnt * o->len);
		}
		return ans;
	}
} pal;

int main() {
	scanf("%s", str+1);
	n = strlen(str+1);
	pal.init();
	printf("%lld\n", pal.solve());
	return 0;
}