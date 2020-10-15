/**
 *  @Source: myself
 *  @Author: Tieway59
 *  @Complexity: $O(N)$
 *  @Description:
 *      给出两个字符串A，B。
 *      求A的所有回文串在B中出现次数的和。
 *
 *      根据回文树的转移dfs序同时遍历两个图。
 *
 *  @Example:
 *      3
 *      abacab
 *      abccab
 *      faultydogeuniversity
 *      hasnopalindromeatall
 *      abbacabbaccab
 *      youmayexpectedstrongsamplesbutnow
 *
 *      Case #1: 12
 *      Case #2: 20
 *      Case #3: 18
 *
 *  @Verification:
 *      2014 ICPC 西安EC G The Problem to Slow Down You
 *      https://codeforces.com/gym/100548/attachments
 */

#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const int PAMN = 2e5 + 59;
typedef pair<int, int> pii;

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
//        npos[tot] = pos;
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
        int d = c - 'a';
        int u = jump(las);
        if (!ch[u][d]) {
            int v = node(len[u] + 2);
            fail[v] = ch[jump(fail[u])][d];
            ch[u][d] = v;
        }
        las = ch[u][d];
        cnt[las]++;
    }

    void build(char s[], int length) {
        for (int i = 0; i < length; ++i) {
            extend(s[i]);
        }
    }

    void pushcnt() {
        for (int i = tot; i > 1; i--) {
            cnt[fail[i]] += cnt[i];
        }
    }
} pam_a, pam_b;

char a[PAMN], b[PAMN];
pii stk[PAMN];
int top;

int main() {
    int kase, kaseId = 0;
    scanf("%d", &kase);
    while (kase--) {
        int na, nb;
        scanf("%s %s", a + 1, b + 1);
        na = strlen(a + 1);
        nb = strlen(b + 1);

        pam_a.init();
        pam_a.build(a + 1, na);
        pam_a.pushcnt();
        pam_b.init();
        pam_b.build(b + 1, nb);
        pam_b.pushcnt();

        for (int k = 0; k < 26; ++k) {
            if (pam_a.ch[0][k] > 0 && pam_b.ch[0][k] > 0)
                stk[top++] = pii{pam_a.ch[0][k], pam_b.ch[0][k]};
            if (pam_a.ch[1][k] > 0 && pam_b.ch[1][k] > 0)
                stk[top++] = pii{pam_a.ch[1][k], pam_b.ch[1][k]};
        }

        ll ans = 0;
        while (top) {
            int i = stk[--top].first;
            int j = stk[top].second;

            ans += pam_a.cnt[i] * 1ll * pam_b.cnt[j];

            for (int k = 0; k < 26; ++k) {
                if (pam_a.ch[i][k] > 0 && pam_b.ch[j][k] > 0)
                    stk[top++] = pii{pam_a.ch[i][k], pam_b.ch[j][k]};
            }
        }
        printf("Case #%d: %lld\n", ++kaseId, ans);
    }
    return 0;
}
