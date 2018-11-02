#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

#define maxn 10010
#define maxm 50010

struct DirectedGraph {
	int hd[maxn], nxt[maxm];
	int fm[maxm], to[maxm];
	int ct;

	DirectedGraph() {
		memset(hd, 0, sizeof(hd));
		memset(nxt, 0, sizeof(nxt));
		memset(fm, 0, sizeof(fm));
		memset(to, 0, sizeof(to));
		ct = 0;
	}

	void Link(int u, int v) {
		fm[++ct] = u; to[ct] = v;
		nxt[ct] = hd[u];
		hd[u]= ct;
	}

} G, Gt;

int f[maxn], d[maxn];
int ft, dt;

void CalcF(int u) {
	d[u] = ++dt;
	for (int i = G.hd[u]; i; i = G.nxt[i]) {
		int v = G.to[i];
		if (!d[v]) CalcF(v);
	}
	f[u] = ++ft;
}	

int N, M;

void CalcF() {
	for (int i = 1; i <= N; i++) 
		if (!d[i]) CalcF(i);
}

int id;
int nlist[maxn];

bool cmp(int x, int y) {
	return f[x] > f[y];
}

int mpid[maxn];
int in[maxn], out[maxn];
int siz[maxn];

void Map(int u, int id) {
	mpid[u] = id;
	siz[id]++;
	for (int i = Gt.hd[u]; i; i = Gt.nxt[i]) {
		int v = Gt.to[i];
		if (!mpid[v]) Map(v, id);
		else if (mpid[v] != id) {
			// Gscc.Link(mpid[v], id);
			in[id]++; out[mpid[v]]++;
		}
	}
}

void Map() {
	for (int i = 1; i <= N; i++)
		nlist[i] = i;
	sort(nlist+1, nlist+1+N, cmp);
	for (int i = 1; i <= N; i++)
		if (!mpid[nlist[i]]) Map(nlist[i], ++id);
}

void AnalyseSCC() {

	if(id == 1) {
		printf("%d\n", siz[1]);
		return;
	}

	for (int i = 1; i <= id; i++)
		if (!in[i] && !out[i]) {
			puts("0"); return;
		}

	// printf("there exist %d SCCs total\n", id);
	// printf("one has size %d, the other has size %d\n", siz[1], siz[2]);
	// printf("SCC #1 has in degree %d, out degree %d\n", in[1], out[1]);
	// printf("SCC #2 has in degree %d, out degree %d\n", in[2], out[2]);

	int ans = 0;
	for (int i = 1; i <= id; i++) {
		if (!out[i]) {
			if (ans) {
				puts("0");
				return;
			}
			ans = siz[i];
		}
	}

	printf("%d\n", ans);
}

void Read() {
	scanf("%d %d", &N, &M);
	int u, v;
	for (int i = 1; i <= M; i++) {
		scanf("%d %d", &u, &v);
		G.Link(u, v);
		Gt.Link(v, u);
	}
}

int main() {

	Read();

	CalcF();

	Map();

	AnalyseSCC();	

	return 0;
}