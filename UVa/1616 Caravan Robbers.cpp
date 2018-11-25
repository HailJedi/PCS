#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
using namespace std;

typedef pair<double, double> Pair;
Pair intv[100000];

long long gcd(long long a, long long b) {
    return b == 0 ? a : gcd(b, a %b);
}

int n;

bool deal(const double len) {
    double lst = 0;
    for (int i = 0; i < n; i++) {
        lst = (lst >= intv[i].first ? lst : intv[i].first);
        if (lst + len > intv[i].second) return false;
        lst += len;
    }
    return true;
}

int main()
{
    
    // freopen("read.txt", "r", stdin);
    // freopen("write.txt", "w", stdout);
    
    ios::sync_with_stdio(false);
    
    double low, up;
    while (cin >> n) {
        low = 0; up = 1000010;
        for (int i = 0; i < n; i++) {
            cin >> intv[i].first >> intv[i].second;
            up = min(up, intv[i].second - intv[i].first);
        }
        sort(intv, intv + n);
        // up += 0.0000001;
        int cnt = 0;
        while (cnt++ < 100 && low < up) {
            double mid = low + (up - low) / 2;
            if (deal(mid)) low = mid;
            else up = mid;
        }
        low = up;
        long long a = low * 1000000, b = 1000000;
        long long g = gcd(a, b);
        cout << a / g << '/' << b / g << endl;
    }
    return 0;
}

