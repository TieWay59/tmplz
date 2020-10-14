/**
 *  @Source: https://codeforces.com/contest/1326/submission/73675730
 *  @Author: tourist
 *  @Complexity: O(n)
 *  @Description:
 *      得到经过填充长2n-1的回文半径数组，填充模式为：a$b$c
 *      + 由于串实际没有被修改，常数喜人
 *      + 同时适配 char* 与 string，各取所爱
 *      + 你不满意可以改成全局变量数组，简简单单
 *      + 此处回文半径不含中心
 *
 *  @Example:
 *      char s[] = "123321";
 *      vint p = manacher(6, s);
 *      // [p] := {0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0}
 *
 *      string s[] = "12321";
 *      vint p = manacher(s);
 *      // [p] := {0, 0, 0, 0, 2, 0, 0, 0, 0}
 *
 *  @Verification:
 *      https://codeforces.com/contest/1326/submission/73675730
 */
template<typename T>
vector<int> manacher(int n, const T &s) {
    if (n == 0) {
        return vector<int>();
    }
    vector<int> res(2 * n - 1, 0);
    int l = -1, r = -1;
    for (int z = 0; z < 2 * n - 1; z++) {
        int i = (z + 1) >> 1;
        int j = z >> 1;
        int p = (i >= r ? 0 : min(r - i, res[2 * (l + r) - z]));
        while (j + p + 1 < n && i - p - 1 >= 0) {
            if (!(s[j + p + 1] == s[i - p - 1])) {
                break;
            }
            p++;
        }
        if (j + p > r) {
            l = i - p;
            r = j + p;
        }
        res[z] = p;
    }
    return res;
}

template<typename T>
vector<int> manacher(const T &s) {
    return manacher((int) s.size(), s);
}