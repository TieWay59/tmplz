//大数分解和随机测试素数
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN = (int) 1e6 + 7;
typedef pair<ll, int> pli;
/**
 *  @Source: https://blog.csdn.net/qq_41848675/article/details/98233182
 *  @Author: 苏丁力
 *  @Complexity: $O(n^{\frac{1}{4}})$
 *  @Description:
 *      1e18范围内的数做质因子分解
 *      输出是按照因子从小到大的（中间有一步排序）
 *
 *  @Example:
 *      if (!pollard_rho::miller_rabin(n))
 *          res = pollard_rho::solve(n);
 *
 *      [n] := 30
 *      [res] := {(2, 1), (3, 1), (5, 1)}
 *
 *  @Verification:
 *      身经百战（懒得贴了）
 *
 */
namespace pollard_rho {
    const int C = 2307;
    const int S = 8;//可以适当调大
    typedef pair<ll, int> pli;
    mt19937_64 rd(time(0));
    vector<ll> ve;

    ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }

    ll mul(ll a, ll b, ll mod) {
        return (a * b - (ll) (a / (long double) mod * b + 1e-3) * mod + mod) % mod;
    }

    ll power(ll a, ll b, ll mod) {
        ll res = 1;
        a %= mod;
        while (b) {
            if (b & 1)res = mul(res, a, mod);
            a = mul(a, a, mod);
            b >>= 1;
        }
        return res;
    }

    bool check(ll a, ll n) {
        ll m = n - 1, x, y;
        int j = 0;
        while (!(m & 1))m >>= 1, j++;
        x = power(a, m, n);
        for (int i = 1; i <= j; x = y, i++) {
            y = mul(x, x, n);
            if (y == 1 && x != 1 && x != n - 1)return 1;
        }
        return y != 1;
    }

    bool miller_rabin(ll n) { //素数随机测试算法
        if (n == 1)return 0;
        if (n == 2)return 1;
        if (!(n & 1))return 0;
        for (int i = 0; i < S; i++)
            if (check(rd() % (n - 1) + 1, n))
                return 0;
        return 1;
    }

    ll pollard_rho(ll n, int c) {
        ll i = 1, k = 2, x = rd() % n, y = x, d;
        while (1) {
            i++;
            x = (mul(x, x, n) + c) % n, d = gcd(y - x, n);
            if (d > 1 && d < n)return d;
            if (y == x)return n;
            if (i == k)y = x, k <<= 1;
        }
    }

    void findfac(ll n, int c) {
        if (n == 1)return;
        if (miller_rabin(n)) {
            ve.push_back(n);
            return;
        }
        ll m = n;
        while (m == n)m = pollard_rho(n, c--);
        findfac(m, c);
        findfac(n / m, c);
    }

    vector<pli> solve(ll n) {
        vector<pli> res;
        ve.clear();
        findfac(n, C);
        sort(ve.begin(), ve.end());
        for (auto x:ve) {
            if (res.empty() || res.back().first != x)
                res.push_back({x, 1});
            else res.back().second++;
        }
        return res;
    }
}
vector<pli> res;
//接口返回一个所有质因数及其个数的vector
