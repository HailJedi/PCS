
#include <cstring>
#include <iostream>
using namespace std;

const int maxn = 64;
unsigned long long maxv, minv, k;
unsigned long long dp[maxn+1][maxn+1];
int O[maxn+1], Z[maxn+1], digit[maxn+1];
int cntz, cnto, n, d, kase;

bool CanReceiveZero(int z, int o) {
    return z+1 <= cntz && (o == cnto || O[o+1]+d >= Z[z+1]);
}

bool CanReceiveOne(int z, int o) {
    return o+1 <= cnto && (z == cntz || Z[z+1]+d >= O[o+1]);
}

void init() {
    for (int i = n; i >= 1; i--)
        { digit[i] = k % 2; k /= 2; }
    
    cnto = cntz = 0;
    for (int i = 1; i <= n; i++) {
        if (digit[i] == 1) O[++cnto] = i;
        else Z[++cntz] = i;
    }
}

void DP() {
    memset(dp, 0, sizeof(dp));
    dp[0][0] = 1;
    for (int z = 0; z <= cntz; z++)
        for (int o = 0; o <= cnto; o++) {
            if (CanReceiveOne(z, o)) dp[z][o+1] += dp[z][o];
            if (CanReceiveZero(z, o)) dp[z+1][o] += dp[z][o];
        }
    cout << dp[cntz][cnto] << ' ';
}

void Greedy() {
    minv = maxv = 0;
    int z, o;
    
    z = o = 0;
    while (z < cntz || o < cnto) {
        if (CanReceiveOne(z, o)) { maxv = maxv * 2 + 1; o++; }
        else { maxv = maxv * 2; z++; }
    }
    
    z = o = 0;
    while (z < cntz || o < cnto) {
        if (CanReceiveZero(z, o)) { minv = minv * 2; z++; }
        else { minv = minv * 2 + 1; o++; }
    }
    cout << minv << ' ' << maxv << endl;
}

int main() {
    ios::sync_with_stdio(false);
    while (cin >> n >> d >> k) {
        init();
        cout << "Case " << ++kase << ": ";
        DP();
        Greedy();
    }
    return 0;
}


/*

// UVa1228 Integer Transmission
// Rujia Liu
#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 64;

int n, d, K[maxn];
unsigned long long f[maxn+1][maxn+1];

int zcnt = 0, ocnt = 0;
int Z[maxn], O[maxn]; // z[i] is the i-th zero from left (0-based)

// now we received i zeros and j ones. Can we receive another zero at the next time?
bool can_receive_zero(int i, int j) {
    return i+1 <= zcnt && (j == ocnt || O[j]+d >= Z[i]);
}

bool can_receive_one(int i, int j) {
    return j+1 <= ocnt && (i == zcnt || Z[i]+d >= O[j]);
}

unsigned long long minv, maxv;

void greedy() {
    minv = maxv = 0;
    int i = 0, j = 0;
    while(i < zcnt || j < ocnt) {
        if(can_receive_zero(i, j)) { i++; minv = minv * 2; }
        else { j++; minv = minv * 2 + 1; }
    }
    i = j = 0;
    while(i < zcnt || j < ocnt) {
        if(can_receive_one(i, j)) { j++; maxv = maxv * 2 + 1; }
        else { i++; maxv = maxv * 2; }
    }
}

void solve() {
    // compute Z and O
    ocnt = zcnt = 0;
    for(int i = 0; i < n; i++)
        if(K[i] == 1) O[ocnt++] = i;
        else Z[zcnt++] = i;
    
    // greedy to get minv, maxv
    greedy();
    
    // dp
    memset(f, 0, sizeof(f));
    f[0][0] = 1;
    for(int i = 0; i <= zcnt; i++)
        for(int j = 0; j <= ocnt; j++) {
            if(can_receive_zero(i, j)) f[i+1][j] += f[i][j];
            if(can_receive_one(i, j)) f[i][j+1] += f[i][j];
        }
    cout << f[zcnt][ocnt] << " " << minv << " " << maxv << "\n";
}

int main() {
    int kase = 0;
    unsigned long long k;
    while(cin >> n >> d >> k) {
        for(int i = 0; i < n; i++) {
            K[n-i-1] = k % 2; k /= 2;
        }
        cout << "Case " << ++kase << ": ";
        solve();
    }
    return 0;
}
*/
