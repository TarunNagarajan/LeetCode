#include <bits/stdc++.h>
using namespace std;
 
int main() {
    int n;
    cin >> n;
 
    int xor_input = 0, xor_full = 0;
    int num;
 
    for (int i = 0; i < n - 1; ++i) {
        cin >> num;
        xor_input ^= num;
    }
 
    for (int i = 1; i <= n; ++i) {
        xor_full ^= i;
    }
 
    cout << (xor_input ^ xor_full) << "\n";
    return 0;
}
