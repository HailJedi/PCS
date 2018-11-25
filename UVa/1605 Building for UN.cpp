#include <iostream>
#include <cstring>
using namespace std;

const string letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

int main() {
    int n;
    while (cin >> n && n) {
        cout << 2 << ' ' << n << ' ' << n << endl;
        for (int r = 0; r < n; r++) {
            for (int c = 0; c < n; c++)
                cout << letters[c];
            cout << endl;
        } cout << endl;
        for (int r = 0; r < n; r++) {
            for (int c = 0; c < n; c++)
                cout << letters[r];
            cout << endl;
        } cout << endl;
    }
    return 0;
}
