/**
 *  @Source: https://codeforces.com/blog/entry/12143
 *  @Complexity: O(n)
 *  @Description: length of largest palindrome centered at each
 *      character of string and between every consecutive pair
 *      二维数组分别表示第i个位置偶数长度和奇数长度的回文半径（不含中心位置）。
 *  @Example:
 *      s = "123321"
 *      [p[0], p[1]] := {0, 0, 0, 3, 0, 0} {0, 0, 0, 0, 0, 0}
 *      s = "12321"
 *      [p[0], p[1]] := {0, 0, 0, 0, 0} {0, 0, 2, 0, 0}
 *  @Verification:
 *      https://codeforces.com/contest/1326/submission/73742092
 */
void manacher(const string &s, vector<vector<int>> &p) {
    int n = s.size();
    p.assign(2, vector<int>(n, 0));
    for (int z = 0, l = 0, r = 0; z < 2; z++, l = 0, r = 0) {
        for (int i = 0; i < n; i++) {
            if (i < r) p[z][i] = min(r - i + !z, p[z][l + r - i + !z]);
            int L = i - p[z][i], R = i + p[z][i] - !z;
            while (L - 1 >= 0 && R + 1 < n && s[L - 1] == s[R + 1])
                p[z][i]++, L--, R++;
            if (R > r) l = L, r = R;
        }
    }
}

/**
 *  @Source: https://cp-algorithms.com/string/manacher.html
 *  @Complexity: O(n)
 *  @Description: length of largest palindrome centered at each
 *      character of string and between every consecutive pair
 *      两个数组分别表示第i个位置偶数长度和奇数长度的回文半径（含中心位置）。
 *  @Example:
 *      s = "123321"
 *      [d1, d2] := {1, 1, 1, 1, 1, 1} {0, 0, 0, 3, 0, 0}
 *      s = "12321"
 *      [d1, d2] := {1, 1, 3, 1, 1} {0, 0, 0, 0, 0}
 *  @Verification:
 *      https://codeforces.com/contest/1326/submission/73715067
 */
void manacher(const string &s, vint &d1, vint &d2) {
    int n = s.size();
    d1.assign(n, 0);
    for (int i = 0, l = 0, r = -1; i < n; i++) {
        int k = (i > r) ? 1 : min(d1[l + r - i], r - i + 1);
        while (0 <= i - k && i + k < n && s[i - k] == s[i + k]) {
            k++;
        }
        d1[i] = k--;
        if (i + k > r) {
            l = i - k;
            r = i + k;
        }
    }
    d2.assign(n, 0);
    for (int i = 0, l = 0, r = -1; i < n; i++) {
        int k = (i > r) ? 0 : min(d2[l + r - i + 1], r - i + 1);
        while (0 <= i - k - 1 && i + k < n && s[i - k - 1] == s[i + k]) {
            k++;
        }
        d2[i] = k--;
        if (i + k > r) {
            l = i - k - 1;
            r = i + k;
        }
    }
}