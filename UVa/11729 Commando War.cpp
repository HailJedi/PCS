#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

struct Job {
    int b, j;
    bool operator < (const Job &x) const {
        return j > x.j;
    }
};
vector<Job> jobs;
int n, kase;

void solve() {
    sort(jobs.begin(), jobs.end());
    int now = 0, ans = 0;
    for (int i = 0; i < jobs.size(); i++) {
        Job &nj = jobs[i];
        ans = max(ans, now + nj.b + nj.j);
        now += nj.b;
    }
    cout << "Case " << ++kase << ": "<< ans << endl;
}

int main() {
    ios::sync_with_stdio(false);
    while (cin >> n && n) {
        jobs.clear();
        for (int i = 1; i <= n; i++) {
            int b, j;
            cin >> b >> j;
            jobs.push_back((Job){b, j});
        }
        solve();
    }
    return 0;
}
