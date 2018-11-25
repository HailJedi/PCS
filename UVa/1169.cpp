#include <bits/stdc++.h>

using namespace std;

const int N = 1e5+5;

int x[N], y[N], w[N];
int totDist[N], totWeight[N];
int f[N];

struct DS {
	deque< pair<int, int> > q;
	bool del[N];

	void append(int pos, int val) {
		while (!q.empty() && val <= q.back().second) {
			q.pop_back();
		}
		q.push_back(make_pair(pos, val));
	}
	
	void popFront() {
		q.pop_front();
	}

	int frontIdx() {
		return q.front().first;
	}

	int min_val() {
		return q.front().second;
	}	

	void clear() {
		while (!q.empty()) {
			q.pop_front();
		}
	}
} ds;

int main() {
//	freopen("read", "r", stdin);
//	freopen("write", "w", stdout);
	
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	
	int T, C, n;
	cin >> T;
	while (T--) {
		cin >> C >> n;
		for (int i = 1; i <= n; i++) {
			cin >> x[i] >> y[i];
			totDist[i] = totDist[i-1] + abs(x[i] - x[i-1]) + abs(y[i] - y[i-1]);
			cin >> w[i];
			totWeight[i] = totWeight[i-1] + w[i];
		}
		ds.clear();
		ds.append(0, 0);
		for (int i = 1; i <= n; i++) {
			while (totWeight[i] - totWeight[ds.frontIdx()] > C) {
				ds.popFront();
			}
			f[i] = ds.min_val() + x[i] + y[i] + totDist[i];
			ds.append(i, f[i] + x[i+1] + y[i+1] - totDist[i+1]);
		}
		cout << f[n] << endl;
		if (T) {
			cout << endl;
		}
	}
	return 0;
}