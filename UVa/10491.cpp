/*
Created 2018-11-21
"Cows and Cars"
*/

#include <bits/stdc++.h>

using namespace std;

int main() {
	double cows, cars, show;
	while (scanf("%lf %lf %lf", &cows, &cars, &show) == 3) {
		double tot = cows + cars;
		printf("%.5lf\n", cars / tot * (cars - 1) / (tot - show - 1) + (tot - cars) / tot * cars / (tot - show - 1));
	}
	return 0;
}
