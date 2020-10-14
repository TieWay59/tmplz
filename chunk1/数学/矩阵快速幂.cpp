/**
 *  @Source: myself
 *  @Author: Tieway59
 *  @Complexity: $O(N^3logP)$
 *  @Description:
 *      n行m列，下标从1开始
 *
 *  @Example:
 *
 *  @Verification:
 *      http://codeforces.com/problemset/problem/185/A
 *      http://codeforces.com/problemset/submission/185/95319533
 *
 */

#include<bits/stdc++.h>

using namespace std;
const long long mo = 1e9 + 7;
const int MATSZ = 11;
typedef long long ll;

struct matrix {
    int n, m;
    ll a[MATSZ][MATSZ];

    void clear() {
        n = m = 0;
        memset(a, 0, sizeof a);
    }

    matrix operator*(const matrix &t) const {
        matrix ret;
        ret.clear();
        ret.n = n, ret.m = m;
        for (int i = 1; i <= n; i++)
            for (int k = 1; k <= m; k++)
                for (int j = 1; j <= m; j++)
                    //这里m其实应该写t.m，但是矩阵乘法的条件就是两者相等
                    ret.a[i][j] = (ret.a[i][j] + (a[i][k] * t.a[k][j]) % mo) % mo;
        return ret;
    }

    void eye(int x)//生成单位矩阵
    {
        clear();
        n = m = x;
        for (int i = 1; i <= x; i++)
            a[i][i] = 1;
    }
};

matrix fpow(matrix base, ll idx) {
    matrix ans;
    ans.eye(base.n);
    while (idx) {
        if (idx & 1)ans = ans * base;
        base = base * base;
        idx >>= 1;
    }
    return ans;
}

int main() {
    ll n;
    matrix mat1, mat2, ans;
    while (cin >> n) {
        mat1.n = 1, mat1.m = 2;
        mat1.a[1][1] = 1;
        mat1.a[1][2] = 0;
        mat2.n = 2, mat2.m = 2;
        mat2.a[1][1] = 3, mat2.a[1][2] = 1;
        mat2.a[2][1] = 1, mat2.a[2][2] = 3;

        ans = mat1 * fpow(mat2, n);
        cout << (ans.a[1][1] % mo) << endl;
    }
    return 0;
}
/*

*/
