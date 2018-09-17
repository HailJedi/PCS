#include <bits/stdc++.h>

using namespace std;

#define all(x) x.begin(), x.end()
#define pb push_back
#define sz(x) x.size()
#define lc (p << 1)
#define rc (p << 1 | 1)
#define mid ((l+r) >> 1)
#define vi vector<int>

const int N = 400010;
const int M = N << 2;
const int ST = N << 5;

int suf_T[M], prf_T[M], a[N], L[M], R[M];
int st, n;
int *pos[ST];
int val[ST];
map<int, int> dsc;

int discret() {
    vi rec;
    for (int i = 1; i <= n; i++) {
        rec.pb(a[i] - i);
        rec.pb(a[i] - (i-1));
    }
    sort(all(rec));
    rec.erase(unique(all(rec)), rec.end());
    for (int i = 0; i < sz(rec); i++) dsc[rec[i]] = i+1;
    return sz(rec);
}

void change(int &x, int y) {
    pos[st] = &x;
    val[st] = x;
    st++;
    x = y;
}

void rollback(int nst) {
    while (st > nst) {
        st--;
        *pos[st] = val[st];
    }
}

void update(int T, int p, int pos, int v) {
    int l = L[p], r = R[p];
    if (T == 0) change(suf_T[p], max(suf_T[p], v));
    if (T == 1) prf_T[p] = max(prf_T[p], v);
    if (l == r) return;
    if (pos <= mid) update(T, lc, pos, v);
    else update(T, rc, pos, v);
}

int query(int *T, int p, int ql, int qr) {
    int l = L[p], r = R[p];
    if (ql <= l && r <= qr) return T[p];
    int ret = 0;
    if (mid >= ql) ret = max(ret, query(T, lc, ql, qr));
    if (mid+1 <= qr) ret = max(ret, query(T, rc, ql, qr));
    return ret;
}

void build(int *T, int p, int l, int r) {
    L[p] = l, R[p] = r;
    if (l < r) {
        build(T, lc, l, mid);
        build(T, rc, mid+1, r);
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]);
    int sz = discret();
    build(suf_T, 1, 1, sz);
    build(prf_T, 1, 1, sz);
    vi state;
    for (int i = n; i > 1; i--) {
        state.pb(st);
        int pos = dsc[a[i] - (i-1)];
        int val = query(suf_T, 1, pos, sz);
        update(0, 1, pos, val+1);
    }
    int ans = query(suf_T, 1, 1, sz);
    for (int i = 1; i < n; i++) {
        rollback(state.back());
        state.pop_back();
        int pos = dsc[a[i] - i];
        int val = query(prf_T, 1, 1, pos);
        update(1, 1, pos, val+1);
        ans = max(ans, val+1+query(suf_T, 1, pos, sz));
    }
    printf("%d\n", max(n - 1 - ans, 0));
    return 0;
}