#include <iostream>

using namespace std;
typedef unsigned long long ull;

ull m, n;
const ull P = 100003;

ull Pow(ull a, ull n) { // a^n
	ull ret = 1;
	while (n) {
		if (n & 1) {
			ret *= a;
			ret %= P;
		}
		n >>= 1;
		a *= a;
		a %= P;
	}
	return ret;
}

int main() {
	cin >> m >> n;
	cout << (Pow(m, n) % P - m * Pow(m-1, n-1) % P + P * P) % P;
	return 0;
}