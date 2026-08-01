#include <iostream>
#include <vector>
using namespace std;

// Extended Euclidean Algorithm to find modular inverse
// Computes x such that (a * x) % m == 1
long long extGCD(long long a, long long m, long long &x, long long &y) {
    if (m == 0) {
        x = 1;
        y = 0;
        return a;
    }
    long long x1, y1;
    long long gcd = extGCD(m, a % m, x1, y1);
    x = y1;
    y = x1 - y1 * (a / m);
    return gcd;
}

// Function to find modular inverse of 'a' under modulo 'm'
long long modInverse(long long a, long long m) {
    long long x, y;
    long long g = extGCD(a, m, x, y);
    if (g != 1) {
        return -1; // Inverse doesn't exist if gcd(a, m) != 1
    }
    return (x % m + m) % m; // Ensure positive result
}

/**
 * Solves the system of congruences:
 * x ≡ rem[0] (mod num[0])
 * x ≡ rem[1] (mod num[1])
 * ...
 * x ≡ rem[k-1] (mod num[k-1])
 *
 * Requirements: All moduli in 'num' must be pairwise coprime.
 */
long long findMinX(const vector<long long>& num, const vector<long long>& rem) {
    long long N = 1;
    int k = num.size();

    // 1. Calculate the product of all moduli
    for (int i = 0; i < k; i++) {
        N *= num[i];
    }

    long long result = 0;

    // 2. Apply the CRT formula: sum(rem[i] * Ni * M_inv[i]) % N
    for (int i = 0; i < k; i++) {
        long long Ni = N / num[i];
        long long inv = modInverse(Ni, num[i]);

        if (inv == -1) {
            cout << "Error: Moduli are not pairwise coprime.\n";
            return -1;
        }

        result = (result + rem[i] * Ni % N * inv % N) % N;
    }

    return (result + N) % N;
}

// Function replacing int main logic
void solveCRT(const vector<long long>& num, const vector<long long>& rem) {
    long long x = findMinX(num, rem);
    if (x != -1) {
        cout << "Minimum value x = " << x << "\n";
    }
}
