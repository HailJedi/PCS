#include <bits/stdc++.h>

using namespace std;

const int maxn = 150010;

typedef long long ll;

struct Repair {
	ll T1, T2;
	bool operator < (const Repair &rhs) const {
		return T1 < rhs.T1;
	}
} rep[maxn];

bool cmp(Repair a, Repair b) {
	if (a.T2 != b.T2) return a.T2 < b.T2;
	return a.T1 < b.T1;
}

int n;

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%lld %lld", &rep[i].T1, &rep[i].T2);
	}
	sort(rep+1, rep+1+n, cmp);

	priority_queue<Repair> que;

	ll acum = 0;
	for (int i = 1; i <= n; i++) {
		if (acum + rep[i].T1 > rep[i].T2) {
			if (que.top().T1 > rep[i].T1) {
				(acum -= que.top().T1) += rep[i].T1;
				que.pop();
				que.push(rep[i]);
			}
		} else {
			que.push(rep[i]);
			acum += rep[i].T1;
		}
	}

	printf("%lld\n", (ll)que.size());

	return 0;
}