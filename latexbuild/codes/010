/**
 *  @Source: myself
 *  @Author: Tieway59
 *  @Complexity: $|S|$
 *  @Description:
 *      给一个串S，询问Q个串ti最少需要几个S的字串可以拼成。
 *      |S| -> 2e5, sum(|ti|) -> 2e5
 *      每次匹配一个串，失配就回到root
 *
 *  @Example:
 *      SANTIAGO
 *      3
 *      TITA
 *      SANTIAGO
 *      NAS
 *
 *      3
 *      1
 *      3
 *
 *  @Verification:
 *      2019 ICPC Latin American Regional Contests G
 *      https://codeforces.com/gym/102428/problem/G
 */

#include<stdio.h>
#include<string.h>
#include<iostream>

using namespace std;
typedef long long ll;

const int MAXN = 2e5 + 59;
const ll MOD = 998244353;

const int SAMN = MAXN << 1;

struct SAM {
    const int begin = 1;

    int nxt[SAMN][26];
    int link[SAMN];
    int len[SAMN];
//    int cnt[SAMN];

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
//        cnt[id] = int(is_endpos);
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


int n;
char s[MAXN], t[MAXN];

int main() {

    scanf("%s", s);
    scanf("%d", &n);

    sam.build(s, strlen(s));

    for (int _ = 0; _ < n; ++_) {
        scanf("%s", t);
        int len = strlen(t);
        int i = 0;
        int j = sam.begin;
        int res = 1;

        while (i < len) {
            int ch = t[i] - 'A';
            if (sam.nxt[j][ch] == 0) {
                j = sam.begin;

                if (sam.nxt[j][ch] == 0) {
                    res = -1;
                    break;
                } else {
                    res++;
                }
            }
            j = sam.nxt[j][ch];
            i = i + 1;
        }
        printf("%d\n", res);
    }

    return 0;
}
