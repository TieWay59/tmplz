//
// Created by acm-33 on 2019/7/23.
//

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
