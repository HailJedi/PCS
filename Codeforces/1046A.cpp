/*
Created 2018-09-30
"AI robots"
A segment tree solution
*/

#include <bits/stdc++.h>

using namespace std;

const int N = 100000 + 1;
const int K = 20 + 1;

struct SegTree {
  SegTree *ls, *rs;
  int l, r, sum;
} *qtree[N*K*2];

int qsize, xsize;

SegTree *make_new(int l, int r) {
  SegTree *ret = new SegTree();
  ret->l = l;
  ret->r = r;
  return ret;
}

void insert(SegTree *&o, int p) {
  if (o->l != o->r) {
    int mid = (o->l + o->r) / 2;
    if (p <= mid) {
      if (o->ls == 0x0) {
        o->ls = make_new(o->l, mid);
      }
      insert(o->ls, p);
    } else {
      if (o->rs == 0x0) {
        o->rs = make_new(mid+1, o->r);
      }
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
  scanf("%d %d", &n, &k);
  for (int i = 1; i <= n; i++) {
    scanf("%d %d %d", &x[i], &r[i], &q[i]);
    xs.push_back(x[i]);
    xs.push_back(x[i]-r[i]);
    xs.push_back(x[i]+r[i]);
    qs.push_back(q[i]);
    for (int j = 1; j <= k; j++) {
      qs.push_back(q[i]+j);
      qs.push_back(q[i]-j);
    }
  }
  sort(qs.begin(), qs.end());
  sort(xs.begin(), xs.end());
  qs.resize(distance(qs.begin(), unique(qs.begin(), qs.end())));
  xs.resize(distance(xs.begin(), unique(xs.begin(), xs.end())));
  for (int i = 1; i <= n; i++) {
    event.push_back(tuple<int, int, int>(x[i]-r[i], -1, i));
    event.push_back(tuple<int, int, int>(x[i], 0, i));
    event.push_back(tuple<int, int, int>(x[i]+r[i], 1, i));
  }
  sort(event.begin(), event.end());
  qsize = qs.size();
  xsize = xs.size();
  for (int i = 1; i <= qsize; i++) {
    qtree[i] = make_new(1, xsize);
  }
  long long ans = 0;
  for (auto tp: event) {
    int ev = get<1>(tp);
    int id = get<2>(tp);
    int q_val = ID(qs, q[id]);
    int x_val = ID(xs, x[id]);
    if (ev == -1) {
      insert(qtree[q_val], x_val);
    }
    if (ev == 1) {
      erase(qtree[q_val], x_val);
    }
    if (ev == 0) {
      int lx_val = ID(xs, x[id]-r[id]);
      int rx_val = ID(xs, x[id]+r[id]);
      for (int i = -k; i <= k; i++) {
        int q_val = ID(qs, q[id]+i);
        ans += query(qtree[q_val], lx_val, rx_val);
      }
    }
  }
  printf("%lld\n", (ans-n)/2);
  return 0;
}
