/*
Created 2018-12-06
"背单词"
*/

#include <bits/stdc++.h>

using namespace std;

const int N = 20000 + 5;
const int L = 300000 + 5;

void update(long long &x, long long y) {
	x = max(x, y);
}

class Failtree {
public:
	struct Edge {
		Edge *next;
		int v;
		void *operator new(size_t, Edge *next, int v) {
			static Edge pool[L], *p = pool;
			if (p == pool + L) {
				p = pool;
			}
			Edge *ret = p++;
			ret->next = next;
			ret->v = v;
			return ret;
		}
	} *head[L];

	int tim, st[L], ed[L];
	
	void init() {
		tim = 0;
		memset(head, 0x0, sizeof head);
		memset(st, 0, sizeof st);
		memset(ed, 0, sizeof ed);
	}

	void add_edge(int u, int v) {
		head[u] = new (head[u], v) Edge;
	}

	void dfs(int u, int fa) {
		st[u] = ++tim;
		for (Edge *e = head[u]; e; e = e->next) {
			if (e->v != fa) {
				dfs(e->v, u);
			}
		}
		ed[u] = tim;
	}
} ftree;

class ACAutomata {
public:
	struct Node {
		Node *tr[26], *suf;
		int id;
		void *operator new(size_t, Node *o, int id) {
			static Node pool[L], *p = pool;
			if (p == pool + L) {
				p = pool;
			}
			Node *ret = p++;
			ret->suf = o;
			for (int i = 0; i < 26; i++) {
				ret->tr[i] = o;
			}
			ret->id = id;
			return ret;
		}
	} *root;

	int cnt;
	vector<int> pos[N];

	void init(int n) {
		cnt = 0;
		root = new (0x0, ++cnt) Node;
		for (int i = 0; i < 26; i++) {
			root->tr[i] = root;
		}
		root->suf = root;
		for (int i = 1; i <= n; i++) {
			pos[i].clear();
		}
	}

	void insert(char *str, int p) {
		int n = strlen(str);
		Node *o = root;
		for (int i = 0; i < n; i++) {
			if (o->tr[str[i]-'a'] == root) {
				o->tr[str[i]-'a'] = new (root, ++cnt) Node;
			}
			o = o->tr[str[i]-'a'];
			pos[p].push_back(o->id);
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
			ftree.add_edge(o->suf->id, o->id);
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
} ac;

class Segtree {
public:
	struct Node {
		Node *ls, *rs;
		int l, r;
		long long tag, mx;
		void *operator new(size_t, int l, int r) {
			static Node pool[L*5], *p = pool;
			if (p == pool + L*5) {
				p = pool;
			}
			Node *ret = p++;
			ret->l = l;
			ret->r = r;
			ret->tag = ret->mx = 0;
			return ret;
		}
	} *root;

	int n;

	void build(Node *&o) {
		if (o->l != o->r) {
			int mid = (o->l + o->r) / 2;
			o->ls = new (o->l, mid) Node;
			o->rs = new (mid+1, o->r) Node;
			build(o->ls);
			build(o->rs);
		}
	}

	void build() {
		root = new (1, n) Node;
		build(root);
	}

	void init(int n) {
		this->n = n;
		build();
	}

	void pushdown(Node *&o) {
		if (o->tag) {
			update(o->ls->mx, o->tag);
			update(o->ls->tag, o->tag);
			update(o->rs->mx, o->tag);
			update(o->rs->tag, o->tag);
			o->tag = 0;
		}
	}

	void change(Node *&o, int l, int r, long long v) {
		if (l <= o->l && o->r <= r) {
			update(o->mx, v);
			update(o->tag, v);
			return;
		}
		pushdown(o);
		int mid = (o->l + o->r) / 2;
		if (l <= mid) {
			change(o->ls, l, r, v);
		}
		if (r > mid) {
			change(o->rs, l, r, v);
		}
		o->mx = max(o->ls->mx, o->rs->mx);
	}

	void change(int l, int r, long long v) {
		change(root, l, r, v);
	}

	long long query(Node *&o, int p) {
		if (o->l == o->r) {
			return o->mx;
		}
		pushdown(o);
		int mid = (o->l + o->r) / 2;
		if (p <= mid) {
			return query(o->ls, p);
		} else {
			return query(o->rs, p);
		}
	}

	long long query(int p) {
		return query(root, p);
	}
} seg;

char str[L];
long long w[N];

int main() {
	int T, n;
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		ac.init(n);
		ftree.init();
		for (int i = 1; i <= n; i++) {
			scanf("%s %lld", str, &w[i]);
			ac.insert(str, i);
		}
		ac.build();
		ftree.dfs(1, 0);
		seg.init(ftree.tim);
		long long ans = 0;
		for (int i = 1; i <= n; i++) {
			if (w[i] > 0) {
				long long t = 0;
				int sz = ac.pos[i].size()-1;
				for (int j = 0; j <= sz; j++) {
					update(t, seg.query(ftree.st[ac.pos[i][j]]));
				}
				update(ans, t + w[i]);
				seg.change(ftree.st[ac.pos[i][sz]], ftree.ed[ac.pos[i][sz]], t + w[i]);
			}
		}
		printf("%lld\n", ans);
	}
	return 0;
}