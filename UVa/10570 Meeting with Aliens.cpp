#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int n;
int alien[500<<1];
int cpy[500<<1];

int main()
{
    // freopen("in.txt", "r", stdin);
    // freopen("out.txt", "w", stdout);
    
    while (cin >> n && n) {
        for (int i = 0; i < n; i++) { cin >> alien[i]; alien[n+i] = alien[i]; }
        
        int ans = 0x3f3f3f3f, tmp;
        memcpy(cpy, alien, sizeof(alien));
        
        for (int c = 1; c <= 2; c++) {
            reverse(cpy, cpy+2*n);
            for (int i = 0; i < n; i++) {
                memcpy(alien, cpy, sizeof(cpy));
                tmp = 0;
                for (int j = i; j < i + n; j++) {
                    const int srch = j - i + 1;
                    int pos;
                    for (int k = j; true; k++)
                        if (alien[k] == srch) { pos = k; break; }
                    if (pos != j) { swap(alien[j], alien[pos]); tmp++; }
                }
                ans = min(ans, tmp);
            }
        }
        cout << ans << endl;
    }
    return 0;
}

