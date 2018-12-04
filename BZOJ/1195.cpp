/*
Created 2018-12-03
"[HNOI2006]最短母串"
*/

#include <bits/stdc++.h>

using namespace std;

const int N = 12;
const int M = 600 + 5;

class ACMata {

public: 

	struct Node {
		Node *tr[26], *suf;
		int f[1<<N];
		int end;
		Node () {}
		void *operator new(size_t, Node *o) {
			static Node pool[M], *p = pool;
			Node *ret = p++;
			for (int i = 0; i < 26; i++) {
				p->tr[i] = o;
			}
			p->suf = o;
			memset(p->f, -1, sizeof p->f);
			return p;
		}
	} *root;
	
	int n;
	
	void init(int n) {
		root = new (NULL) Node;
		this->n = n;
		for (int i = 0; i < 26; i++) {
			root->tr[i] = root;
		}
		root->suf = root;
		memset(root->f, -1, sizeof root->f);
	}

	int cnt;

	void insert(char *s, int id) {
		int n = strlen(s);
		Node *o = root;
		for (int i = 0; i < n; i++) {
			if (o->tr[s[i]-'A'] == root) {
				o->tr[s[i]-'A'] = new (root) Node;
			}
			o = o->tr[s[i]-'A'];
		}
		o->end |= (1 << id);
	}
	
	void solve() {
		build();
		root->f[0] = 0;
		min_step = -1;
		for (int i = 0; i < (1 << n); i++) {
			queue<Node*> q;
			for (int j = 0; j < (int)nodes.size(); j++) {
				Node *o = nodes[j];
				if (o->f[i] != -1) {
					q.push(o);
				}
			}
			while (!q.empty()) {
				Node *o = q.front();
				q.pop();
				if (i == (1 << n) - 1) {
					update(min_step, o->f[i]);
				}
				for (int k = 0; k < 26; k++) {
					if (update(o->tr[k]->f[i|o->tr[k]->end], o->f[i] + 1)) {
						if (o->tr[k]->end == 0) {
							q.push(o->tr[k]);
						}
					}
				}
			}
		}
		ans = vector<int>(min_step);
		assert(dfs(root, 0, 0));
		for (int i = 0; i < min_step; i++) {
			printf("%c", 'A' + ans[i]);
		}
		puts("");
	}

private:

	vector<Node*> nodes;

	void build() {
		nodes.push_back(root);
		queue<Node*> q;
		for (int i = 0; i < 26; i++) {
			if (root->tr[i] != root) {
				q.push(root->tr[i]);
			}
		}
		while (!q.empty()) {
			Node *o = q.front();
			q.pop();
			nodes.push_back(o);
			o->end |= o->suf->end;
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
	
	int min_step;
	vector<int> ans;

	bool dfs(Node *o, int st, int d) {
		if (o->f[st] == -1) {
			return false;
		}
		if (o->f[st] == min_step) {
			return st == (1 << n) - 1;
		}
		for (int i = 0; i < 26; i++) {
			if (o->tr[i]->f[st|o->tr[i]->end] == o->f[st] + 1) {
				ans[d] = i;
				if (dfs(o->tr[i], st | o->tr[i]->end, d+1)) {
					return true;
				}
			}
		}
		o->f[st] = -1;
		return false;
	}
		
	bool update(int &x, int y) {
		if (x == -1 || x > y) {
			x = y;
			return true;
		}
		return false;
	}
} ac;

int main() {
	int n;
	scanf("%d", &n);
	ac.init(n);
	for (int i = 0; i < n; i++) {
		char str[100];
		scanf("%s", str);
		ac.insert(str, i);
	}
	ac.solve();
	return 0;
}
