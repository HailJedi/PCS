/*
Created 2018-09-29
*/

#include <bits/stdc++.h>

using namespace std;

const int N = 100000 + 5;

int n;
int lft[N], rgt[N];

struct SegmentTree {
  struct Node {
    Node *ls, *rs;
    int mx;
    void *operator new(size_t, int mx) {
      static Node pool[N*5], *p = pool;
      Node *ret = p++;
      ret->mx = mx;
      return ret;
    }
  } *root;

  int n;

  void build(Node *&o, int l, int r) {
    if (l != r) {
      int mid = (l + r) / 2;
      o->ls = new (0) Node;
      o->rs = new (0) Node;
      build(o->ls, l, mid);
      build(o->rs, mid+1, r);
    }
  }

  void init(int n) {
    this->n = n;
    root = new (0) Node;
    build(root, 1, n);
  }

  void change(Node *&o, int l, int r, int p, int v) {
    if (l == r) {
      o->mx = v;
    } else {
      int mid = (l + r) / 2;
      if (p <= mid) {
        change(o->ls, l, mid, p, v);
      } else {
        change(o->rs, mid+1, r, p, v);
      }
      o->mx = max(o->ls->mx, o->rs->mx);
    }
  }

  void change(int p, int v) {
    change(root, 1, n, p, v);
  }

  int max_val(Node *o, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr) {
      return o->mx;
    }
    int mid = (l + r) / 2, ret = -1;
    if (mid >= ql) {
      ret = max(ret, max_val(o->ls, l, mid, ql, qr));
    }
    if (mid + 1 <= qr) {
      ret = max(ret, max_val(o->rs, mid+1, r, ql, qr));
    }
    return ret;
  }

  int max_val(int ql, int qr) {
    if (ql > qr) {
      return 0;
    }
    return max_val(root, 1, n, ql, qr);
  }
} ds;

struct Segment {
  int l, r;
  Segment() {}
  Segment(int l, int r) : l(l), r(r) {}
  bool operator < (const Segment &sg) const {
    return l < sg.l;
  }
} seg[N];

int main() {
  freopen("art2.in", "r", stdin);
  freopen("art2.out", "w", stdout);
  scanf("%d", &n);
  for (int i = 1; i <= n+1; i++) {
    lft[i] = n+1;
    rgt[i] = 0;
  }
  for (int i = 1; i <= n; i++) {
    int v;
    scanf("%d", &v);
    v++;
    lft[v] = min(lft[v], i);
    rgt[v] = max(rgt[v], i);
  }
  vector< pair<int, int> > vec;
  for (int i = 1; i <= n+1; i++) {
    if (lft[i] != n+1) {
      vec.push_back(make_pair(lft[i], -i));
      vec.push_back(make_pair(rgt[i], i));
    }
  }
  sort(vec.begin(), vec.end());
  stack<int> stk;
  bool ok = true;
  for (int i = 0; i < (int)vec.size(); i++) {
    if (vec[i].second < 0) {
      stk.push(-vec[i].second);
    } else {
      if (stk.top() != vec[i].second) {
        ok = false;
        break;
      }
      stk.pop();
    }
  }
  if (!ok) {
    puts("-1");
    return 0;
  }
  int m = 0;
  for (int i = 2; i <= n+1; i++) {
    if (lft[i] != n+1) {
      seg[++m] = Segment(lft[i], rgt[i]);
    }
  }
  sort(seg+1, seg+1+m);
  ds.init(n);
  for (int i = m; i >= 1; i--) {
    int f = 1 + ds.max_val(1, seg[i].r-1);
    ds.change(seg[i].r, f);
  }
  printf("%d\n", ds.max_val(1, n));
  return 0;
}
