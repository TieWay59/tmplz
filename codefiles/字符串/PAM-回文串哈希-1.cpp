/**
 *  @Source:myself
 *  @Author: Tieway59
 *  @Complexity: $O(N)$
 *  @Description:
 *      给出一个长度为N的字符串，要求输出一个长度为N的统计数组A
 *      A[i]表示长度为i的good substring的数量
 *      good substring ：该子串是回文串，且该子串的一半也是回文串。
 *      做法是子串哈希，PAM枚举所有子串，检查。
 *
 *  @Example:
 *      abababa
 *      7 0 0 0 3 0 0
 *
 *  @Verification:
 *      2019 杭电多校2 1009 I Love Palindrome String
 *      http://acm.hdu.edu.cn/showproblem.php?pid=6599
 */

#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const int PAMN = 3e5 + 59;

struct PAM {
    int tot, las;
    int ch[PAMN][26];
    int cnt[PAMN];
    int len[PAMN];
    int fail[PAMN];
    int npos[PAMN];

    int pos;
    char s[PAMN];

    int node(int l) {
        tot++;
        memset(ch[tot], 0, sizeof(ch[tot]));
        len[tot] = l;
        cnt[tot] = 0;
        fail[tot] = 0;
        npos[tot] = pos;    //记录第一次出现的位置
        return tot;
    }

    void init() {
        tot = -1;
        las = 0;
        pos = 0;
        s[pos] = '$';   // s = '￥......'
        node(0);      // node[0] : len =  0 偶根
        node(-1);     // node[1] : len = -1 奇根
        fail[0] = 1;
    }

    int jump(int u) {
        while (s[pos - len[u] - 1] != s[pos]) {
            u = fail[u];
        }
        return u;
    }

    void extend(char c) {
        s[++pos] = c;
        int d = c - 'a';
        int u = jump(las);
        if (!ch[u][d]) {
            int v = node(len[u] + 2);
            fail[v] = ch[jump(fail[u])][d];
            ch[u][d] = v;
        }
        las = ch[u][d];
        cnt[las]++;
//        npos[las] = pos;    // 记录最后出现的位置
    }
} pam;

char s[PAMN];
typedef long long ll;
const ll MOD = 1e9 + 7;
ll pre[PAMN];
ll ans[PAMN];

ll fpow(ll a, ll b) {
    ll res = 1;
    while (b) {
        if (b & 1) res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}

ll subhush(int l, int r) {
    l--;
    return (pre[r] + MOD - pre[l] * fpow(19491001, r - l) % MOD) % MOD;
}

int main() {

    while (scanf("%s", s + 1) != EOF) {
        int n = strlen(s + 1);
        pam.init();
        for (int i = 1; i <= n; i++) {
            pam.extend(s[i]);
            ans[i] = 0;
            pre[i] = 0;
        }

        for (int i = 1; i <= n; ++i) {
            pre[i] = (pre[i - 1] * 19491001 + (s[i] - 'a')) % MOD;
        }

        for (int i = pam.tot; i > 1; --i) {
            pam.cnt[pam.fail[i]] += pam.cnt[i];
        }

        for (int i = 2; i <= pam.tot; ++i) {
            int r = pam.npos[i];
            int l = r - pam.len[i] + 1;
            int len = pam.len[i];
            int m = (l + r) >> 1;
            if (len & 1) {
                if (subhush(l, m) == subhush(m, r)) {
                    ans[len] += pam.cnt[i];
                }
            } else {
                if (subhush(l, m) == subhush(m + 1, r)) {
                    ans[len] += pam.cnt[i];
                }
            }
        }

        for (int i = 1; i <= n; ++i) {
            printf("%lld%c", ans[i], " \n"[i == n]);
        }
    }

    return 0;
}