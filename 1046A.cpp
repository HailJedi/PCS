/*
Created 2018-09-30
"AI robots"
A segment tree solution
*/

#include <bits/stdc++.h>

using namespace std;

const int N = 100000 + 5;
const int K = 20 + 5;

struct SegTree {
  SegTree *ls, *rs;
  int l, r, sum;
  void *operator new(size_t, SegTree *ls, SegTree *rs, int l, int r, int sum) {
    static SegTree pool[N*10], *p = pool;
    SegTree *ret = p++;
    ret->ls = ls;
    ret->rs = rs;
    ret->l = l;
    ret->r = r;
    ret->sum = sum;
    return ret;
  }
} *qtree[N*K*2];

void assign(SegTree *&o, int l, int r, int sum) {
  if (o == 0x0) {
    o = new (0x0, 0x0, l, r, sum) SegTree;
  }
}

int qsize;

void insert(SegTree *&o, int p) {
  if (o->l != o->r) {
    int mid = (o->l + o->r) / 2;
    if (p <= mid) {
      assign(o->ls, 1, mid, 0);
      insert(o->ls, p);
    } else {
      assign(o->rs, mid+1, qsize, 0);
      insert(o->rs, p);
    }
  }
  o->sum++;
}

void erase(SegTree *&o, int p) {
  if (o->l != o->r) {
    int mid = (o->l + o->r) / 2;
    if (p <= mid) {
      assert(o->ls != 0x0);
      erase(o->ls, p);
    } else {
      assert(o->rs != 0x0);
      erase(o->rs, p);
    }
  }
  o->sum--;
}

int query(SegTree *o, int qr) {
  if (o->l == o->r) {
    return o->sum;
  }
  int mid = (o->l + o->r) / 2;
  int ret = 0;
  if (qr <= mid) {
    ret += o->ls ? query(o->ls, qr) : 0;
  } else {
    ret += o->ls ? o->ls->sum : 0;
    ret += o->rs ? query(o->rs, qr) : 0;
  }
  return ret;
}

int query(SegTree *o, int ql, int qr) {
  return query(o, qr) - query(o, ql-1);
}

int n, k;
vector<int> qs, xs;
vector<tuple<int, int, int>> event;
int x[N], r[N], q[N];

int ID(vector<int> &vec, int x) {
  return lower_bound(vec.begin(), vec.end(), x) - vec.begin() + 1;
}

int main() {
  freopen("read.in", "r", stdin);
  scanf("%d %d", &n, &k);
  for (int i = 1; i <= n; i++) {
    scanf("%d %d %d", &x[i], &r[i], &q[i]);
    xs.push_back(x[i]);
    xs.push_back(x[i]-r[i]);
    xs.push_back(x[i]+r[i]);
    qs.push_back(q[i]);
    for (int j = 1; j <= k; j++) {
      qs.push_back(q[i]+i);
      qs.push_back(q[i]-i);
    }
  }
  sort(qs.begin(), qs.end());
  sort(xs.begin(), xs.end());
  qs.resize(distance(qs.begin(), unique(qs.begin(), qs.end())));
  xs.resize(distance(xs.begin(), unique(xs.begin(), xs.end())));
  for (int i = 1; i <= n; i++) {
    event.push_back(make_tuple(x[i]-r[i], i, -1));
    event.push_back(make_tuple(x[i], i, 0));
    event.push_back(make_tuple(x[i]+r[i], i, 1));
  }
  sort(event.begin(), event.end());
  qsize = qs.size();
  for (int i = 1; i <= qsize; i++) {
    assign(qtree[i], 1, qsize, 0);
  }
  long long ans = 0;
  for (int i = 0; i < (int)event.size(); i++) {
    int ev = get<2>(event[i]);
    int id = get<1>(event[i]);
    if (ev == -1) {
      int q_val = ID(qs, q[i]);
      int x_val = ID(xs, x[i]);
      insert(qtree[k], x_val);
    }
    if (ev == 0) {
      int lx_val = ID(xs, x[i]-r[i]);
      int rx_val = ID(xs, x[i]+r[i]);
      for (int j = -k; j <= k; j++) {
        if (q[i]+j >= 0) {
          int q_val = ID(qs, q[i]+j);
          ans += query(qtree[q_val], rx_val, lx_val);
        }
      }
    }
    if (ev == 1) {
      int q_val = ID(qs, q[i]);
      int x_val = ID(xs, x[i]);
      erase(qtree[q_val], x_val);
    }
  }
  printf("%lld\n", ans);
  return 0;
}
