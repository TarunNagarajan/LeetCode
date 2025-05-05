#include <iostream>
#include <unordered_map>
#include <algorithm>
using namespace std;

unordered_map<int, int> cache;

int cycle_length(int n) {
    
    if (n == 1) return 1;
    if (cache.count(n)) return cache[n];
    
    int len;
    
    if (n & 1) {
        len = 1 + cycle_length(3 * n + 1);
    } else {
        len = 1 + cycle_length(n / 2);
    }
    
    cache[n] = len;
    return len;
    
}

int max_length(int i, int j) {
    int low = min(i, j);
    int high = max(i, j);
    
    int max_len = 0;
    for (int n = low; n <= high; ++n) {
        int len = cycle_length(n);
        max_len = max(max_len, len);
    }
    
    return max_len;
}

int main() {
    int i; 
    int j;
    
    while (cin >> i >> j) {
        int result = max_length(i, j);
        cout << i << " " << j << " " << result << endl;
    }
    
    return 0;
}
