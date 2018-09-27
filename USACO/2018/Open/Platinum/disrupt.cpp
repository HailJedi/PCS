#include <bits/stdc++.h>

using namespace std;

const int N = 100000 + 5;
const int M = 200000 + 5;

int n, m;
set< pair<int, int> > *st[N];
vector< pair<int, int> > tag[N];
vector< pair<int, int> > g[N];
int ans[N];

set< pair<int, int> > *merge(set< pair<int, int> > *st1, set< pair<int, int> > *st2) {
  if (st1->size() < st2->size()) {
    for (set< pair<int, int> >::iterator it = st1->begin(); it != st1->end(); ++it) {
      if (st2->count(*it)) {
        st2->erase(st2->find(*it));
      } else {
        st2->insert(*it);
      }
    }
    return st2;
  } else {
    for (set< pair<int, int> >::iterator it = st2->begin(); it != st2->end(); ++it) {
      if (st1->count(*it)) {
        st1->erase(st1->find(*it));
      } else {
        st1->insert(*it);
      }
    }
    return st1;
  }
}

void dfs(int u, int f = 0) {
  for (int i = 0; i < (int)tag[u].size(); i++) {
    st[u]->insert(tag[u][i]);
  }
  for (int i = 0; i < (int)g[u].size(); i++) {
    int v = g[u][i].first;
    if (v != f) {
      dfs(v, u);
      if (st[v]->empty()) {
        ans[g[u][i].second] = -1;
      } else {
        ans[g[u][i].second] = st[v]->begin()->first;
      }
      st[u] = merge(st[u], st[v]);
    }
  }
}

int main() {
  freopen("disrupt.in", "r", stdin);
  freopen("disrupt.out", "w", stdout);
  scanf("%d %d", &n, &m);
  for (int i = 1; i <= n; i++) {
    st[i] = new set< pair<int, int> > ();
  }
  for (int i = 1; i < n; i++) {
    int u, v;
    scanf("%d %d", &u, &v);
    g[u].push_back(make_pair(v, i));
    g[v].push_back(make_pair(u, i));
  }
  for (int i = 1; i <= m; i++) {
    int u, v, w;
    scanf("%d %d %d", &u, &v, &w);
    tag[u].push_back(make_pair(w, i));
    tag[v].push_back(make_pair(w, i));
  }
  dfs(1);
  for (int i = 1; i < n; i++) {
    printf("%d\n", ans[i]);
  }
  return 0;
}
