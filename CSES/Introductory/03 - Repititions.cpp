#include <bits/stdc++.h>
using namespace std;
 
int main() {
    string s;
    cin >> s;
    
    char current = s[0];
    int counter = 1;
    int maxi = 1;
    
    for (int i = 1; i < s.size(); ++i) {
        if (s[i] == current) {
            counter++;
        } else {
            current = s[i];
            counter = 1;
        }
        maxi = max(maxi, counter);
    }
    
    cout << maxi << "\n";
    return 0;
