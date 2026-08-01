#include <iostream>
using namespace std;

// Large modulo constant
long long int mod = 1e18 + 7;

// Forward declaration of binMultiply so binExp can use it
long long binMultiply(long long a, long long b);

// Large Exponentiation using Binary Multiplication
// Computes (a^b) % mod where a, b < 10^18
// Time Complexity: O(log^2(b))
long long binExp(long long a, long long b) {
    long long ans = 1;
    while (b > 0) {
        if (b & 1) { // Check if lowest bit is set
            ans = binMultiply(ans, a);
        }
        a = binMultiply(a, a); 
        b >>= 1; // Right-shift to process next bit
    }
    return ans;
}

// Binary Multiplication to prevent overflow during (a * b) % mod
// Computes (a * b) % mod using repeated addition
// Time Complexity: O(log(b))
long long binMultiply(long long a, long long b) {
    long long ans = 0;
    while (b > 0) {
        if (b & 1) {
            ans = (ans + a) % mod;
        }
        a = (a + a) % mod; // Double 'a' for next bit position
        b >>= 1;
    }
    return ans;
}

// Function replacing int main logic
void solve(long long a, long long b) {
    cout << binExp(a, b) << "\n";      // Calculates a^b % mod
    cout << binMultiply(a, b) << "\n"; // Calculates (a * b) % mod
}
