#include <cstdio>
#include <iostream>
#include <vector>
#include <cstring>
#include <string>

using namespace std;
typedef long long ll;

const int MAX_N = 1000 + 3;
const int INF = 0x3f3f3f3f;
struct BigInt {
    vector<int> v;
    static const int BASE = 10;
    BigInt(ll x) {
        do {
            v.push_back(x % 10);
        } while (x /= 10);
    }
    BigInt(const string &str) {
        v.reserve(str.length());
        for (int i = str.length() - 1; i >= 0; i--) {
            v.push_back(str[i] - '0');
        }
    }
    BigInt() {}
    void removePreZero() {
        while(v.size() >= 1 && v.back() == 0) v.pop_back();
    }
    bool operator<(const BigInt &a) const {
        if (v.size() != a.v.size()) {
            return v.size() < a.v.size();
        }
        for (int i = v.size() - 1; i >= 0; i--) {
            if (v[i] != a.v[i]) {
                return v[i] < a.v[i];
            }
        }
        return false;
    }
    bool operator>(const BigInt &a) const { return a < *this; }
    bool operator<=(const BigInt &a) const { return !(a < *this); }
    bool operator>=(const BigInt &a) const { return !(*this < a); }
    bool operator!=(const BigInt &a) const { return a < *this || a > *this; }
    bool operator==(const BigInt &a) const { return !(a < *this) && !(a > *this); }
    BigInt operator+(const BigInt &a) const {
        BigInt res;
        int sum = 0;
        for (int i = 0; i < max(a.v.size(), v.size()); i++) {
            if (i < a.v.size()) sum += a.v[i];
            if (i < v.size()) sum += v[i];
            res.v.push_back(sum % BASE);
            sum /= BASE;
        }
        if (sum) res.v.push_back(sum);
        res.removePreZero();
        return res;
    }
    BigInt operator-(const BigInt &a) const {
        BigInt res;
        int dif = 0;
        for (int i = 0; i < max(a.v.size(), v.size()); i++) {
            if (i < v.size()) dif += v[i];
            if (i < a.v.size()) dif -= a.v[i];
            if (dif >= 0) {
                res.v.push_back(dif);
                dif = 0;
            }
            else {
                res.v.push_back((dif + BASE) % BASE);
                dif = -1;
            }
        }
        res.removePreZero();
        return res;
    }
    BigInt operator*(const BigInt &a) const {
        BigInt res;
        res.v.resize(v.size() + a.v.size(), 0);
        for (int i = 0; i < v.size(); i++) {
            for (int j = 0; j < a.v.size(); j++) {
                res.v[i + j] += v[i] * a.v[j];
                res.v[i + j + 1] += res.v[i + j] / BASE;
                res.v[i + j] %= BASE;
            }
        }
        res.removePreZero();
        return res;
    }
};
ostream& operator<<(ostream &out, const BigInt &x) {
    for (int i = x.v.size() - 1; i >= 0; i--) {
        out << x.v[i];
    }
    return out;
}
istream& operator>>(istream &in, BigInt &x) {
    string str;
    in >> str;
    x = BigInt(str);
    return in;
}

const int maxn = 110;
BigInt F1, F2, F3;

int main()
{
    int n;
    cin >> n;
    if (n == 1) 
        puts("1");
    else if (n == 2) 
        puts("5");
    else {
        F1 = 1, F2 = 5;
        for (BigInt i = 3; i <= n; i = i + 1) {
            F3 = F2 * 3 - F1 + 2;
            F1 = F2; F2 = F3;
        }
        cout << F3 << endl;
    }

    return 0;
}