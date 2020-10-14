#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const ll mod = 1e9 + 7;
const int MAXN = 500000 + 59;
const int inf = 1e9 + 5;

// Aho–Corasick algorithm, finite-state machine
template<const int NODEsetsize, const int CHARsetsize>
struct Aho_Corasick_FSM {

    int trie[NODEsetsize][CHARsetsize], cntNd;
    int fail[NODEsetsize];
    int end[NODEsetsize];
    int root;

    inline int newNd() {
        for (int i = 0; i < CHARsetsize; ++i) trie[cntNd][i] = -1;
        end[cntNd] = 0;
        return cntNd++;
    }

    // hash char to a proper int ID;
    inline int hashChar(const char &c) { return c - 'a'; }

    // what will be changed when reaching an end node;
    inline void endOperation(const int &id) { end[id]++; }

    inline void init() {
        cntNd = 0;
        root = newNd();
    }

    // insert pattern, ensure p[len-1]==0
    inline void insert(const char p[]) {
        int cur = root;
        for (int j = 0, i; p[j]; ++j) {
            i = hashChar(p[j]);
            cur = (~trie[cur][i]) ? trie[cur][i] : trie[cur][i] = newNd();
            //            if (trie[cur][i] == -1) trie[cur][i] = newNd();
            //            cur = trie[cur][i];
        }
        endOperation(cur);
    }

    inline void build() {
        int cur = root;
        fail[root] = root;
        queue<int> que;
        for (int i = 0; i < CHARsetsize; ++i) {
            if (~trie[cur][i]) {
                fail[trie[cur][i]] = root;
                que.push(trie[cur][i]);
            } else {
                trie[cur][i] = root;
            }
        }
        while (!que.empty()) {
            cur = que.front();
            que.pop();

            for (int i = 0; i < CHARsetsize; ++i) {
                if (~trie[cur][i]) {
                    fail[trie[cur][i]] = trie[fail[cur]][i];
                    que.push(trie[cur][i]);
                } else {
                    trie[cur][i] = trie[fail[cur]][i];
                }
            }
        }
    }

    // dictionary-matching target, differs by problem
    inline int query(const char t[]) {
        int cur = root;
        int res = 0;
        for (int j = 0, i, rec; t[j]; ++j) {
            i = hashChar(t[j]);
            rec = cur = trie[cur][i];

            // enhance recursion efficiency
            while (rec != root && ~end[rec]) {
                res += end[rec];
                end[rec] = -1;
                rec = fail[rec];
            }
        }
        return res;
    }

    //    void debugAc() {
    //        for (int i = 0; i < cntNd; i++) {
    //            printf("fail[%d] = %02d\nend[%d] = %02d\nchi[%d] = [", i, fail[i], i, end[i], i);
    //            for (int j = 0; j < CHARsetsize; j++)
    //                printf("%d%c", trie[i][j], ", "[j == CHARsetsize - 1]);
    //            printf("]\n");
    //        }
    //    }
};

typedef Aho_Corasick_FSM<MAXN, 26> ACFSM;

ACFSM ac;

int kase, Kase;
int n, k;
char s[1000059];

//test multi-input  https://loj.ac/problem/10057
//test single-input  https://www.luogu.org/problem/P3808
/*
 * just judge the existence of some patterns.
 *
 */
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> Kase;
    while (Kase--) {
        cin >> n;
        ac.init();
        for (int i = 1; i <= n; i++) {
            cin >> s;
            ac.insert(s);
        }
        ac.build();
        cin >> s;
        cout << ac.query(s) << '\n';
    }
    return 0;
}
