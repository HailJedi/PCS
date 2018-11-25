#include <iostream>
#include <vector>
using namespace std;

const int maxans = 13;
int data[maxans+1];
int n;

bool dfs(int d, int maxd) {
    if (data[d] == n) return true;
    if (d == maxd) return false;
    
    int maxv = data[0];
    for (int i = 1; i <= d; i++) {
        maxv = max(maxv, data[i]);
    }
    
    if(maxv<<(maxd-d) < n) return false;
    
    for(int i = d; i >= 0; i--) {
        data[d+1] = data[d] + data[i];
        if(dfs(d+1, maxd)) return true;
        data[d+1] = data[d] - data[i];
        if(dfs(d+1, maxd)) return true;
    }
    return false;
}

int solve() {
    if(n == 1) return 0;
    data[0] = 1;
    for (int maxd = 0; maxd < maxans; maxd++) {
        if(dfs(0, maxd)) return maxd;
    }
    return maxans;
}

int main() {
    // insert code here...
    ios::sync_with_stdio(false);
    
    while (cin >> n && n) {
        cout << solve() << endl;
    }
    
    return 0;
}
