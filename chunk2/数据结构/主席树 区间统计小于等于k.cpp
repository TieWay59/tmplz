/**
 *  @Source: https://blog.csdn.net/Tighway/article/details/81534166
 *  @Author: Tieway59
 *  @Complexity: $O(nlogn)$ 大常数
 *  @Description:
 *      统计区间小于等于k的数
 *
 *  @Example:
 *      see below
 *
 *  @Verification:
 *      2012 ICPC 杭州站
 *      http://acm.hdu.edu.cn/showproblem.php?pid=4417
 */
#include<stdio.h>
#include<algorithm>

using namespace std;
#define MAXN 100010

int root[MAXN], tcnt;
int ls[MAXN * 17];
int rs[MAXN * 17];
int sum[MAXN * 17];

void update(int l, int r, int pre, int &cur, int pos) {
    cur = ++tcnt;
    if (l == r) {
        sum[cur] = sum[pre] + 1;
        return;
    }
    ls[cur] = ls[pre];
    rs[cur] = rs[pre];
    int mid = (l + r) >> 1;
    if (pos <= mid)update(l, mid, ls[pre], ls[cur], pos);
    else update(mid + 1, r, rs[pre], rs[cur], pos);
    sum[cur] = sum[ls[cur]] + sum[rs[cur]];
}

int query(int l, int r, int old, int nuw, int h) {
    if (h < 0) return 0;
    if (0 <= l && r <= h) return sum[nuw] - sum[old];
    int mid = (l + r) >> 1, ret = 0;
    if (0 <= mid) ret += query(l, mid, ls[old], ls[nuw], h);
    if (h > mid) ret += query(mid + 1, r, rs[old], rs[nuw], h);
    return ret;//返还统计总数
}

int dsc[MAXN], dcnt;//discrete
int a[MAXN];

int main() {
    int n, m, t;
    scanf("%d", &t);
    for (int kase = 1; kase <= t; kase++) {
        printf("Case %d:\n", kase);
        scanf("%d%d", &n, &m);
        dcnt = 0;

        for (int i = 1; i <= n; i++) {
            scanf("%d", a + i);
            dsc[dcnt++] = a[i];//离散化步骤1记录
        }

        sort(dsc, dsc + dcnt);//离散化步骤2排序
        dcnt = unique(dsc, dsc + dcnt) - dsc;//离散化步骤3去重
        tcnt = 0;

        for (int x, i = 1; i <= n; i++) {
            x = lower_bound(dsc, dsc + dcnt, a[i]) - dsc;
            update(0, dcnt - 1, root[i - 1], root[i], x);
        }

        int old, nuw, h;
        while (m--) {
            scanf("%d%d%d", &old, &nuw, &h);
            old++, nuw++;
            h = upper_bound(dsc, dsc + dcnt, h) - dsc - 1;
            printf("%d\n", query(0, dcnt - 1, root[old - 1], root[nuw], h));
        }
    }
    return 0;
}
/*
1
10 10
0 5 2 7 5 4 3 8 7 7
2 8 6
3 5 0
1 3 1
1 9 4
0 1 0
3 5 5
5 5 1
4 6 3
1 5 7
5 7 3
*/
/*
Case 1:
4
0
0
3
1
2
0
1
5
1
*/