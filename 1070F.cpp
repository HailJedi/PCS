/*
Created 2018-10-22
"Debate"
*/

#include <bits/stdc++.h>

using namespace std;

const int N = 400000 + 5;

struct Spec {
	int a;
	int al, bb;
	Spec(int al, int bb, int a) : al(al), bb(bb), a(a) {}
	bool operator < (const Spec &sp) const {
		return a > sp.a;
	}
};

vector<Spec> st[4];
int n;
map<string, int> mp;

int extract(set<Spec> &st, int &alice, int &bob) {
	int ret = st.begin()->a;
	alice += st.begin()->al;
	bob += st.begin()->bb;
	st.erase(st.begin());
	return ret;
}

int main() {
	freopen("read.in", "r", stdin);
	mp["00"] = 0;
	mp["01"] = 1;
	mp["10"] = 2;
	mp["11"] = 3;
	cin >> n;
	for (int i = 1; i <= n; i++) {
		string str;
		int a;
		cin >> str >> a;
		int num = mp[str];
		st[num].push_back(Spec(num / 2, num % 2, a));
	}
	int ans = 0;
	int alice = 0, bob = 0, cnt = 0;
	while (!st[3].empty()) {
		ans += extract(st[3], alice, bob);
		cnt++;
	}
	while (!st[1].empty() && !st[2].empty()) {
		ans += extract(st[1], alice, bob);
		ans += extract(st[2], alice, bob);
		cnt += 2;
	}
	while (!st[1].empty()) {
		st[0].push_back(*st[1].begin());
		st[1].erase(st[1].begin());
	}
	while (!st[2].empty()) {
		st[0].push_back(*st[2].begin());
		st[2].erase(st[2].begin());
	}
	int tmp = 0;
	while (!st[0].empty()) {
		tmp = extract(st[0], alice, bob);
		cnt++;
		cout << alice << ' ' << bob << ' ' << cnt << endl;
		if (2 * alice >= cnt && 2 * bob >= cnt) {
			ans += tmp;
		} else {
			break;
		}
	}
	printf("%d\n", ans);
	return 0;
}
