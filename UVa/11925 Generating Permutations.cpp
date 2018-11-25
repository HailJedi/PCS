#include <iostream>
#include <deque>
#include <vector>
using namespace std;

deque<int> perm;
vector<int> ans;
int n, A;

bool done() {
    for (int i = 0; i < n; i++)
        if (perm[i] != i + 1) return false;
    return true;
}

int main()
{
    ios::sync_with_stdio(false);
    while (cin >> n && n) {
        perm.clear();
        for (int i = 1; i <= n; i++) {
            cin >> A;
            perm.push_back(A);
        }
        ans.clear();
        while (!done()) {
            if (perm[0] > perm[1] && perm[0] != n) {
                ans.push_back(1);
                swap(perm[0], perm[1]);
            }
            if (!done()) {
                int p = perm.back(); perm.pop_back(); perm.push_front(p);
                ans.push_back(2);
            }
        }
        for (vector<int>::reverse_iterator it = ans.rbegin(); it != ans.rend(); ++it)
            cout << *it;
        cout << endl;
    }
    return 0;
}

