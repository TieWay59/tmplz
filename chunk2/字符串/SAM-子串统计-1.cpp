/**
 *  @Source: myself
 *  @Author: Tieway59
 *  @Complexity: $O(|S|)$
 *  @Description:
 *      求原串S中出现次数在[A,B]之间的子串的种数
 *      ！注意修改 build 中的字符类型
 *      ！注意extend是int参数
 *      ！注意SAM外数组的大小
 *
 *  @Example:
 *      AAA 2 3
 *      ABAB 2 2
 *
 *      2
 *      3
 *
 *  @Verification:
 *      2018 ICPC 焦作站 网络赛 H
 *      https://nanti.jisuanke.com/t/A2018
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
            extend(s[i] - 'A'); // char type
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


int A, B;
char s[MAXN];
int stk[SAMN], top;    // 小心范围
int deg[SAMN];            // 小心范围

int main() {

    while (scanf("%s %d %d", s, &A, &B) != EOF) {
        sam.init();
        sam.build(s, strlen(s));
        top = 0;

        for (int i = 0; i <= sam.tot; ++i) {
            deg[i] = 0;
        }
        for (int i = 2; i <= sam.tot; ++i) {
            deg[sam.link[i]]++;
        }
        for (int i = 2; i <= sam.tot; ++i) {
            if (deg[i] == 0) {
                stk[++top] = i;
            }
        }

        ll ans = 0;

        while (top) {
            int u = stk[top--];

            sam.cnt[sam.link[u]] += sam.cnt[u];
            if (0 == (--deg[sam.link[u]]) &&
                sam.link[u] != sam.begin) {
                stk[++top] = sam.link[u];
            }

            if (A <= sam.cnt[u] && sam.cnt[u] <= B) {
                ans += sam.len[u] - sam.len[sam.link[u]];
            }

        }
        printf("%lld\n", ans);
    }

    return 0;
}
