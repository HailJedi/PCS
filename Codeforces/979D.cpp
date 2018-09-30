#include <bits/stdc++.h>

using namespace std;

const int N = 1e5+5;
const int LG = 20;
const int INF = 1e9;

struct Trie {
	struct Node {
		Node *p[2];
		int minv;
		Node() { p[0] = p[1] = NULL; minv = INF; }
	} *root = new Node();

	void add(int x) {
		Node *o = root;
		for (int i = LG; i >= 0; i--) {
			int d = 1 & (x >> i);
			if (!o->p[d]) o->p[d] = new Node();
			o->minv = min(o->minv, x);
			o = o->p[d];
		}
		o->minv = min(o->minv, x);
	}

	int query(int x, int s) {
		int ret = 0;
		Node *o = root;
		for (int i = LG; i >= 0; i--) {
			int d = 1 & (x >> i);
			if (o->p[d^1] && o->p[d^1]->minv <= s) o = o->p[d^1], (ret <<= 1) |= (d ^ 1);
			else o = o->p[d], (ret <<= 1) |= d;
		}
		return ret;
	}

} trie[N];

int q, x, k, s, a, type;

int main() {
	scanf("%d", &q);
	while (q--) {
		scanf("%d", &type);
		if (type == 1) {
			scanf("%d", &a);
			for (int i = 1; i * i <= a; i++)
				if (a % i == 0) trie[i].add(a), trie[a/i].add(a);
		} else {
			scanf("%d %d %d", &x, &k, &s);
			if (x % k || trie[k].root->minv > s-x) { puts("-1"); continue; }
			int v = trie[k].query(x, s-x);
			printf("%d\n", v);
		}
	}
}