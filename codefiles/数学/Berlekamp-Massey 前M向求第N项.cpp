/**
 *  @Source: https://blog.csdn.net/cloudy_happy/article/details/82748973
 *  @Author: Tieway59
 *  @Complexity: $O(k^2logN)$ k代表最短线性递推式的长度
 *  @Description:
 *      $O(K^2)$ 的复杂度用BM求 最短线性递推式
 *      $O(k^2logN)$ 的复杂度做线性递推求第N项
 *      注意从0开始下标。
 *      常见用于解决一些矩阵快速幂推不出来公式的情况
 *
 *  @Example:
 *      see below
 *
 *  @Verification:
 *      2018 ICPC 焦作站网络赛
 *      https://vjudge.net/solution/27743995
 *
 *      洛谷模板题
 *      https://www.luogu.com.cn/problem/P5487
 *
 */

#include <stdio.h>
#include <vector>

using namespace std;
typedef long long ll;
typedef vector<ll> VLL;
#define REP(i, a, b) for (ll i = (a);i<(b);i++)
#define pb push_back
#define SZ(x) (ll((x).size()))
const ll mod = -1;


ll fmod(ll a, ll b) {
    ll res = 1;
    a %= mod;
    for (; b; b >>= 1) {
        if (b & 1)res = res * a % mod;
        a = a * a % mod;
    }
    return res;
}

namespace linear_seq {
    const long long N = 10010;
    ll res[N], base[N];
    ll _c[N], _md[N];

    vector<long long> Md;

    void mul(ll *a, ll *b, long long k) {
        REP(i, 0, k + k) _c[i] = 0;
        REP(i, 0, k) {
            if (a[i]) {
                REP(j, 0, k) {
                    _c[i + j] = (_c[i + j] + a[i] * b[j]) % mod;
                }
            }
        }
        for (long long i = k + k - 1; i >= k; i--) {
            if (_c[i]) {
                REP(j, 0, SZ(Md)) {
                    _c[i - k + Md[j]] = (_c[i - k + Md[j]] - _c[i] * _md[Md[j]]) % mod;
                }
            }
        }
        REP(i, 0, k) a[i] = _c[i];
    }

    // a 系数 b 初值 b[n+1]=a[0]*b[n]+...
    long long solve(ll n, const VLL &a, const VLL &b) {
        ll ans = 0, pnt = 0;
        long long k = SZ(a);
//        assert(SZ(a) == SZ(b));
        REP(i, 0, k) _md[k - 1 - i] = -a[i];
        _md[k] = 1;
        Md.clear();
        REP(i, 0, k) if (_md[i] != 0) Md.push_back(i);
        REP(i, 0, k) res[i] = base[i] = 0;
        res[0] = 1;
        while ((1ll << pnt) <= n) pnt++;
        for (long long p = pnt; p >= 0; p--) {
            mul(res, res, k);
            if ((n >> p) & 1) {
                for (long long i = k - 1; i >= 0; i--) res[i + 1] = res[i];
                res[0] = 0;
                REP(j, 0, SZ(Md)) {
                    res[Md[j]] = (res[Md[j]] - res[k] * _md[Md[j]]) % mod;
                }
            }
        }
        REP(i, 0, k) ans = (ans + res[i] * b[i]) % mod;
        if (ans < 0) ans += mod;
        return ans;
    }

    VLL BM(const VLL &s) {
        VLL C(1, 1), B(1, 1);
        ll L = 0, m = 1, b = 1;
        REP(n, 0, SZ(s)) {
            ll d = 0;
            REP(i, 0, L + 1) d = (d + (ll) C[i] * s[n - i]) % mod;
            if (d == 0) ++m;
            else if (2 * L <= n) {
                VLL T = C;
                ll c = mod - d * fmod(b, mod - 2) % mod;
                while (SZ(C) < SZ(B) + m) C.pb(0);
                REP(i, 0, SZ(B)) C[i + m] = (C[i + m] + c * B[i]) % mod;
                L = n + 1 - L;
                B = T;
                b = d;
                m = 1;
            } else {
                ll c = mod - d * fmod(b, mod - 2) % mod;
                while (SZ(C) < SZ(B) + m) C.pb(0);
                REP(i, 0, SZ(B)) C[i + m] = (C[i + m] + c * B[i]) % mod;
                ++m;
            }
        }
        return C;
    }

    VLL seq; // 线性递推式 系数数组

    void build(const VLL &a) {
        seq = BM(a);
        seq.erase(seq.begin());
        REP(i, 0, SZ(seq)) seq[i] = (mod - seq[i]) % mod;
    }

    ll cal(const VLL &a, ll n) {
        build(a);
        return solve(n, seq, VLL(a.begin(), a.begin() + SZ(seq)));
    }
}

const VLL v = {3, 9, 20, 46, 106, 244, 560, 1286, 2956, 6794, 15610};
ll n;
int kase;

int main() {
    scanf("%d", &kase);
    while (kase--) {
        scanf("%lld", &n);
        printf("%lld\n", linear_seq::cal(v, n - 1));
    }
    return 0;
}
