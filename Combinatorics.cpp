#include <iostream>
#include <vector>
using namespace std;

// Calculates Factorial: n!
long long factorial(int n) {
    long long ans = 1;
    for (int i = 2; i <= n; i++) {
        ans *= i;
    }
    return ans;
}

// Calculates Permutations: nPr = n! / (n - r)!
long long nPr(int n, int r) {
    if (r < 0 || r > n) return 0;
    long long ans = 1;
    for (int i = 0; i < r; i++) {
        ans *= (n - i);
    }
    return ans;
}

// Calculates Combinations: nCr = n! / (r! * (n - r)!)
long long nCr(int n, int r) {
    if (r < 0 || r > n) return 0;
    if (r == 0 || r == n) return 1;
    if (r > n / 2) r = n - r; // Symmetry property: nCr = nC(n-r)

    long long ans = 1;
    for (int i = 1; i <= r; i++) {
        ans = ans * (n - r + i) / i;
    }
    return ans;
}

// Function encapsulating basic combinatorics operations
void solveCombinatorics(int n, int r) {
    cout << "Factorial(" << n << ") = " << factorial(n) << "\n";
    cout << n << "P" << r << " = " << nPr(n, r) << "\n";
    cout << n << "C" << r << " = " << nCr(n, r) << "\n";
}
