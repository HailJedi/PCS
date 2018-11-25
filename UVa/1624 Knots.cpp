#include <cstdio>
#include <cstring>
using namespace std;

const int maxn = 1000010;

struct Node {
    int l, r, face;
} nodes[maxn];

int L, P;
int used[maxn], pos[maxn];

void remove(int node) {
    used[node] = 0;
    nodes[nodes[node].r].l = nodes[node].l;
    nodes[nodes[node].l].r = nodes[node].r;
}

int main() {
//    freopen("write.txt", "w", stdout);
    int T; scanf("%d", &T);
    for (int kase = 1; kase <= T; kase++) {
        scanf("%d%d", &L, &P);
        for (int i = 0; i < L; i++) {
            nodes[i].l = i-1; nodes[i].r = i + 1; used[i] = 0;
        } nodes[0].l = L-1; nodes[L-1].r = 0;
        
        for (int i = 0; i < P; i++) {
            int x, y; scanf("%d%d", &x, &y);
            pos[x] = 1; pos[y] = -1;
            nodes[x].face = y; nodes[y].face = x;
            used[x] = used[y] = 1;
        }
        
        for (int i = 0; i < L; i++)
            if (!used[i]) remove(i);
        
        int size = 2 * P, update = 0, st = 0;
        while (size) {
            while (!used[st]) st++;
            update = 0;
            for (int node = nodes[st].r; node != st && !update; node = nodes[node].r) {
                int x = node, y = nodes[node].r;
                // passing
                if (pos[x] == pos[y] && (nodes[nodes[x].face].r == nodes[y].face
                                      || nodes[nodes[y].face].r == nodes[x].face)) {
                    remove(x); remove(nodes[x].face);
                    remove(y); remove(nodes[y].face);
                    size -= 4; update = 1;
                } else if (nodes[x].face == y) { // self loop
                    remove(x); remove(y);
                    size -= 2; update = 1;
                }
            }
            if (!update) break;
        }
        
        printf("Case #%d: ", kase);
        if (size) puts("NO");
        else puts("YES");
    }
    return 0;
}
