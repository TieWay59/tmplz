/**
 *  @Source: myself
 *  @Author: Tieway59
 *  @Complexity: $O(|S|)$
 *  @Description:
 *      长度为n的数字串，只包含数字1~9，求所有本质不同的回文串代表的整数之和
 *      MOD 1e9+7
 *
 *  @Example:
 *      "1232111"：ans = 1+11+111+2+3+232+12321 = 12681
 *
 *  @Verification:
 *      2018 ICPC 南京站 网络赛 I Skr
 *      https://nanti.jisuanke.com/t/A1955
 */

#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const int PAMN = 2e6 + 59;

struct PAM {
    int tot, las;
    int ch[PAMN][26];
//    int cnt[PAMN];
    int len[PAMN];
    int fail[PAMN];
    int npos[PAMN];

    int pos;
    char s[PAMN];

    int node(int l) {
        tot++;
        memset(ch[tot], 0, sizeof(ch[tot]));
        len[tot] = l;
//        cnt[tot] = 0;
        fail[tot] = 0;
        npos[tot] = pos;
        return tot;
    }

    void init() {
        tot = -1;
        las = 0;
        pos = 0;
        s[pos] = '*';   // s = '*......'
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
        int d = c - '0';
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
    scanf("%s", s + 1);
    int n = strlen(s + 1);
    for (int i = 1; i <= n; i++) {
        pam.extend(s[i]);
    }

    ll ans = 0;

    for (int i = 1; i <= n; ++i) {
        pre[i] = (pre[i - 1] * 10 + s[i] - '0') % MOD;
    }

    for (int i = 2; i <= pam.tot; ++i) {
        int len = pam.len[i];
        int r = pam.npos[i];
        int l = r - len;
        ans = (ans + pre[r] + MOD - pre[l] * fpow(10, len) % MOD) % MOD;
    }

    printf("%lld\n", ans);
    return 0;
}