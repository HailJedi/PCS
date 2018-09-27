#include <bits/stdc++.h>

using namespace std;

const int N = 100000 + 5;

struct SegmentTree {
  struct Node {
    Node *ls, *rs;
    int mn;
    void *operator new(size_t) {
      static Node pool[10*N], *p = pool;

    }
  };
};

int main() {

}
