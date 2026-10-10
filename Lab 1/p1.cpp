#include <iostream>
using namespace std;

struct Cerc {
    float r;
    float p;
    float a;
};

int main() {
    Cerc c;
    float pi;
    pi = 3.1415;
    cin >> c.r;
    c.p = 2.0 * pi * c.r;
    c.a = pi * c.r * c.r;
    cout << c.p;
    cout << c.a;
    return 0;
}