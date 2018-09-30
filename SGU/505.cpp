#include <bits/stdc++.h>

using namespace std;

const int N = 100000 + 5;

struct Trie {
  Trie *son[27], *fail;
  int id;
  void *operator new(size_t, int id) {
    static Trie pool[2*N], *p = pool;
    Trie *ret = p++;
    ret->id = id;
    memset(ret->son, 0x0, sizeof ret->son);
    ret->fail = 0x0;
    return ret;
  }
} *root;

int hsh(char c) {
  return c - 'a';
}

int id;
int idx[N];
void add(const string &s, int i) {
  int n = s.length();
  Trie *nd = root;
  for (int i = 0; i < n; i++) {
    if (nd->son[hsh(s[i])] == 0x0) {
      nd->son[hsh(s[i])] = new (++id) Trie;
    }
    nd = nd->son[hsh(s[i])];
  }
  idx[i] = nd->id;
}

vector<Trie*> topo;

void build() {
  root->fail = root;
  queue<Trie*> q;
  q.push(root);
  while (!q.empty()) {
    Trie *nd = q.front();
    q.pop();
    for (int i = 0; i < 27; i++) {
      if (nd->son[i] != 0x0) {
        Trie *f = nd->fail;
        while (f != root && f->son[i] == 0x0) {
          f = f->fail;
        }
        if (f != nd && f->son[i] != 0x0) {
          f = f->son[i];
        }
        nd->son[i]->fail = f;
        q.push(nd->son[i]);
        // if (nd->son[i]->id != 0) {
          topo.push_back(nd->son[i]);
        // }
      }
    }
  }
}

int ans[2*N];

void run(const string &s) {
  int n = s.length();
  Trie *nd = root;
  for (int i = 0; i < n; i++) {
    while (nd != root && nd->son[hsh(s[i])] == 0x0) {
      nd = nd->fail;
    }
    if (nd->son[hsh(s[i])] != 0x0) {
      nd = nd->son[hsh(s[i])];
    }
    ans[nd->id]++;
  }
}

string txt[N];
string pre, suf;

int main() {
  int n, m;
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> txt[i];
  }
  cin >> m;
  root = new (0) Trie;
  for (int i = 1; i <= m; i++) {
    cin >> pre >> suf;
    add(suf + '{' + pre, i);
  }
  build();
  for (int i = 1; i <= n; i++) {
    run(txt[i] + '{' + txt[i]);
  }
  for (int i = topo.size()-1; i >= 0; i--) {
    Trie *nd = topo[i];
    ans[nd->fail->id] += ans[nd->id];
  }
  for (int i = 1; i <= m; i++) {
    cout << ans[idx[i]] << endl;
  }
  return 0;
}
