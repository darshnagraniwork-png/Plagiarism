#include <string>
#include <vector>

using namespace std;

vector<int> rabinKarp(const string& pat, const string& txt) {
    int d = 256;
    int q = 101;
    int m = pat.length();
    int n = txt.length();
    int p = 0;
    int t = 0;
    int h = 1;
    vector<int> ans;

    for (int i = 0; i < m - 1; i++) h = (h * d) % q;

    for (int i = 0; i < m; i++) {
        p = (d * p + pat[i]) % q;
        t = (d * t + txt[i]) % q;
    }

    for (int i = 0; i <= n - m; i++) {
        if (p == t) {
            bool match = true;
            for (int j = 0; j < m; j++) {
                if (txt[i + j] != pat[j]) {
                    match = false;
                    break;
                }
            }
            if (match) ans.push_back(i);
        }

        if (i < n - m) {
            t = (d * (t - txt[i] * h) + txt[i + m]) % q;
            if (t < 0) t += q;
        }
    }

    return ans;
}