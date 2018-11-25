#include <cstdio>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cstring>
#include <vector>
#include <cmath>
using namespace std;

int score[20000][10];
int n;
int rnk[20000];

void input() {
    double t;
    for (int i = 1; i <= n; i++) {
        for (int k = 0; k <= 2; k++) {
            scanf("%lf", &t);
            score[i][k] = round(t * 100.0);
        }
    }
    for (int i = 1; i <= n; i++) scanf("%d", &rnk[i]);
}

int uper_bnd(int psn, int lst_scr, int flag) {
    int scr[8];
    int a = score[psn][0], b = score[psn][1], c = score[psn][2];
    scr[0] = 0; scr[1] = a; scr[2] = b; scr[3] = c;
    scr[4] = a + b; scr[5] = a + c; scr[6] = b + c;
    scr[7] = a + b + c;
    sort(scr, scr + 8);
    
    for (int i = 7; i >= 0; i--)
        if (scr[i] < lst_scr
            || (scr[i] == lst_scr && flag)) return scr[i];
    return -1;
}

int kase = 0;
void solve() {
    printf("Case %d: ", ++kase);
    
    int psn = rnk[1];
    int lst_scr = score[psn][0] + score[psn][1] + score[psn][2];
    for (int i = 2; i <= n && lst_scr >= 0; i++) {
        psn = rnk[i];
        lst_scr = uper_bnd(psn, lst_scr, rnk[i-1] < psn);
    }
    
    if (lst_scr < 0) printf("No solution\n");
    else printf("%.2f\n", (double)lst_scr / 100.0);
}

//#define LOCAL

int main() {
    
//#ifdef LOCAL
//    freopen("in", "r", stdin);
//    freopen("out.txt", "w", stdout);
//#endif // LOCAL
    
    while (scanf("%d", &n) == 1 && n) {
        input();
        solve();
    }
    return 0;
}