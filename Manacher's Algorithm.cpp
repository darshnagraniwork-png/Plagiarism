#include <string>
#include <vector>

using namespace std;

class Manacher {
public:
    vector<int> p;
    string ms;

    Manacher(const string& s) {
        ms = "@";
        for (char c : s) ms += "#" + string(1, c);
        ms += "#$";

        int n = ms.size();
        p.assign(n, 0);
        int l = 0;
        int r = 0;

        for (int i = 1; i < n - 1; i++) {
            int mirror = l + r - i;

            if (i < r) p[i] = min(r - i, p[mirror]);

            while (ms[i + 1 + p[i]] == ms[i - 1 - p[i]]) p[i]++;

            if (i + p[i] > r) {
                l = i - p[i];
                r = i + p[i];
            }
        }
    }

    int getLongest(int cen, int odd) {
        int pos = 2 * cen + 2 + !odd;
        return p[pos];
    }

    bool check(int l, int r) {
        int len = r - l + 1;
        int cen = (l + r) / 2;
        return len <= getLongest(cen, len % 2);
    }
};