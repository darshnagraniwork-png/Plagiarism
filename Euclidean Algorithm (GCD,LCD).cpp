#include <iostream>
using namespace std;

// Function to return gcd of a and b
int findGCD(int a, int b) {
    if (a == 0)
        return b;
    return findGCD(b % a, a);
}

// Function encapsulating the main logic
void computeAndPrintGCD(int a, int b) {
    int g = findGCD(a, b);
    cout << g << endl;
}

int main() {
    computeAndPrintGCD(35, 15);
    return 0;
}
