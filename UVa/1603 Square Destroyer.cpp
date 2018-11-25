#include <iostream>
#include <cstring>
using namespace std;

int n, k;
const int maxn = 60 + 1;
const int count_n[] = {0, 4, 12, 24, 40, 60}; // 2 * n * (n+1)
int exist[maxn];
int contains[maxn][maxn];
int cnt; // total exist sides
int fullsize[maxn], realsize[maxn];

/*
    0 1 2 3 4 5 6 7 ...
  0 ------------------------> x
  1 |
  2 |
  3 |
  4 |
    .
    .
    y
*/

int row_id(int x, int y) { return x+(2*n+1)*y; }
int col_id(int x, int y) { return row_id(x, y)+n; }

void init() {
    cin >> n >> k;
    for (int i = 0; i < count_n[n]; i++) exist[i] = 1;
    int temp; while (k--) { cin >> temp; exist[temp-1] = 0; }
    
    // count each square's sides
    cnt = 0;
    memset(contains, 0, sizeof(contains));
    memset(realsize, 0, sizeof(realsize));
    for (int size = 1; size <= n; size++) {
        for (int x = 0; x+size <= n; x++) {
            for (int y = 0; y + size <= n; y++) {
                // draw a square based on (x, y) of size
                fullsize[cnt] = size*4;
                // count one match on each four sides one by one
                for (int ite = 0; ite < size; ite++) {
                    int up = row_id(x+ite, y);
                    int down = row_id(x+ite, y+size);
                    int left = col_id(x, y+ite);
                    int right = col_id(x+size, y+ite);
                    contains[cnt][up]    = 1;
                    contains[cnt][down]  = 1;
                    contains[cnt][left]  = 1;
                    contains[cnt][right] = 1;
                    realsize[cnt] += exist[up] + exist[down] + exist[left] + exist[right];
                }
                cnt++;
            }
        }
    }
}

int find_square() {
    for (int i = 0; i < cnt; i++) {
        if (realsize[i] == fullsize[i]) return i;
    }
    return -1;
}

int best;
#define iterator_side(s, n) for (int s = 0; s < n; s++)
void dfs(int d) {
    if(d >= best) return;
    
    int k = find_square();
    if (k == -1) {
        if(d < best) best = d;
        return;
    }
    
    iterator_side (si, count_n[n]) if (contains[k][si]) {
        iterator_side (asq, cnt) if (contains[asq][si]) realsize[asq]--;
        dfs(d+1);
        iterator_side (asq, cnt) if (contains[asq][si]) realsize[asq]++;
    }
}

int maxd[6] = {0, 1, 3, 6, 9, 14};
int main() {
    ios::sync_with_stdio(false);
    int T; cin >> T;
    while (T--) {
        init();
        best = maxd[n];
        dfs(0);
        cout << best << endl;
    }
    return 0;
}
