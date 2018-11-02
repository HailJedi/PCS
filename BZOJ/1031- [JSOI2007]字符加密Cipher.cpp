#include <iostream>
#include <cstdio>
#include <string>
#include <algorithm>

using namespace std;

typedef pair<int, int> Pair;
typedef pair<Pair, int> Triple;

#define mp(x, y) make_pair(x, y)
#define left(x) x.first.first
#define right(x) x.first.second

const int maxn = 1000010;
string T;
int n;
int sa[maxn], rnk[maxn];
Triple tmp[maxn];

bool cmp_sa(int x, int y) {
    return T[x] < T[y];
} 

bool cmp_rnk(Triple x, Triple y) {
    if (left(x) != left(y)) return left(x) < left(y);
    return right(x) < right(y);
}

void calc_SA(string &s) {
    for (int i = 0; i < n; i++) sa[i] = i;
    sort(sa, sa+n, cmp_sa);	
    int p = 0;
    rnk[sa[0]] = 0;
    for (int i = 1; i < n; i++) rnk[sa[i]] = T[sa[i]] == T[sa[i-1]] ? p : ++p;
    // for (int i = 0; i < n; i++) cout << rnk[i] << ' ';
        // puts("");
    // for (int i = 0; i < n; i++) cout << (char)T[sa[i]] << ' ';
    // puts("");

    for (int k = 1; k <= n; k <<= 1) {
        for (int i = 0; i < n; i++)
            tmp[i] = mp(mp(rnk[i], i+k < n ? rnk[i+k] : -1), i);
        sort(tmp, tmp+n, cmp_rnk);
        // for (int i = 0; i < n; i++) 
            // cout << left(tmp[i]) << ' ' << right(tmp[i]) << endl;
        int p = 0;
        rnk[tmp[0].second] = 0;
        for (int i = 1; i < n; i++)
            rnk[tmp[i].second] = tmp[i].first == tmp[i-1].first ? p : ++p;
    }

    // for (int i = 0; i < n; i++) cout << rnk[i] << ' ';
        // puts("");
    for (int i = 0; i < n; i++) sa[rnk[i]] = i;
    // for (int i = 0; i < n; i++) cout << sa[i] << ' ';
        // puts("");
}

int main() {

    cin >> T;
    T = T + T;
    // cout << T << endl;

    n = T.length();
    // cout << n << endl;

    calc_SA(T);
    // build_SA(T);

    for (int i = 0; i < n; i++)
        if (sa[i] < n/2) cout << T[sa[i]+n/2-1];
    puts("");

    return 0;
}