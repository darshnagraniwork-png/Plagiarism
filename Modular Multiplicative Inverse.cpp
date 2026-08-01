#include <iostream>
using namespace std;

// Function to find modular inverse using brute force O(m)
int modInverse(int n, int m)
{
    // Try all values from 1 to m-1
    for (int x = 1; x < m; x++)
    {
        // Check if (n * x) % m == 1
        if (((n % m) * (x % m)) % m == 1)
            return x;
    }

    return -1; // Inverse doesn't exist (e.g., if gcd(n, m) != 1)
}

// Function replacing int main logic
void solve(int n, int m)
{
    cout << modInverse(n, m) << "\n";
}
