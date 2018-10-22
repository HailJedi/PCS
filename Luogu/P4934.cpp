/*
Created 2018-10-22
*/

#include <bits/stdc++.h>

using namespace std;

const int N = 1000000 + 5;
const int K = 21;

int n, k;
vector<int> g[N];
bool valid[1<<K];
int in[1<<K];
int a[N];

int main() {
//	freopen("read.in", "r", stdin);
//	freopen("write.out", "w", stdout);
	scanf("%d %d", &n, &k);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
		valid[a[i]] = true;
	}
	for (int i = 1; i <= n; i++) {
		int u = a[i];
		for (int j = 0; j < K; j++) {
			if (u & (1 << j)) {
				int v = u ^ (1 << j);
				g[u].push_back(v);
				in[v]++;
			}
		}
	}
	vector< vector<int> > ans;
	vector<int> st;
	queue<int> q;
	for (int i = 1; i <= n; i++) {
		int u = a[i];
		if (!in[u]) {
			q.push(u);
			st.push_back(u);
		}
	}
	if (!st.empty()) {
		ans.push_back(st);
	}
	while (!q.empty()) {
		st.clear();
		queue<int> useless;
		int sz = q.size();
		while (sz--) {
			int u = q.front();
			q.pop();
			for (auto v: g[u]) {
				in[v]--;
				if (in[v] == 0) {
					if (valid[v]) {
						st.push_back(v);
						q.push(v);
					} else {
						useless.push(v);
					}
				}
			}
		}
		while (!useless.empty()) {
			int u = useless.front();
			useless.pop();
			for (auto v: g[u]) {
				in[v]--;
				if (in[v] == 0) {
					if (valid[v]) {
						st.push_back(v);
						q.push(v);
					} else {
						useless.push(v);
					}
				}
			}
		}
		if (!st.empty()) {
			ans.push_back(st);
		}
	}
	printf("1\n");
	printf("%d\n", (int)ans.size());
	for (auto e: ans) {
		printf("%d ", (int)e.size());
		for (auto v: e) {
			printf("%d ", v);
		}
		printf("\n");
	}
	return 0;
}
