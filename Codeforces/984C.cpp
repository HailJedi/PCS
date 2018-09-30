#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
ll p, q, b, Q;

ll gcd(ll a, ll b) {
	return !b ? a : gcd(b, a%b);
}

vector<ll> prime;
const int MAX_PRIME = 1e3;
bool isprime[MAX_PRIME+5];

void generate_prime() {
	for (int i = 2; i <= MAX_PRIME; i++) isprime[i] = true;
	for (int i = 2; i <= MAX_PRIME; i++)
		if (isprime[i]) {
			prime.push_back(i);
			for (int j = i*2; j <= MAX_PRIME; j += i)
				isprime[j] = false;
		}
}

int main() {
	generate_prime();
	scanf("%lld", &Q);
	while (Q--) {
		scanf("%lld %lld %lld", &p, &q, &b);
		if (p % q == 0) {
			puts("Finite");
			continue;
		}
		ll g = gcd(p, q);
		p /= g, q /= g;
		bool ok = true;
		for (auto e: prime) {
			if (e > max(q, b)) break;
			if (q % e == 0 && b % e != 0) {
				ok = false; break;
			}
			while (q % e == 0) q /= e;
			while (b % e == 0) b /= e;
		}
		if (!ok) { puts("Infinite"); continue; }
		while (true) {
			ll gd = gcd(q, b);
			if (gd == 1) break;
			q /= gd; 
			if (q == 1) break;
		}
		if (q == 1) puts("Finite");
		else puts("Infinite");
	}
	return 0;
}