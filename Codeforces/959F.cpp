#include <bits/stdc++.h>
#define mp make_pair
#define pb push_back
#define sz(x) x.size()
#define fs first
#define sc second

using namespace std;

const int N = 100010;
const int A = (1<<21);
const int mod = 1000000007;

int a[N], ans[N];
int n, q, l, x;
bool inset[A];
vector< int > st;
vector< pair<int, int> > off[N];

int main() {
	scanf("%d %d", &n, &q);
	for (int i = 1; i <= n; i++) 
		scanf("%d", &a[i]);

	for (int i = 1; i <= q; i++) {
		scanf("%d %d", &l, &x);
		off[l].pb(mp(x, i));
	}

	st.pb(0);
	inset[0] = true;
	int p = 1;
	
	for (int i = 1; i <= n; i++) {
		if (inset[a[i]]) (p <<= 1) %= mod;
		else {
			int sz = sz(st);
			for (int j = 0; j < sz; j++) {
				int e = st[j]^a[i];
				st.pb(e);
				inset[e] = true;
			}
		}
		for (int j = 0; j < sz(off[i]); j++)
			ans[off[i][j].sc] = p * inset[off[i][j].fs] % mod;
	}
	for (int i = 1; i <= q; i++)
		printf("%d\n", ans[i]);

	return 0;
}