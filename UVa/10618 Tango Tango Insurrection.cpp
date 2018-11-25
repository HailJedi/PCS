#include <cstdio>
#include <cstring>

const int UP = 0;
const int LEFT = 1;
const int RIGHT = 2;
const int DOWN = 3;

const int maxn = 70;

int d[maxn][4][4][3];
int action[maxn][4][4][3];
char seq[maxn], pos[256], footch[] = ".LR";

int energy(int a, int ta) {
    if (a == ta) return 3;
    if (a + ta == 3) return 7;
    return 5;
}

int energy(int i, int a, int b, int s, int f, int t, int &ta, int &tb) {
    ta = a; tb = b;
    if (f == LEFT) ta = t;
    if (f == RIGHT) tb = t;
    
    if (ta == tb) return -1;
    if (ta == RIGHT && tb == LEFT) return -1;
    if (a == RIGHT && tb != b) return -1;
    if (b == LEFT && ta != a) return -1;
    
    int e;
    if (f == 0) e = 0;
    else if (f != s) e = 1;
    else {
        if (f == LEFT) e = energy(a, ta);
        if (f == RIGHT) e = energy(b, tb);
    }
    return e;
}

void update(int i, int a, int b, int s, int f, int t) {
    int ta, tb;
    int e = energy(i, a, b, s, f, t, ta, tb);
    if (e < 0) return;
    
    int cost = d[i+1][ta][tb][f] + e;
    int &ans = d[i][a][b][s];
    if (cost < ans) {
        ans = cost;
        action[i][a][b][s] = f * 4 + t;
    }
}

int main() {
    pos['U'] = UP; pos['L'] = LEFT; pos['R'] = RIGHT; pos['D'] = DOWN;
    
    while (scanf("%s", seq) == 1) {
        if (seq[0] == '#') break;
        int n = (int)strlen(seq);
        memset(d, 0, sizeof(d));
        for (int i = n-1; i >= 0; i--) {
            for (int a = 0; a <= 3; a++) {
                for (int b = 0; b <= 3; b++) {
                    if (a == b) continue;
                    for (int s = 0; s <= 2; s++) {
                        d[i][a][b][s] = 10*n;
                        if (seq[i] == '.') {
                            update(i, a, b, s, 0, 0);
                            for (int t = 0; t <= 3; t++) {
                                update(i, a, b, s, LEFT, t);
                                update(i, a, b, s, RIGHT, t);
                            }
                        } else {
                            update(i, a, b, s, LEFT, pos[seq[i]]);
                            update(i, a, b, s, RIGHT, pos[seq[i]]);
                        }
                    }
                }
            }
        }
        
        int a = LEFT, b = RIGHT, s = 0;
        for (int i = 0; i < n; i++) {
            int f = action[i][a][b][s] / 4;
            int t = action[i][a][b][s] % 4;
            printf("%c", footch[f]);
            s = f;
            if (f == LEFT) a = t;
            if (f == RIGHT) b = t;
        }
        puts("");
    }
    return 0;
}

