#include<bits/stdc++.h>
using namespace std;

/**
 *  @Source: https://www.luogu.com.cn/blog/Marser/solution-p3812
 *  @Author: Marser
 *  @Complexity: $O(NlogX)$
 *  @Description:
 *      对线性基做插入与查询。
 *
 *      有些性质：
 *      线性基的值域与原数组的值域相同
 *      LB.a[i] 是出现 1 的最高位在第 i 位的数
 *      构造方法: 每一个数，我们找出他的最高位的1在第i位，
 *          如果此时ai为零，就将这个数加入线性基，否则异或ai继续找。
 *
 *  @Verification:
 *      对n个整数（可能重复）取某个子集的异或和最大值。
 *      https://www.luogu.com.cn/problem/P3812
 */
typedef long long ll;
const int LBSZ = 60;

struct LB {
    // LLONG_MAX := 9223372036854775807
    ll a[61];
    ll tmp[61];
    bool flag;

    void ins(ll x) {
        for (int i = LBSZ; ~i; i--) {
            if (x & (1ll << i)) {
                if (!a[i]) {
                    a[i] = x;
                    return;
                }
                x ^= a[i];
            }
        }
        flag = true;
    }

    // 查询是否属于线性基的值域
    bool check(ll x) {
        for (int i = LBSZ; ~i; i--) {
            if (x & (1ll << i)) {
                if (!a[i]) return false;
                else x ^= a[i];
            }
        }
        return true;
    }

    ll qmax(ll res = 0) {
        for (int i = LBSZ; ~i; i--)
            res = max(res, res ^ a[i]);
        return res;
    }

    ll qmin() {
        if (flag) return 0;
        for (int i = 0; i <= LBSZ; i++)
            if (a[i]) return a[i];
    }

    /**
     *  @Complexity: $O(log^2{X})$
     *  @Description:
     *      求线性基的值域中从小到大第k的数字
     *
     *  @Example:
     *      a[] := {1, 2, 4, 8, 16};
     *      lb.query(0) == 0
     *      lb.query(1) == 1
     *      lb.query(2) == 2
     *      lb.query(3) == 3
     *
     *  @Verification:
     *
     */
    ll query(ll k) {
        ll res = 0;
        int cnt = 0;
        k -= flag;
        if (!k)return 0;
        for (int i = 0; i <= LBSZ; i++) {
            for (int j = i - 1; ~j; j--) {
                if (a[i] & (1ll << j))
                    a[i] ^= a[j];
            }
            if (a[i])tmp[cnt++] = a[i];
        }
        if (k >= (1ll << cnt))return -1;
        for (int i = 0; i < cnt; i++) {
            if (k & (1ll << i))
                res ^= tmp[i];
        }
        return res;
    }
} lb;