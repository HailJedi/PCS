#include <iostream>
#include <algorithm>
#include <map>
#include <set>
using namespace std;

map<int, set< pair<int, int> > > P;
int dir[1<<15];

// 0 up, 1 down, 2 left, 3 right
const int trans[] = { 2, 3, 1, 0 };

void build(int n) {
    int m = 1;
    dir[0] = 3;
    for (int i = 1; i <= n; i++) {
        for (int j = m-1, k = m; j >= 0; j--, k++)
            dir[k] = trans[dir[j]];
        m <<= 1;
    }
    int x, y, px = 0, py = 0;
    P.clear();
    for (int i = 0; i < m; i++) {
        switch (dir[i]) {
            case 0: x = px << 1; y = py; break;
            case 1: x = px << 1; y = py - 1; break;
            case 2: x = (px << 1) - 1; y = py; break;
            case 3: x = (px << 1) + 1; y = py; break;
        }
        P[y].insert(make_pair(x, dir[i]));
        switch (dir[i]) {
            case 0: py++; break;
            case 1: py--; break;
            case 2: px--; break;
            case 3: px++; break;
        }
    }
    
}

int main() {
    int n;
    while (cin >> n && n) {
        build(n);
        
        int minx = 0x3f3f3f3f;
        for (map<int, set< pair<int, int> > >::iterator it = P.begin(); it != P.end(); ++it)
            for (set< pair<int, int> >::iterator jt = it->second.begin(); jt != it->second.end(); ++jt)
                minx = min(minx, jt->first);
        
        for (map< int, set< pair<int, int> > >::reverse_iterator it = P.rbegin(); it != P.rend(); ++it) {
            int x = minx;
            for (set< pair<int, int> >::iterator jt = it->second.begin(); jt != it->second.end(); ++jt) {
                while (x++ < jt->first) putchar(' ');
                if (jt->second == 0 || jt->second == 1)
                    putchar('|');
                else
                    putchar('_');
            }
            puts("");
        }
        puts("^");
    }
    return 0;
}
