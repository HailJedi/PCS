#include <bits/stdc++.h>

using namespace std;

const int N = 5e4+5;
int n, nn, m;
int a[N], mp[N], x[N], y[N], k[N], v[N], rnk[N];
char cmd[N];
map<int, int> tr;

struct SBTree {
    SBTree *ls, *rs;
    int sum, l, r;
    void *operator new (size_t, SBTree *ls, SBTree *rs, int l, int r, int sum) {
        static SBTree pool[N*100], *p = pool;
        SBTree *ret = p++;
        ret->ls = ls;
        ret->rs = rs;
        ret->l = l;
        ret->r = r;
        ret->sum = sum;
        return ret;
    }
} *root[N], *bits[N];

SBTree* create(SBTree *pre, int p) {
    SBTree *ret = new (pre->ls, pre->rs, pre->l, pre->r, pre->sum) SBTree;
    if (ret->l != ret->r) {
        if (p <= ret->ls->r) {
            ret->ls = create(pre->ls, p);
        } else {
            ret->rs = create(pre->rs, p);
        }
    }
    ret->sum++;
    return ret;
}

SBTree *build(int l, int r) {
    SBTree *ret = new (0x0, 0x0, l, r, 0) SBTree;
    if (l != r) {
        int mid = (l + r) / 2;
        ret->ls = build(l, mid);
        ret->rs = build(mid+1, r);
    }
    return ret;
}

void recrew(SBTree *&cr, int l, int r) {
    if (!cr) {
        cr = new (0x0, 0x0, l, r, 0) SBTree;
    }
}

void add(SBTree *&pre, int p, int v) {
    pre->sum += v;
    if (pre->l != pre->r) {
        int mid = (pre->l + pre->r) / 2;
        if (p <= mid) {
            recrew(pre->ls, pre->l, mid);
            add(pre->ls, p, v);
        } else {
            recrew(pre->rs, mid+1, pre->r);
            add(pre->rs, p, v);
        }
    }
}

int lowbit(int x) {
    return x & -x;
}

void add(int p, int v) {
    int w = tr[a[p]];
    for (; p <= n; p += lowbit(p)) {
        add(bits[p], w, v);
    }
}

vector<SBTree*> ql, qr;

int buf(vector<SBTree*> q) {
    int ret = 0;
    for (int i = 0; i < q.size(); i++) {
        if (q[i] && q[i]->ls) {
            ret += q[i]->ls->sum;
        }
    }
    return ret;
}

int buf() {
    return buf(qr) - buf(ql);
}

void change(vector<SBTree*> &q, bool t) {
    for (int i = 0; i < q.size(); i++) {
        if (q[i]) {
            q[i] = t ? q[i]->rs : q[i]->ls;
        }
    }
}

int query(SBTree *lt, SBTree *rt, int k) {
    if (lt->l == lt->r) {
        return lt->l;
    }
    int lsz = buf() + rt->ls->sum - lt->ls->sum;
    if (k <= lsz) {
        change(ql, 0);
        change(qr, 0);
        return query(lt->ls, rt->ls, k);
    } else {
        change(ql, 1);
        change(qr, 1);
        return query(lt->rs, rt->rs, k-lsz);
    }
}

int query(int l, int r, int k) {
    ql.clear();
    qr.clear();
    for (int i = l-1; i; i -= lowbit(i)) {
        ql.push_back(bits[i]);
    }
   for (int i = r; i; i -= lowbit(i)) {
        qr.push_back(bits[i]);
    }
    return query(root[l-1], root[r], k);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        rnk[i] = a[i];
    }
    int t = n;
    for (int i = 1; i <= m; i++) {
        cin >> cmd[i];
        if (cmd[i] == 'C') {
            cin >> x[i] >> v[i];
            rnk[++t] = v[i];
        } else {
            cin >> x[i] >> y[i] >> k[i];
        }
    }
    sort(rnk+1, rnk+1+t);
    rnk[0] = -1;
    nn = 0;
    for (int i = 1; i <= t; i++) {
        if (rnk[i] != rnk[i-1]) {
            rnk[++nn] = rnk[i];
        }
    }
    for (int i = 1; i <= n; i++) {
        tr[a[i]] = lower_bound(rnk+1, rnk+1+nn, a[i]) - rnk;
    }
    for (int i = 1; i <= m; i++) {
        if (cmd[i] == 'C') {
            tr[v[i]] = lower_bound(rnk+1, rnk+1+nn, v[i]) - rnk;
        }
    }
    root[0] = build(1, nn);
    for (int i = 1; i <= n; i++) {
        root[i] = create(root[i-1], tr[a[i]]);
        bits[i] = new (0x0, 0x0, 1, nn, 0) SBTree;
    }
    for (int i = 1; i <= m; i++) {
        if (cmd[i] == 'Q') {
            cout << rnk[query(x[i], y[i], k[i])] << endl;
        } else {
            add(x[i], -1);
            a[x[i]] = v[i];
            add(x[i], 1);
        }
    }
    return 0;
}