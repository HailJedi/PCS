#include <cstdio>
#include <cstring>
#include <set>
using namespace std;

inline void read(int &x) {
    x = 0;
    char c = getchar();
    while (c > '9' || c < '0') c = getchar();
    while ('0' <= c && c <= '9') {
        x = x * 10 + c - '0';
        c = getchar();
    }
}

inline void output(int x) {
    if (x > 9)
        output(x/10);
    putchar(x % 10 + '0');
}

const int maxn = 1000010;
int n;
int size[maxn];

int main() {
    
//    freopen("result.txt", "w", stdout);
    
    int T; read(T);
    while (T--) {
        read(n);
        for (int i = 0; i < n; i++)
            read(size[i]);
        set<int> s;
        int L = 0, R = 0, ans = 0;
        while (R < n) {
            while (R < n && !s.count(size[R])) s.insert(size[R++]);
            ans = max(ans, R - L);
            s.erase(size[L++]);
        }
        output(ans);
        printf("\n");
    }
    return 0;
}
