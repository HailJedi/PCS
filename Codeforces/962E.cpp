#include <cstdio>
#include <algorithm>
#include <map>

using namespace std;

const int maxe = 10000000;
const int maxn = 200010;

int pos[maxn];
char cty[maxn];
int u[maxe], v[maxe], w[maxe];
int rnk[maxe];

bool cmp(int x, int y) {
	return w[x] < w[y];
}

int n;
map<char, int> lstidx;
int ct;

void Link(int uu, int vv) {
	u[++ct] = uu; 
	v[ct] = vv;;
	w[ct] = pos[vv] - pos[uu];
	rnk[ct] = ct;
}

int fa[maxn];
int dep[maxn];

int Find(int x) {
	return x == fa[x] ? x : Find(fa[x]);
}

int main() {
	// puts("ready");
	scanf("%d", &n);
	lstidx['P'] = lstidx['R'] = lstidx['B'] = 0;
	for (int i = 1; i <= n; i++) {
		fa[i] = i; dep[i] = 1;
		scanf("%d %c", &pos[i], &cty[i]);
		if (lstidx[cty[i]])
			Link(lstidx[cty[i]], i);
		lstidx[cty[i]] = i;
		if (cty[i] != 'P') {
			if (lstidx['P'])
				Link(lstidx['P'], i);
		} else {
			if (lstidx['R']) 
				Link(lstidx['R'], i);
			if (lstidx['B']) 
				Link(lstidx['B'], i);
		}
	}

	sort(rnk+1, rnk+1+ct, cmp);

	// for (int i = 0; i < ct; i++) {
		// printf("Edge #%d connects position %d with position %d\n", i, edge[i].u, edge[i].v);
		// printf("In which there are country %c and country %c\n", city[edge[i].u].cty, city[edge[i].v].cty);
	// }

	int cost = 0, cnt = 0;
	for (int i = 1; i <= ct && cnt < n-1; i++) {
		int fu = Find(u[i]);
		int fv = Find(v[i]); 
		if (fu != fv) {
			if (dep[fu] == dep[fv]) 
				fa[fu] = fv;
			else if (dep[fu] < dep[fv]) {
				fa[fu] = fv;
				dep[fv]++;
			} else {
				fa[fv] = fu;
				dep[fu]++;
			}
			cost += w[i];
			cnt++;
		}
	}
	printf("%d\n", cost);
	return 0;
}