#include <cstdio>
#include <cstring>
using namespace std;

const int maxn = 301;
int graph[maxn][maxn];
int m, k, u, v;

bool judge() {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            int f1 = 0, f2 = 0;
            for (int k = 0; k < m; k++) {
                if (graph[i][k] && graph[j][k]) f1 = 1;
                if (graph[i][k] ^  graph[j][k]) f2 = 1;
            }
            if (f1 && f2) return false;
        }
    }
    return true;
}

int main() {
    int T; scanf("%d", &T);
    for (int kase = 1; kase <= T; kase++) {
        scanf("%d%d", &m, &k);
        memset(graph, 0, sizeof(graph));
        for (int i = 1; i <= k; i++) {
            scanf("%d%d", &u, &v);
            graph[u][v] = 1;
        }
        printf("Case #%d: ", kase);
        if (judge()) puts("Yes");
        else puts("No");
    }
    return 0;
}
