#include <iostream>
using namespace std;

int main() {
    int n;
    int s;
    int x;
    int i;
    cin >> n;
    s = 0;
    i = 0;
    while (i < n) {
        cin >> x;
        s = s + x;
        i = i + 1;
    }
    cout << s;
    return 0;
}