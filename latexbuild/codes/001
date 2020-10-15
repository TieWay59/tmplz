#include <bits/stdc++.h>

#define  _debug(x) cerr<<#x<<" = "<<x<<endl

using namespace std;

// Aho–Corasick algorithm, finite-state machine
template<const int NODEsetsize, const int CHARsetsize, const int STRsetsize>
struct Aho_Corasick_FSM {

    int root;
    int cntNd;
    int trie[NODEsetsize][CHARsetsize];
    int fail[NODEsetsize];
    int end[NODEsetsize];   //number of strings ends at node i
    int tag[NODEsetsize];   //times of visit j-th end.
    int ind[NODEsetsize];   //save for topo order

    int strNum;
    int strEnd[STRsetsize];   //the i-th pattern's end node is strEnd[i];

    inline int newNd() {
        for (int i = 0; i < CHARsetsize; ++i)
            trie[cntNd][i] = -1;
        end[cntNd] = 0;
        tag[cntNd] = 0;
        return cntNd++;
    }

    // hash char to a proper int ID;
    inline int hashChar(const char &c) { return c - 'a'; }

    // what will be changed when reaching an end node;
    inline void endOperation(const int &id) {
        end[id]++;
        strEnd[strNum++] = id;
    }

    inline void init() {
        cntNd = 0;
        strNum = 0;
        root = newNd();
    }

    // insert pattern, ensure p[len-1]==0
    inline void insert(const char p[]) {
        int cur = root;
        for (int j = 0, i; p[j]; ++j) {
            i = hashChar(p[j]);
            cur = (~trie[cur][i]) ? trie[cur][i] : trie[cur][i] = newNd();
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
                ind[root]++;    //+ topo
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
                    ind[trie[fail[cur]][i]]++;    //+ topo
                    que.push(trie[cur][i]);
                } else {
                    trie[cur][i] = trie[fail[cur]][i];
                }
            }
        }
    }

    // dictionary-matching target, differs by problem
    inline void query(const char t[]) {
        int cur = root;
        for (int j = 0, i, rec; t[j]; ++j) {
            i = hashChar(t[j]);
            cur = trie[cur][i];
            tag[cur]++;   //+ topo
        }

        queue<int> topo;
        for (int i = 0; i < cntNd; ++i)
            if (!ind[i])topo.emplace(i);

        while (!topo.empty()) {
            int u = topo.front();
            topo.pop();
            tag[fail[u]] += tag[u];
            if (!--ind[fail[u]])
                topo.emplace(fail[u]);
        }

        for (int i = 0; i < strNum; ++i) {
            cout << tag[strEnd[i]] << '\n';
        }
    }

//    void printAllNode() {
//        for (int i = 0; i < cntNd; i++) {
//            printf("fail[%d] = %02d\nend[%d] = %02d\nchi[%d] = [", i, fail[i], i, end[i], i);
//            for (int j = 0; j < CHARsetsize; j++)
//                printf("%d%c", trie[i][j], ", "[j == CHARsetsize - 1]);
//            printf("]\n");
//        }
//    }
};

typedef long long ll;
const int MOD = 1e9 + 7;
const int INF = 1e9 + 59;
const int MAXP = 2e5 + 59;  //Pattern
const int MAXT = 2e6 + 59;  //Target

typedef Aho_Corasick_FSM<MAXP, 26, MAXP> ACFSM;
ACFSM ac;

int kase, Kase;
int n, k;
char p[MAXP];
char t[MAXT];


/*
 * https://www.luogu.org/problem/P5357
 * print the times of appearance of all patterns in target.
 *
 */

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    ac.init();
    for (int i = 1, j; i <= n; i++) {
        cin >> p;
        ac.insert(p);
    }
    ac.build();
    cin >> t;
    ac.query(t);

    return 0;
}
/*


 a
 aa
 aaa
 aaaa
 aaaaa

 */