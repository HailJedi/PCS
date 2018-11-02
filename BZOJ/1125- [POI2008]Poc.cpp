#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;

const int L = 110;
const int N = 1e3+5;
const int B = 131;

int ans[N];

struct Treap {
	static queue<Treap*> bin;
	Treap *ls, *rs;
	int val, key, sz, mark;

	void *operator new (size_t, int x) {
		Treap *ret;
		if (bin.size()) {
			ret = bin.front();
			bin.pop();
		} else {
			static Treap pool[N], *c = pool;
			ret = c++;
		}
		ret -> ls = ret -> rs = 0x0;
		ret -> val = x;
		ret -> key = rand();
		ret -> sz = 1;
		ret -> mark = 0;
		return ret;
	}

	void operator delete(void *p) {
		bin.push((Treap*)p);
	}

	void get_mark(int x) {
		ans[val] = max(ans[val], x);
		mark = max(mark, x);
	}

	void push_up() {
		sz = 1;
		if (ls) sz += ls -> sz;
		if (rs) sz += rs -> sz;
	}

	void push_down() {
		if (!mark) {
			return;
		}
		if (ls) {
			ls -> get_mark(mark);
		}
		if (rs) {
			rs -> get_mark(mark);
		}
		mark = 0;
	}

	friend void zig(Treap *&x) {
		Treap *y = x -> ls;
		x -> push_down();
		y -> push_down();
		x -> ls = y -> rs;
		y -> rs = x;
		x = y;
		x -> push_up();
		x -> rs -> push_up();
	}

	friend void zag(Treap *&x) {
		Treap *y = x -> rs;
		x -> push_down();
		y -> push_down();
		x -> rs = y -> ls;
		y -> ls = x;
		x = y;
		x -> push_up();
		x -> ls -> push_up();
	}

	friend void insert(Treap *&x, int y) {
		if (!x) {
			x = new(y)Treap;
			return;
		}
		x -> push_down();
		if (y < x -> val) {
			insert(x -> ls, y);
			if (x -> ls -> key > x -> key) {
				zig(x);
			}
		} else {
			insert(x -> rs, y);
			if (x -> rs -> key > x -> key) {
				zag(x);
			}
		}
		x -> push_up();
	}

	friend void delet(Treap *&x, int y) {
		x -> push_down();
		if (y < x -> val) {
			delet(x -> ls, y);
		} else 
		if (y > x -> val) {
			delet(x -> rs, y);
		} else {
			if (!x -> ls) {
				delete x, x = x -> rs;
			} else 
			if (!x -> rs) {
				delete x, x = x -> ls;
			} else {
				zag(x);
				delet(x -> ls, y);
				if (x -> ls && x -> ls -> key > x -> key) {
					zig(x);
				}
			}
		}
		if (x) {
			x -> push_up();
		}
	}
};

queue<Treap*> Treap::bin;

int n, m, l;
ull power[L], Hsh[N];

namespace Hash_set {
	struct List {
		ull hash;
		Treap *pointer;
		List *next;
		List(ull x, List *l) :
			hash(x), pointer(0x0), next(l) {}
	} *head[10301];
	
	Treap *& Hash(ull hash) {
		int pos = hash % 10301;
		for (List *t = head[pos]; t; t = t -> next) {
			if (t -> hash == hash) {
				return t -> pointer;
			}
		}
		return (head[pos] = new List(hash, head[pos])) -> pointer;
	}
} using namespace Hash_set;

void insert(int x) {
	Treap *&root = Hash(Hsh[x]);
	insert(root, x);
	root -> get_mark(root -> sz);
}

void delet(int x) {
	Treap *&root = Hash(Hsh[x]);
	delet(root, x);
}

string s[N];
int x_1, x_2, y_1, y_2;

int main() {
	srand(time(NULL));
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	cin >> n >> l >> m;
	for (int i = power[0] = 1; i <= l; i++) {
		power[i] = power[i-1] * B;
	}
	for (int i = 1; i <= n; i++) {
		cin >> s[i];
		for (int j = 0; j < l; j++) {
			(Hsh[i] *= B) += s[i][j];
		}
		insert(i);
	}
	for (int i = 1; i <= m; i++) {
		cin >> x_1 >> y_1 >> x_2 >> y_2;
		y_1--, y_2--;
		delet(x_1);
		if (x_1 != x_2) {
			delet(x_2);
		}
		Hsh[x_1] -= s[x_1][y_1] * power[l-y_1-1];
		Hsh[x_2] -= s[x_2][y_2] * power[l-y_2-1];
		swap(s[x_1][y_1], s[x_2][y_2]);
		Hsh[x_1] += s[x_1][y_1] * power[l-y_1-1];
		Hsh[x_2] += s[x_2][y_2] * power[l-y_2-1];
		insert(x_1);
		if (x_1 != x_2) {
			insert(x_2);
		}
	}
	for (int i = 1; i <= n; i++) {
		delet(i);
	}
	for (int i = 1; i <= n; i++) {
		cout << ans[i] << endl;
	}
	return 0;
}