/*
Created 2018-12-04
"[Jsoi2009]有趣的游戏"
*/

#include <bits/stdc++.h>

using namespace std;

const int N = 20;

struct Node {
	Node *tr[26], *suf;
	int id;
	bool end;
	void *operator new(size_t, Node *o, int id) {
		static Node pool[N*N], *p = pool;
		Node *ret = p++;
		ret->suf = o;
		for (int i = 0; i < 26; i++) {
			ret->tr[i] = o;
		}
		ret->id = id;
		return ret;
	}
} *root;

double p[N];
bool out[N];
int hsh[N];
int cnt;

void insert(char *s, int id) {
	int n = strlen(s);
	Node *o = root;
	for (int i = 0; i < n; i++) {
		if (o->tr[s[i]-'A'] == root) {
			o->tr[s[i]-'A'] = new (root, cnt++) Node;
		}
		o = o->tr[s[i]-'A'];
	}
	hsh[id] = o->id;
	o->end = true;
}

vector<double> solve(vector< vector<double> > &f) {
	for (int i = 0; i < cnt; i++) {
		double mx = 0;
		for (int j = i; j < cnt; j++) {
			mx = max(mx, fabs(f[j][i]));
		}
		if (mx < -1e10) {
			return vector<double>();
		}
		double t = f[i][i];
		for (int j = i; j <= cnt; j++) {
			f[i][j] /= t;
		}
		for (int j = 0; j < cnt; j++) if (j != i) {
			double t = f[j][i];
			for (int k = i; k <= cnt; k++) {
				f[j][k] -= f[i][k] * t;
			}
		}
	}
	vector<double> ans(cnt);
	for (int i = 0; i < cnt; i++) {
		ans[i] = f[i][cnt];
	}
	return ans;
}

int main() {
	int n, m, l;
	scanf("%d %d %d", &n, &l, &m);
	for (int i = 0; i < m; i++) {
		int a, b;
		scanf("%d %d", &a, &b);
		p[i] = 1.0 * a / b;
		out[i] = !a;
	}
	int cut = 0;
	root = new (0x0, cnt++) Node;
	for (int i = 0; i < m; i++) {
		root->tr[i] = root;
	}
	root->suf = root;
	for (int i = 1; i <= n; i++) {
		char str[20];
		scanf("%s", str);
		insert(str, i);
		for (int j = 0; j < strlen(str); j++) {
			if (out[str[j]-'A']) {
				cut++;
				break;
			}
		}
	}
	if (cut == n) {
		for (int i = 1; i <= n; i++) {
			puts("0.00");
		}
		return 0;
	}
	vector< vector<double> > f(cnt, vector<double>(cnt+1, 0));
	f[0][cnt] = 1;
	queue<Node*> q;
	for (int i = 0; i < m; i++) {
		if (root->tr[i] != root) {
			q.push(root->tr[i]);
		}
		f[root->tr[i]->id][root->id] -= p[i];
	}
	for (int i = 0; i < cnt; i++) {
		f[i][i] = 1;	
	}
	while (!q.empty()) {
		Node *o = q.front();
		q.pop();
		for (int i = 0; i < m; i++) {
			if (o->tr[i] != root) {
				o->tr[i]->suf = o->suf->tr[i];
				q.push(o->tr[i]);
			} else {
				o->tr[i] = o->suf->tr[i];
			}
			if (!o->end) {
				f[o->tr[i]->id][o->id] -= p[i];
			}
		}
	}
	vector<double> sol = solve(f);
	if (sol.empty()) {
		for (int i = 1; i <= n; i++) {
			puts("0.00");
		}
		return 0;
	}
	double sum = 0;
	for (int i = 1; i <= n; i++) {
		sum += sol[hsh[i]];
	}
	for (int i = 1; i <= n; i++) {
		printf("%.2lf\n", sol[hsh[i]] / sum);
	}
	return 0;
}

