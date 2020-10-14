/**
 *  @Source: myself
 *  @Author: Tieway59
 *  @Complexity: $O(N)$
 *  @Description:
 *      统计一个串长度大于1并且是奇数的本质不同回文子串个数。
 *
 *  @Example:
 *      5
 *      ababa
 *
 *      ans = 3
 *
 *  @Verification:
 *      2020 ICPC UNCPC H. Happy game
 *      https://codeforces.ml/gym/102700/problem/H
 */

#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const int PAMN = 1e5 + 59;

struct PAM {
    int tot, las;
    int ch[PAMN][26];
//    int cnt[PAMN];
    int len[PAMN];
    int fail[PAMN];
//    int npos[PAMN];

    int pos;
    char s[PAMN];

    int node(int l) {
        tot++;
        memset(ch[tot], 0, sizeof(ch[tot]));
        len[tot] = l;
//        cnt[tot] = 0;
        fail[tot] = 0;
//        npos[tot] = pos;
        return tot;
    }

    void init() {
        tot = -1;
        las = 0;
        pos = 0;
        s[pos] = '$';   // s = '$......'
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
//        cnt[las]++;
    }
} pam;

char s[PAMN];
ll pre[PAMN];
const ll MOD = 1e9 + 7;

ll fpow(ll a, ll b) {
    ll res = 1;
    while (b) {
        if (b & 1) res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}

int main() {
    pam.init();
    int n;
    scanf("%d %s", &n, s + 1);
    for (int i = 1; i <= n; i++) {
        pam.extend(s[i]);
    }

    ll ans = 0;

    for (int i = 2; i <= pam.tot; ++i) {
        if (pam.len[i] > 1)
            ans += pam.len[i] % 2;
    }

    printf("%lld\n", ans);
    return 0;
}
