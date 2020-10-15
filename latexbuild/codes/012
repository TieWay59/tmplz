/**
 *  @Source: myself
 *  @Author: Tieway59
 *  @Complexity: $O(|S|)$
 *  @Description:
 *      求原串S中出现次数恰号是K的子串的种数
 *      ！注意修改 build 中的字符类型
 *      ！注意extend是int参数
 *      ！注意SAM外数组的大小
 *
 *  @Example:
 *      2
 *      2
 *      abcabc
 *      3
 *      abcabcabcabc
 *
 *      6
 *      9
 *
 *  @Verification:
 *      2017 ICPC 沈阳站 网络赛 A
 *      acm.hdu.edu.cn/showproblem.php?pid=6194
 *
 */
#include<stdio.h>
#include<string.h>
#include<iostream>

using namespace std;
typedef long long ll;

const int MAXN = 1e5 + 59;
const ll MOD = 998244353;

const int SAMN = MAXN << 1;

struct SAM {
    const int begin = 1;

    int nxt[SAMN][26];
    int link[SAMN];
    int len[SAMN];
    int cnt[SAMN];

    int las = begin;    // last state
    int tot = 1;        // total states

    inline void init() {
        las = nuw(begin, false);
        tot = 1;
    }

    // start from zero
    inline void build(char s[], int length) {
        for (int i = 0; i < length; ++i) {
            extend(s[i] - 'a');
        }
    }

    // new node
    int nuw(int id, bool is_endpos) {
        memset(nxt[id], 0, sizeof(nxt[id]));
        len[id] = link[id] = 0;
        cnt[id] = int(is_endpos);
        return id;
    }

    inline void extend(int c) {
        int p = las;
        int cur = nuw(++tot, true);
        len[cur] = len[p] + 1;
        las = cur;

        while (p > 0 && !nxt[p][c]) {
            nxt[p][c] = cur;
            p = link[p];
        }

        if (p == 0) {
            link[cur] = 1;
        } else {
            int q = nxt[p][c];
            if (len[q] == len[p] + 1) {
                link[cur] = q;
            } else {
                int clone = nuw(++tot, false);
                memcpy(nxt[clone], nxt[q], sizeof(nxt[clone]));
                link[clone] = link[q];
                len[clone] = len[p] + 1;
                link[q] = link[cur] = clone;
                while (p > 0 && nxt[p][c] == q) {
                    nxt[p][c] = clone;
                    p = link[p];
                }
            }
        }
    }
} sam;

int kase;
int n;
int k;
char s[MAXN];

int deg[SAMN];
int stk[SAMN], top;

int main() {
    scanf("%d", &kase);
    while (kase--) {
        scanf("%d", &k);
        scanf("%s", s);
        n = strlen(s);

        top = 0;
        sam.init();
        sam.build(s, n);
        memset(deg, 0, (sam.tot + 5) * sizeof(deg[0]));

        for (int i = sam.begin + 1; i <= sam.tot; ++i) {
            deg[sam.link[i]] += 1;
        }

        ll ans = 0;
        for (int u = sam.tot; u > sam.begin; --u) {
            if (deg[u] == 0 && u != sam.begin) {
                stk[top++] = u;
            }
        }

        while (top) {
            int v = stk[--top];
            int u = sam.link[v];

            if (sam.cnt[v] == k) {
                ans += sam.len[v] - sam.len[u];
            }

            sam.cnt[u] += sam.cnt[v];
            if (0 == (--deg[u]) && u != sam.begin) {
                stk[top++] = u;
            }
        }
        printf("%lld\n", ans);
    }

    return 0;
}
