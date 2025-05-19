#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    cin >> n;

    vector<int> array(n);
    for (int i = 0; i < n; ++i) {
        cin >> array[i];
    }

    long long moves = 0;

    for (int i = 1; i < n; ++i) {
        if (array[i] < array[i - 1]) {
            moves += (array[i - 1] - array[i]);
            array[i] = array[i - 1]; // increase current to match previous
        }
    }

    cout << moves << endl;

    return 0;
}
