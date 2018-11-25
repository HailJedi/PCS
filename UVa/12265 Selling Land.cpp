#include <cstring>
#include <cstdio>
using namespace std;

const int maxn = 1010;
char s[maxn][maxn];
int height[maxn], ans[maxn*2];

struct Rect {
    int c, h;
    Rect(int c = 0, int h = 0) : c(c), h(h) {}
} rect[maxn];

int main() {
    int n, m, T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n, &m);
        for (int i = 0; i < n; i++) scanf("%s", s[i]);

        memset(height, 0, sizeof(height));
        memset(ans, 0, sizeof(ans));

        for (int r = 0; r < n; r++) {
            int top = -1;
            for (int c = 0; c < m; c++) {
                if (s[r][c] == '#') {
                    top = -1;
                    height[c] = 0;
                } else {
                    height[c]++;
                    Rect r(c, height[c]);
                    if (top < 0) rect[++top] = r;
                    else {
                        while (top >= 0 && r.h <= rect[top].h)
                            r.c = rect[top--].c;
                        if (top < 0 || r.h - r.c > rect[top].h - rect[top].c)
                            rect[++top] = r;
                    }
                    ans[c-rect[top].c+rect[top].h+1]++;
                }
            }
        }
        for (int i = 1; i <= n + m; i++)
            if (ans[i]) printf("%d x %d\n", ans[i], i*2);
    }
    return 0;
}
