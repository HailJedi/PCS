#include <bits/stdc++.h>

using namespace std;

const int N = 750 + 5;

int A[N], B[N];
int n;

struct Item {
	int s, b;
	Item(int s, int b) : s(s), b(b) {}
	bool operator < (const Item &i) const {
		return s > i.s;
	}
};

void merge() {
	priority_queue<Item> q;
	for (int i = 1; i <= n; i++) {
		q.push(Item(A[i] + B[1], 1));
	}
	for (int i = 1; i <= n; i++) {
		Item it = q.top(); q.pop();
		A[i] = it.s;
		if (it.b < n) {
			q.push(Item(it.s - B[it.b] + B[it.b+1], it.b+1));
		}
	}
}

int main() {
//	freopen("read.in", "r", stdin);
//	freopen("write.out", "w", stdout);
	
	while (scanf("%d", &n) == 1) {
		for (int i = 1; i <= n; i++) {
			scanf("%d", &A[i]);
		}
		sort(A+1, A+1+n);
		for (int i = 2; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				scanf("%d", &B[j]);
			}
			sort(B+1, B+1+n);
			merge();
		}
		printf("%d", A[1]);
		for (int i = 2; i <= n; i++) {
			printf(" %d", A[i]);
		}
		puts("");
	}
	return 0;
}

