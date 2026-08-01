#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<int> kmp(const string& pat, const string& txt) {
    int n = txt.length();
    int m = pat.length();
    vector<int> lps(m);
    vector<int> res;

    lps[0] = 0;
    int len = 0;
    int k = 1;

    while (k < m) {
        if (pat[k] == pat[len]) {
            len++;
            lps[k] = len;
            k++;
        } else {
            if (len != 0) len = lps[len - 1];
            else {
                lps[k] = 0;
                k++;
            }
        }
    }

    int i = 0;
    int j = 0;

    while (i < n) {
        if (txt[i] == pat[j]) {
            i++;
            j++;

            if (j == m) {
                res.push_back(i - j);
                j = lps[j - 1];
            }
        } else {
            if (j != 0) j = lps[j - 1];
            else i++;
        }
    }

    return res;
}