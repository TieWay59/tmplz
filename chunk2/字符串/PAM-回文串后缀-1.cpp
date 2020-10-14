/**
 *  @Source:myself
 *  @Author: Tieway59
 *  @Complexity: $O(N)$
 *  @Description:
 *      输入长度为n的串S，求S的最长双回文子串T,即可将T分为两部分X，Y，
 *      ∣X∣,∣Y∣≥1|X|,|Y|≥1∣X∣,∣Y∣≥1 且X和Y都是回文串。
 *
 *      转化成枚举后缀拼接就很好做了。
 *      思路是用PAM处理每个位置i的最长回文后缀，lb[i] (反向是rb[i])
 *      $ans = max(lb[i] + rb[i + 1])$
 *
 *  @Example:
 *      baacaabbacabb
 *      ans := 12
 *
 *  @Verification:
 *      洛谷 P4555 [国家集训队]最长双回文串
 *      https://www.luogu.com.cn/problem/P4555
 */

#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const int PAMN = 1.2e5 + 59;

struct PAM {
    int tot, las;
    int ch[PAMN][26];
    int cnt[PAMN];
    int len[PAMN];
    int fail[PAMN];
//    int npos[PAMN];

    int pos;
    char s[PAMN];

    int node(int l) {
        tot++;
        memset(ch[tot], 0, sizeof(ch[tot]));
        len[tot] = l;
        cnt[tot] = 0;
        fail[tot] = 0;
//        npos[tot] = pos;    //记录第一次出现的位置

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

    void extend(char c, int lb[]) {
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

        lb[pos] = max(lb[pos], len[las]);
//        rb[pos - len[las] + 1] = max(rb[pos - len[las] + 1], len[las]);

//        npos[las] = pos;    // 记录最后出现的位置
    }
} pam;

char s[PAMN];
int lb[PAMN];
int rb[PAMN];


int main() {

    scanf("%s", s + 1);
    int n = strlen(s + 1);

    pam.init();
    for (int i = 1; i <= n; i++) {
        lb[i] = 0;
        pam.extend(s[i], lb);
    }
    reverse(s + 1, s + 1 + n);
    pam.init();
    for (int i = 1; i <= n; i++) {
        rb[i] = 0;
        pam.extend(s[i], rb);
    }
    reverse(rb + 1, rb + 1 + n);

    int ans = 0;
    for (int i = 1; i < n; ++i) {
        ans = max(ans, lb[i] + rb[i + 1]);
    }

    printf("%d\n", ans);

    return 0;
}