#include <iostream>
#include <queue>
#include <string>
#include <cstdio>
#define maxn (20+1)
#define maxm (100+5)
#define INF 0x3f3f3f3f
using namespace std;

int N, M;
typedef pair<int, int> Pair;

struct Patch {
	int pres, abst, fix, intro, cost;
	Patch(int p = 0, int a = 0, int f = 0, int i = 0, int c = 0) 
	: pres(p), abst(a), fix(f), intro(i), cost(c) {}
} patch[maxm];

int Usable(int st, int pt) {
	const int p = patch[pt].pres;
	const int a = patch[pt].abst;
	const int f = patch[pt].fix;
	const int i = patch[pt].intro;

	if ((p & st) != p) return -1;
	if ((a & st) != 0) return -1;
	int new_st = st;
	new_st &= (~f);
	new_st |= i;
	return new_st;
}

int dist[1<<maxn];

bool update(int st, int c) {
	bool ok = false;
	if (c < dist[st]) {
		dist[st] = c;
		ok = true;
	}
	return ok;
}

int Dijkstra(int S) {
	priority_queue<Pair, vector<Pair>, greater<Pair> > que;
	que.push(make_pair(0, S));
	for (int i = 0; i < 1<<N; i++) dist[i] = INF;
	dist[S] = 0;

	while (!que.empty()) {
		Pair u = que.top(); que.pop();
		int status = u.second, cost = u.first;
		for (int i = 1; i <= M; i++) {
			int new_st = Usable(status, i);
			if (new_st != -1) {
				int new_cost = cost + patch[i].cost;
				if (update(new_st, new_cost)) {
					que.push(make_pair(dist[new_st], new_st));
				}
			}
		}
	}

	return dist[0];
}

int main() {
	int kase = 0;
	while (cin >> N >> M && N) {
		string str;
		for (int i = 1; i <= M; i++) {
			patch[i] = Patch(0, 0, 0, 0, 0);
			cin >> patch[i].cost;
			cin >> str;
			for (int j = 0; j < str.length(); j++) {
				if (str[j] == '+') patch[i].pres |= (1<<j);
				if (str[j] == '-') patch[i].abst |= (1<<j);
			}
			cin >> str;
			for (int j = 0; j < str.length(); j++) {
				if (str[j] == '+') patch[i].intro |= (1<<j);
				if (str[j] == '-') patch[i].fix |= (1<<j);
			}
		}
		int ans = Dijkstra((1<<N)-1);
		cout << "Product " << ++kase << endl;
		if (ans < INF) cout << "Fastest sequence takes " << ans << " seconds.";
		else cout << "Bugs cannot be fixed.";
		cout << endl << endl;
	}
	return 0;
}
