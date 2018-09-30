#include <bits/stdc++.h>
#define N 100010
#define all(x) (x).begin(), (x).end()

using namespace std;

struct Node {
    Node *son[26];
    bool term;
    Node() {
        for (int i = 0; i < 26; i++) son[i] = NULL;
        term = false;
    }
};

using PNode = Node*;
PNode root = new Node();
char r[N];
int n;
using MSI = multiset<int>;
using PSI = MSI*;

void add() {
	Node *cur = root;
	char *t = r;
	while (*t != '\0') {
		int v = *t - 'a';
		if (cur->son[v] == NULL)
			cur->son[v] = new Node();
		cur = cur->son[v];
		t++;
	}
	cur->term = true;
}

PSI merge(PSI a, PSI b) {
	if (a->size() < b->size()) swap(a, b);
	for (auto e: *b)
		a->insert(e);
	delete(b);
	return a;
}

PSI calc(Node *cur, int d) {
	PSI ret = new MSI;
	for (int i = 0; i < 26; i++) {
		if (cur->son[i] != NULL) {
			auto s = calc(cur->son[i], d+1);
			ret = merge(ret, s);
		}
	}
	if (cur->term) ret->insert(d);
	else if (d) {
		ret->erase(prev(ret->end()));
		ret->insert(d);
	}
	return ret;
}

int main() {
	cin >> n;
	for (int i = 1; i <= n; i++) {
		scanf("%s", r);
		add();
	}
	auto ans = calc(root, 0);
	cout << accumulate(all(*ans), 0) << endl;
}