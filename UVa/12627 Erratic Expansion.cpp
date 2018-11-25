#include <cstdio>
#include <iostream>
#include <cmath>
using namespace std;

int k;
long long A, B;

long long All(int k) {
    return k == 0 ? 1 : 3 * All(k-1);
}

long long F(int k, int r) {
    if (r == 0) return 0;
    if (k == 0) return 1;
    int p = 1 << (k-1);
    if (r <= p) return 2 * F(k-1, r);
    return 2 * All(k-1) + F(k-1, r - p);
}

int main()
{
    //freopen("input.in", "r", stdin);
    //freopen("output.out", "w", stdout);

    int T; cin >> T;
    int kase = 0;

    while(T--) {
        cout << "Case " << ++kase << ": ";
        cin >> k >> A >> B;

        cout << F(k, B) - F(k, A-1) << endl;
    }
    return 0;
}
