#include <cstdio>
#include <queue>
using namespace std;

int main()
{
    //freopen("input.in", "r", stdin);
    //freopen("output.out", "w", stdout);

    int n, x;
    priority_queue<int, vector<int>, greater<int> > q;

    while (scanf("%d", &n) == 1 && n) {
        while (!q.empty()) q.pop();
        for (int i = 0; i < n; i++) { scanf("%d", &x); q.push(x); }
        int ans = 0;
        for (int i = 0; i < n-1; i++) {
            int a = q.top(); q.pop();
            int b = q.top(); q.pop();
            ans += a + b;
            q.push(a+b);
        }
        printf("%d\n", ans);
    }
    return 0;
}
