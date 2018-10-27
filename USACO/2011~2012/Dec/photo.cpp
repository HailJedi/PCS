/*
Created 2018-10-26
"USACO 2011 December Contest, Gold Division
Problem 1. Cow Photography"
😁
*/

#include <bits/stdc++.h>

using namespace std;

const int N = 20000 + 5;

map<int, int> pos[5];

bool cmp(int x, int y) {
    int cnt = 0;
    for (int i = 0; i < 5; i++) {
        cnt += pos[i][x] < pos[i][y];
    }
    return cnt >= 3;
}

int main() {
    int n;
    scanf("%d", &n);
    vector<int> ans;
    for (int i = 0; i < 5; i++) {
        for (int j = 1; j <= n; j++) {
            int x;
            scanf("%d", &x);
            pos[i][x] = j;
            if (i == 0) {
                ans.push_back(x);
            }
        }
    }
    sort(ans.begin(), ans.end(), cmp);
    for (int e: ans) {
        printf("%d\n", e);
    }
    return 0;
}
