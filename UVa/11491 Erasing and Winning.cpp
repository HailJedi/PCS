/*
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstdio>
using namespace std;

const int maxd = 100010;
int d, e;
char dig[maxd], ans[maxd];

int last;

char max_elem(int L, int R) {
    int mx = '0';
    for (int i = L; i < R; i++)
        if (dig[i] > mx) { mx = dig[i]; last = i; }
    return mx;
}

int main()
{
    //freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    
    ios::sync_with_stdio(false);
    while (cin >> d >> e && d && e) {
        cin >> dig;
        last = -1;
        int remain = d - e;
        for (int i = 1; i <= remain; i++)
            ans[i] = max_elem(last+1, d - remain + i);
        for (int i = 1; i <= remain; i++)
            cout << ans[i]; cout << endl;
    }
    return 0;
}
*/

#include <cstdio>
using namespace std;
int main() {
    int d, e; char ans[100010];
    while (~scanf("%d%d", &d, &e) && d && e) {
        getchar(); int it = 0; ans[0] = '0';
        for (int i = 0; i < d; i++) {
            char c = getchar();
            while (it > 0 && ans[it] < c && it + d - i > d - e) it--;
            if (it < d - e) ans[++it] = c;
        }
        ans[++it] = '\0'; puts(ans+1);
    }
    return 0;
}
