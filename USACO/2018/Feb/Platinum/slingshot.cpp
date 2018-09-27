#include <bits/stdc++.h>

using namespace std;

const int N = 100000 + 5;
const long long INF = 1e18;

struct SegmentTree {
  struct Node {
    Node *ls, *rs;
    long long mn;
    void *operator new(size_t, long long mn) {
      static Node pool[20*N], *p = pool;
      Node *ret = p++;
      ret->ls = ret->rs = 0x0;
      ret->mn = mn;
      return ret;
    }
  } *root;

  int n;

  void build(Node *&o, int l, int r) {
    if (l != r) {
      int mid = (l + r) / 2;
      o->ls = new (INF) Node;
      o->rs = new (INF) Node;
      build(o->ls, l, mid);
      build(o->rs, mid+1, r);
    }
  }

  void clear(Node *&o, int l, int r) {
    o->mn = INF;
    if (l != r) {
      int mid = (l + r) / 2;
      clear(o->ls, l, mid);
      clear(o->rs, mid+1, r);
    }
  }

  void init(int n) {
    this->n = n;
    root = new (INF) Node;
    build(root, 1, n);
  }

  void clear() {
    clear(root, 1, n);
  }

  void change(Node *o, int l, int r, int p, long long v) {
    if (l == r) {
      o->mn = min(o->mn, v);
    } else {
      int mid = (l + r) / 2;
      if (p <= mid) {
        change(o->ls, l, mid, p, v);
      } else {
        change(o->rs, mid+1, r, p, v);
      }
      o->mn = min(o->ls->mn, o->rs->mn);
    }
  }

  void change(int p, long long v) {
    change(root, 1, n, p, v);
  }

  long long min_val(Node *o, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr) {
      return o->mn;
    }
    int mid = (l + r) / 2;
    long long ret = INF;
    if (mid >= ql) {
      ret = min(ret, min_val(o->ls, l, mid, ql, qr));
    }
    if (mid+1 <= qr) {
      ret = min(ret, min_val(o->rs, mid+1, r, ql, qr));
    }
    return ret;
  }

  long long min_val(int l, int r) {
    return min_val(root, 1, n, l, r);
  }

} up, down;

int sh, qry;
long long shot_x[N], shot_y[N], shot_t[N];;
long long query_x[N], query_y[N];
int shot_id[N], query_id[N];
int shot_hsh_y[N], query_hsh_y[N];
vector<int> hsh_y;
long long left_ans[N], right_ans[N];

bool cmp1(int x, int y) {
  return shot_x[x] < shot_x[y];
}

bool cmp2(int x, int y) {
  return query_x[x] < query_x[y];
}

int main() {
  freopen("slingshot.in", "r", stdin);
  freopen("slingshot.out", "w", stdout);
  scanf("%d %d", &sh, &qry);
  for (int i = 1; i <= sh; i++) {
    scanf("%lld %lld %lld", &shot_x[i], &shot_y[i], &shot_t[i]);
    shot_id[i] = i;
    hsh_y.push_back(shot_y[i]);
  }
  for (int i = 1; i <= qry; i++) {
    scanf("%lld %lld", &query_x[i], &query_y[i]);
    query_id[i] = i;
    hsh_y.push_back(query_y[i]);
  }
  sort(shot_id+1, shot_id+1+sh, cmp1);
  sort(query_id+1, query_id+1+qry, cmp2);
  sort(hsh_y.begin(), hsh_y.end());
  hsh_y.resize(distance(hsh_y.begin(), unique(hsh_y.begin(), hsh_y.end())));
  for (int i = 1; i <= sh; i++) {
    shot_hsh_y[i] = lower_bound(hsh_y.begin(), hsh_y.end(), shot_y[i]) - hsh_y.begin() + 1;
  }
  for (int i = 1; i <= qry; i++) {
    query_hsh_y[i] = lower_bound(hsh_y.begin(), hsh_y.end(), query_y[i]) - hsh_y.begin() + 1;
  }
  up.init(hsh_y.size());
  down.init(hsh_y.size());
  int pt = 1;
  for (int i = 1; i <= qry; i++) {
    while (pt <= sh && shot_x[shot_id[pt]] <= query_x[query_id[i]]) {
      up.change(shot_hsh_y[shot_id[pt]], -shot_x[shot_id[pt]] - shot_y[shot_id[pt]] + shot_t[shot_id[pt]]);
      down.change(shot_hsh_y[shot_id[pt]], -shot_x[shot_id[pt]] + shot_y[shot_id[pt]] + shot_t[shot_id[pt]]);
      pt++;
    }
    left_ans[query_id[i]] = min(query_x[query_id[i]] + query_y[query_id[i]] + up.min_val(1, query_hsh_y[query_id[i]]),
                                  query_x[query_id[i]] - query_y[query_id[i]] + down.min_val(query_hsh_y[query_id[i]], hsh_y.size()));
  }
  up.clear();
  down.clear();
  pt = sh;
  for (int i = qry; i >= 1; i--) {
    while (pt >= 1 && shot_x[shot_id[pt]] >= query_x[query_id[i]]) {
      up.change(shot_hsh_y[shot_id[pt]], shot_x[shot_id[pt]] + shot_y[shot_id[pt]] + shot_t[shot_id[pt]]);
      down.change(shot_hsh_y[shot_id[pt]], shot_x[shot_id[pt]] - shot_y[shot_id[pt]] + shot_t[shot_id[pt]]);
      pt--;
    }
    right_ans[query_id[i]] = min(-query_x[query_id[i]] - query_y[query_id[i]] + up.min_val(query_hsh_y[query_id[i]], hsh_y.size()),
                                  -query_x[query_id[i]] + query_y[query_id[i]] + down.min_val(1, query_hsh_y[query_id[i]]));
  }
  for (int i = 1; i <= qry; i++) {
    printf("%lld\n", min(min(left_ans[i], right_ans[i]), abs(query_x[i] - query_y[i])));
  }
  return 0;
}
