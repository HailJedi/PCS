#include <vector>
#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

typedef vector<int> Denominations;

vector<Denominations> sets;

bool cmp(Denominations &lhs, Denominations &rhs) {
	if (lhs.size() != rhs.size()) return lhs.size() < rhs.size();
	for (int i = lhs.size()-1; i >= 0; i--)
		if (lhs[i] != rhs[i]) return lhs[i] < rhs[i];
	return true;
}

const int maxv = 100+5;
const int maxn = 10+2;
int S, N;
int ansv, ansid; 
int d[maxn*maxv];
Denominations self;
int kase;
int vis[maxn*maxv][maxn];

void print() {
	printf("max coverage =%4d :", ansv);
	for (int i = 0; i < sets[ansid].size(); i++)
		printf("%3d", sets[ansid][i]);
	puts("");
}

void update(int res, int id) {
	if (res > ansv) {
		ansv = res;
		ansid = id;
	}
}

void dp(int value, int amount) {
	d[value] = 1;
	if (amount == S) return;
	if (vis[value][amount] == kase) return;
	vis[value][amount] = kase;
	for (int i = 0; i < self.size(); i++)
		dp(value+self[i], amount+1);
}

int calc(int id) {
	self = sets[id];
	memset(d, 0, sizeof(d));
	dp(0, 0);
	int ans, v = S*self[self.size()-1];
	for(ans = 0; ans <= v && d[ans+1]; ans++);
	return ans;
}

void solve() {
	ansv = -1;
	for (int i = 0; i < N; i++) {
		kase++;
		int res = calc(i);
		update(res, i);
	}
	print();
}

void read() {
	scanf("%d", &N);
	sets.clear();
	for (int i = 1; i <= N; i++) {
		int n, d; scanf("%d", &n);
		Denominations _new;
		while(n--) {
			scanf("%d", &d);
			_new.push_back(d);
		}
		sets.push_back(_new);
	}
	sort(sets.begin(), sets.end(), cmp);
}

int main() {
	while (scanf("%d", &S) == 1 && S) {
		read();
		solve();
	}
	return 0;
}