#include <cstdio>
#include <map>
#include <string>
using namespace std;

const int maxn = 60000;

int tot;
char sym[5*maxn], *p;

struct Node {
	string s;
	int hash, left, right;
	bool operator < (const Node &rhs) const {
		if (hash != rhs.hash) return hash < rhs.hash;
		if (left != rhs.left) return left < rhs.left;
		return right < rhs.right;
	}
} node[maxn];

map<Node, int> dic;

int solve() {
	int id = tot++;
	Node &u = node[id];
	u.left = u.right = -1;
	u.hash = 0; u.s = "";
	while (isalpha(*p)) {
		u.hash = u.hash * 27 + *p - 'a'; // ??? 
		u.s.push_back(*p);
		p++;
	}

	if (*p == '(') {
		p++; u.left = solve();
		p++; u.right = solve();
		p++;
	}

	if (dic.count(u)) {
		tot--;
		return dic[u];
	}
	return dic[u] = id;
}

int done[maxn];
int kase;

void print(int id) {
	if (done[id] == kase)
		printf("%d", id+1);
	else {
		done[id] = kase;
		Node &u = node[id];
		printf("%s", u.s.c_str());
		if (~u.left) {
			putchar('(');
			print(u.left);
			putchar(',');
			print(u.right);
			putchar(')');
		}
	}
}

int main() {
	int T; scanf("%d", &T);
	for (kase = 1; kase <= T; kase++) {
		scanf("%s", sym);
		dic.clear();
		tot = 0;
		p = sym;
		print(solve());
		puts("");
	}
	return 0;
}