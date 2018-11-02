#include <bits/stdc++.h>

using namespace std;

const int N = 3e4+5;
int a[N], X[N], Y[N];
int ans1[N], ans2[N];

struct Treap {
	static vector<Treap*> bin;
	Treap *ls, *rs;
	int val, key, size;
	int mark1, mark2;

	void* operator new(size_t, int x) {
		Treap *re;
		if (!bin.empty()) {
			re = bin.back();
			bin.pop_back();
		} else {
			static Treap pool[N], *c = pool;
			re = c++;
		}
		re->ls = re->rs = 0x0;
		re->val = x;
		re->key = rand();
		re->size = 1;
		re->mark1 = re->mark2 = 0;
		return re;
	}

	void operator delete(void *p) {
		bin.push_back((Treap*)p);
	}

	void get_mark(int m1, int m2) {
		ans1[val] = max(ans1[val], m1);
		ans2[val] = max(ans2[val], m2);
		mark1 = max(mark1, m1);
		mark2 = max(mark2, m2);
	}

	void push_down() {
		if (!mark1 && !mark2) {
			return;
		}
		if (ls) {
			ls->get_mark(mark1, mark2);
		}
		if (rs) {
			rs->get_mark(mark1, mark2);
		}
		mark1 = mark2 = 0;
	}

	void push_up() {
		size = 1;
		if (ls) {
			size += ls->size;
		}
		if (rs) {
			size += rs->size;
		}
	}

	friend void zig(Treap *&x) {
		Treap *y = x->ls;
		x->push_down();
		y->push_down();
		x->ls = y->rs;
		y->rs = x;
		x = y;
		x->rs->push_up();
		x->push_up();
	}

	friend void zag(Treap *&x) {
		Treap *y = x->rs;
		x->push_down();
		y->push_down();
		x->rs = y->ls;
		y->ls = x;
		x = y;
		x->ls->push_up();
		x->push_up();
	}

	friend void insert(Treap *&x, int y) {
		if (!x) {
			x = new (y)Treap;
			return;
		}
		x->push_down();
		if (a[y] < a[x->val] || (a[y] == a[x->val] && y < x->val)) {
			insert(x->ls, y);
			if (x->ls->key > x->key) {
				zig(x);
			}
		} else {
			insert(x->rs, y);
			if (x->rs->key > x->key) {
				zag(x);
			}
		}
		x->push_up();
	}

	friend void delet(Treap *&x, int y) {
		x->push_down();
		if (a[y] < a[x->val] || (a[y] == a[x->val] && y < x->val)) {
			delet(x->ls, y);
		} else
		if (a[y] > a[x->val] || (a[y] == a[x->val] && y > x->val)) {
			delet(x->rs, y);
		} else
		if (!x->ls) {
			delete x, x = x->rs;
		} else
		if (!x->rs) {
			delete x, x = x->ls;
		} else {
			zag(x);
			delet(x->ls, y);
			if (x->ls && x->ls->key > x->key) {
				zig(x);
			}
		}
		if (x) {
			x->push_up();
		}
	}

	friend int get_max(Treap *x) {
		if (!x->rs) {
			return a[x->val];
		}
		return get_max(x->rs);
	}
};
vector<Treap*> Treap::bin;

namespace Hash_set {
	struct List {
		int x, y;
		Treap *pointer;
		List *next;
		List(int x, int y, List *p) :
		x(x), y(y), pointer(0x0), next(p) {}
	} *head[349][353];

	Treap *& Hash(int x, int y) {
		int pos1 = ((x % 349) + 349) % 349;
		int pos2 = ((y % 353) + 353) % 353;
		for (List *temp = head[pos1][pos2]; temp; temp = temp->next) {
			if (temp->x == x && temp->y == y) {
				return temp->pointer;
			}
		}
		return (head[pos1][pos2] = new List(x, y, head[pos1][pos2]))->pointer;
	}
} using namespace Hash_set;

int n, m, p, x, y;

void insert(int x) {
	Treap *&root = Hash(X[x], Y[x]);
	if (root) {
		ans1[x] = max(ans1[x], get_max(root));
		root->get_mark(a[x], 0);
	}
	insert(root, x);
	root->get_mark(0, root->size-1);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> a[i] >> X[i] >> Y[i];
		insert(i);
	}
	cin >> m;
	for (int i = 1; i <= m; i++) {
		cin >> p >> x >> y;
		delet(Hash(X[p], Y[p]), p);
		X[p] = x, Y[p] = y;
		insert(x);
	}
	for (int i = 1; i <= n; i++) {
		delet(Hash(X[i], Y[i]), i);
	}
	for (int i = 1; i <= n; i++) {
		cout << (long long)ans1[i] * ans2[i] << endl;
	}
	return 0;
}