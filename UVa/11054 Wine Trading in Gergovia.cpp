#include <iostream>
#include <cmath>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    int n;
    while (cin >> n && n) {
        long long x, res = 0, last = 0;
        for (int i = 0; i < n; i++) {
            cin >> x;
            res += abs(last);
            last += x;
        }
        cout << res << endl;
    }
    return 0;
}
