#include <bits/stdc++.h>

using namespace std;

const int N = 150000 + 5;

struct Data {
	int id, rk, pos;
	Data(int id = 0, int rk = 0, int pos = 0) : id(id), rk(rk), pos(pos) {}
	bool operator < (const Data &d) const {
		if (rk != d.rk) {
			return rk > d.rk;
		}
		return pos < d.pos;
	}
} data[N];

int main() {
	int n;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d %d", &data[i].id, &data[i].rk);
		data[i].pos = i;
	}
	sort(data+1, data+1+n);
	for (int i = 1; i <= n; i++) {
		printf("%d %d\n", data[i].id, data[i].rk);
	}
	return 0;
}