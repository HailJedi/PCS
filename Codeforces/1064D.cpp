/*
Created 2018-10-14
"Labyrinth"
A Dijkstra solution
*/

#include <bits/stdc++.h>

using namespace std;

const int N = 2000 + 5;
const int INF = 0x3f3f3f3f;

const int dr[] = {-1, 1, 0, 0};
const int dc[] = {0, 0, 1, -1};

char cell[N][N];
int n, m, r, c, x, y;
int dis[N][N];

struct Status {
  int r, c, dx, dy;
  Status(int r, int c, int dx, int dy) : r(r), c(c), dx(dx), dy(dy) {}
  bool operator < (const Status &s) const {
    return dx + dy > s.dx + s.dy;
  }
};

int main() {
  scanf("%d %d %d %d %d %d", &n, &m, &r, &c, &x, &y);
  for (int i = 1; i <= n; i++) {
    scanf("%s", cell[i] + 1);
  }
  memset(dis, INF, sizeof dis);
  dis[r][c] = 0;
  priority_queue<Status> q;
  q.push(Status(r, c, 0, 0));
  while (!q.empty()) {
    Status st = q.top();
    q.pop();
    int r = st.r, c = st.c, dx = st.dx, dy = st.dy;
    if (dx + dy > dis[r][c]) {
      continue;
    }
    for (int i = 0; i < 4; i++) {
      int nr = r + dr[i], nc = c + dc[i];
      int nx = dx + (dc[i] == -1), ny = dy + (dc[i] == 1);
      if (cell[nr][nc] == '.' && nx <= x && ny <= y) {
        if (dis[nr][nc] > nx + ny) {
          dis[nr][nc] = nx + ny;
          q.push(Status(nr, nc, nx, ny));
        }
      }
    }
  }
  int ans = 0;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      ans += (dis[i][j] != INF);
    }
  }
  printf("%d\n", ans);
  return 0;
}
