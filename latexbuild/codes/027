//
// Created by acm-33 on 2019/7/24.
//

#define _debug(x) cerr<<#x<<" = "<<x<<endl

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const ll LINF = 0x3f3f3f3f3f3f3f3f;
const ll INF = 0x3f3f3f3f3f3f3f3f;
//const int MAXN = 3000 + 59;
const ll MOD = 998244353;
const int MAXN = 100015;

const int M = MAXN * 30;
int n, q, m, tot;
int a[MAXN], t[MAXN];
int T[MAXN], lson[M], rson[M], c[M];

void Init_hush() {
    for (int i = 1; i <= n; i++)
        t[i] = a[i];
    sort(t + 1, t + 1 + n);
    m = unique(t + 1, t + 1 + n) - t - 1;
}

int build(int l, int r) {
    int root = tot++;
    c[root] = 0;
    if (l != r) {
        int mid = (l + r) >> 1;
        lson[root] = build(l, mid);
        rson[root] = build(mid + 1, r);
    }
    return root;
}

int hush(int x) {
    return lower_bound(t + 1, t + 1 + m, x) - t;
}

int update(int root, int pos, int val) {
    int newroot = tot++, tmp = newroot;
    c[newroot] = c[root] + val;
    int l = 1, r = m;
    while (l < r) {
        int mid = (l + r) >> 1;
        if (pos <= mid) {
            lson[newroot] = tot++;
            rson[newroot] = rson[root];
            newroot = lson[newroot];
            root = lson[root];
            r = mid;
        } else {
            rson[newroot] = tot++;
            lson[newroot] = lson[root];
            newroot = rson[newroot];
            root = rson[root];

            l = mid + 1;
        }
        c[newroot] = c[root] + val;
    }
    return tmp;
}

int query(int left_root, int right_root, int k) {
    int l = 1, r = m;
    while (l < r) {
        int mid = (l + r) >> 1;
        if (c[lson[left_root]] - c[lson[right_root]] >= k) {
            r = mid;
            left_root = lson[left_root];
            right_root = lson[right_root];
        } else {
            l = mid + 1;
            k -= c[lson[left_root]] - c[lson[right_root]];
            left_root = rson[left_root];
            right_root = rson[right_root];
        }
    }
    return l;
}

ll Seg_k(int l, int r, int k) {
    if (k > r - l + 1)return -1;
    return 1ll * t[query(T[l], T[r + 1], k)];
}

int main() {

    while (scanf("%d%d", &n, &q) == 2) {
        tot = 0;
        for (int i = 1; i <= n; i++)
            scanf("%d", &a[i]);
        Init_hush();
        T[n + 1] = build(1, m);
        for (int i = n; i; i--) {
            int pos = hush(a[i]);
            T[i] = update(T[i + 1], pos, 1);
        }
        while (q--) {
            int l, r, k;
            scanf("%d%d%d", &l, &r, &k);
            printf("%lld\n", Seg_k(l, r, k));
        }
    }
    return 0;
}

/*
5 5
5 3 4 1 2
1 2 2
1 2 1
1 5 3
1 5 4
1 5 6


*/

/*




 */