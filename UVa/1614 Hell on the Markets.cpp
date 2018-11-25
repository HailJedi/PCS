#include <stdio.h>
#include <algorithm>
using namespace std;

int n;
pair<int, int> A[100000];
int sym[100000];

int main() {
    
//    freopen("out.txt", "w", stdout);
    
    while (scanf("%d", &n) == 1) {
        
        long long tot = 0;
        for (int i = 0; i < n; i++) {
            scanf("%d", &A[i].first);
            A[i].second = i;
            tot += A[i].first;
        }
        
        if (tot % 2) { puts("No"); continue; }
        puts("Yes");
        
        sort(A, A+n); tot /= 2;
        
        /*
        for (int i = 0; i < n; i++)
            if (tot >= A[i].first) { tot -= A[i].first; sym[A[i].second] = 1; }
            else sym[A[i].second] = -1;
        */
        
        for (int i = n-1; i >= 0; i--)
            if (tot >= A[i].first) { tot -= A[i].first; sym[A[i].second] = 1; }
            else sym[A[i].second] = -1;
        
        
        for (int i = 0; i < n-1; i++)
            printf("%d ", sym[i]);
        printf("%d\n", sym[n-1]);
    }
    return 0;
}
