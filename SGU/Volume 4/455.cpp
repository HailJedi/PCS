#include <bits/stdc++.h>

using namespace std;

long long A, B, C;

long long f(long long x) {
  return (A * x + x % B) % C;
}

int main() {
  cin >> A >> B >> C;
  
}
