#include <iostream>
#include <vector>
using namespace std;

// Sieve of Eratosthenes: returns all primes <= n
vector<int> sieve(int n) {
    vector<bool> isPrime(n + 1, true);
    vector<int> primes;

    if (n >= 0) isPrime[0] = false;
    if (n >= 1) isPrime[1] = false;

    for (int p = 2; p * p <= n; p++) {
        if (isPrime[p]) {
            for (int i = p * p; i <= n; i += p) {
                isPrime[i] = false;
            }
        }
    }

    for (int i = 2; i <= n; i++) {
        if (isPrime[i]) {
            primes.push_back(i);
        }
    }

    return primes;
}

// Function replacing main logic
void printPrimes(int n) {
    vector<int> res = sieve(n);

    for (auto ele : res) {
        cout << ele << ' ';
    }
    cout << endl;
}

int main() {
    printPrimes(35);
    return 0;
}
