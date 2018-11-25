#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

const int maxn = 10010;
int A[maxn]; // 1, 2, 3, 4, ..., n
int n, cnt;

#define mid_btw(L, R) (L + (R - L) / 2 + 1)

void crane(int L, int R) {
    int mid = mid_btw(L, R);
    for (int i = 0; i + L < mid; i++)
        swap(A[L+i], A[mid+i]);
}

#define is_even(L, R) ( (R-L) % 2 == 1 )

int cur_pos(const int x) {
    for (int i = 1; i <= n; i++)
        if (A[i] == x) return i;
    return -1;
}

int first[maxn*maxn], second[maxn*maxn];

void handle(const int x) {
    const int targ = x;
    int cur = cur_pos(x);
    while (cur != targ) {
        const int right = (is_even(cur, targ) ? targ : targ - 1);
        first[cnt] = cur; second[cnt++] = right;
        crane(cur, right);
        cur = mid_btw(cur, right);
    }
}

void output() {
    cout << cnt << endl;
    for (int i = 0; i < cnt; i++)
        cout << first[i] << ' ' << second[i] << endl;
}

int main() {
    ios::sync_with_stdio(false);
    
    int T; cin >> T;
    while (T--) {
        cin >> n;
        for (int i = 1; i <= n; i++) cin >> A[i];
        cnt = 0;
        for (int i = n; i >= 1; i--) handle(i);
        output();
    }
    return 0;
}


