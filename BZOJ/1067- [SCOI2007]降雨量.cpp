#include <bits/stdc++.h>

using namespace std;

const int N = 5e4+5;
const int M = 1e4+5;
int n, m, X, Y;
int R[N], mx[N*4];
map<int, int> id;

void init(int o, int l, int r) {
	if (l != r) {
		int mid = (l + r) >> 1;
		init(o << 1, l, mid);
		init(o << 1 | 1, mid + 1, r);
		mx[o] = max(mx[o << 1], mx[o << 1 | 1]);
	} else {
		mx[o] = R[l];
	}
}

int maxv(int o, int l, int r, int ql, int qr) {
	if (l > r) {
		return -2e9;
	}
	if (ql <= l && r <= qr) {
		return mx[o];
	} else {
		int mid = (l + r) >> 1;
		int ret = -2e9;
		if (mid >= ql) {
			ret = max(ret, maxv(o << 1, l, mid, ql, qr));
		} 
		if (mid + 1 <= qr) {
			ret = max(ret, maxv(o << 1 | 1, mid + 1, r, ql, qr));
		}
		return ret;
	}
}

vector<int> year;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> Y >> R[i];
		year.push_back(Y);
		id[Y] = i;
	}
	init(1, 1, n);
	cin >> m;
	while (m--) {
		cin >> Y >> X;
		int XX = *--lower_bound(year.begin(), year.end(), X);
		int YY = *upper_bound(year.begin(), year.end(), Y);
		int mx = maxv(1, 1, n, id[YY], id[XX]);
		// if (id[X] == 0 || X > year.back() || Y > year.back() || X < year[0] || Y < year[0]) {
		// 	cout << "maybe" << endl;
		// } else
		if (id[X] == 0) {
			cout << "maybe" << endl;
		} else
		if (mx >= R[id[X]]) {
			cout << "false" << endl;
		} else {
			if (id[X] - id[Y] != X - Y || mx < 0) {
				cout << "maybe" << endl;
			} else {
				cout << "true" << endl;
			}
		}
	}
	return 0;
}