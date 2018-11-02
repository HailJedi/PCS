#include <bits/stdc++.h>

using namespace std;

const int N = 2e5+5;
typedef long long ll;
int n, m, x, r, k, d;

struct SGTree {
    SGTree *ls, *rs;
    ll mx, mxl, mxr, sum;
    int lp, rp, mid;
    SGTree() : mx(0ll), mxl(0ll), mxr(0ll) { ls = rs = 0x0; }

    void normal() {
        mx = max(0ll, sum);
        mxl = max(0ll, sum);
        mxr = max(0ll, sum);
    }

    void merge() {
        sum = ls->sum + rs->sum;
        mxl = max(ls->mxl, ls->sum + rs->mxl);
        mxr = max(rs->mxr, rs->sum + ls->mxr);
        mx = max(max(ls->mx, rs->mx), ls->mxr + rs->mxl);
    }

    void build(int l, int r) {
        lp = l, rp = r, mid = (l + r) / 2;
        if (l == r) {
            sum = -k;
            normal();
        } else {
            ls = new SGTree();
            rs = new SGTree();
            ls->build(l, mid);
            rs->build(mid+1, r);
            merge();
        }
    }

    void modify(int p, int v) {
        if (lp == rp) {
            sum += v;
            normal();
        } else {
            if (p <= mid) {
                ls->modify(p, v);
            } else {
                rs->modify(p, v);
            }
            merge();
        }
    }
} *root = new SGTree();

int main() {
    scanf("%d %d %d %d", &n, &m, &k, &d);
    root->build(1, n);
    for (int _ = 1; _ <= m; _++) {
        scanf("%d %d", &r, &x);
        root->modify(r, x);
        puts(root->mx <= (ll)k * d ? "TAK" : "NIE");
    }
    return 0;
}