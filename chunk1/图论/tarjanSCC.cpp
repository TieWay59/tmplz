//http://poj.org/status?problem_id=&user_id=tieway59&result=&language=
#define myDebug(x) cerr<<#x<<" "<<x<<endl

#include <string.h>
#include <algorithm>
#include <iostream>


using namespace std;
const int INF = 0x3f3f3f3f;
const int MAXN = 1e3 + 7;


struct Edge {
    int u, v, nx; // ,w
} e[MAXN << 2];

int head[MAXN], cntEd;

inline void addEdge(int u, int v) {
    e[cntEd] = {u, v, head[u]};
    head[u] = cntEd++;
}

//-----tarjan
int dfn[MAXN], low[MAXN], scc[MAXN], stk[MAXN], index = 0, sccnum = 0, top = 0;

void tarjan(int root) {
    if (dfn[root]) return;
    dfn[root] = low[root] = ++index;
    stk[++top] = root;
    for (int i = head[root]; ~i; i = e[i].nx) {
        int v = e[i].v;
        if (!dfn[v]) {    //如果v结点未访问过
            tarjan(v);
            low[root] = min(low[root], low[v]);
        } else if (!scc[v]) {    //如果还在栈内
            low[root] = min(low[root], dfn[v]);
        }
    }
    if (low[root] == dfn[root]) {    //后代不能找到更浅的点
        sccnum++;
        for (;;) {
            int x = stk[top--];
            scc[x] = sccnum;
            if (x == root) break;
        }
    }
}
//---------

int ind[MAXN], oud[MAXN];

int main() {
    memset(head, -1, sizeof head);

    ios::sync_with_stdio(0);
    cin.tie(0);

    int n;

    cin >> n;
    for (int v, i = 1; i <= n; i++) {
        while (cin >> v && v) {
            addEdge(i, v);
        }
    }
    for (int i = 1; i <= n; i++)
        if (!dfn[i]) tarjan(i);

    int ans1 = 0;
    int ans2 = 0;

    for (int u, v, i = 0; i < cntEd; i++) {
        u = scc[e[i].u];
        v = scc[e[i].v];
        if (u != v) {
            ind[v]++;
            oud[u]++;
        }
    }
    for (int i = 1; i <= sccnum; i++) {
        if (ind[i] == 0) {
            ans1++;
        }
        if (oud[i] == 0) {
            ans2++;
        }
    }
    ans2 = max(ans2, ans1);

    if (sccnum == 1)ans1 = 1, ans2 = 0;
    cout << ans1 << endl << ans2 << endl;

    return 0;
}
