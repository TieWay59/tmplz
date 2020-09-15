
// fastFacterial 快速阶乘(分块+fft)
// O( sqrt(n)log(n) )
// https://www.luogu.org/record/25477473
#include<cstdio>
#include<algorithm>
#include<cmath>

using namespace std;
typedef unsigned long long ll;
const ll N = 262144 + 10;
const int P = 65536;
const int SF = 16;
const int msk = 65535;
ll mod;
ll PP;
typedef long double ld;
const ld pi = acos(-1.0);

inline ll fpow(ll a, ll p) {
    ll r = 1;
    for (; p; p >>= 1, a = a * a % mod)
        if (p & 1)r = r * a % mod;
    return r;
}

struct cmp {
    ld r;
    ld v;

    friend cmp operator+(cmp a, cmp b) {
        return (cmp) {a.r + b.r, a.v + b.v};
    }

    friend cmp operator-(cmp a, cmp b) {
        return (cmp) {a.r - b.r, a.v - b.v};
    }

    friend cmp operator*(cmp a, cmp b) {
        return (cmp) {a.r * b.r - a.v * b.v,
                      a.r * b.v + a.v * b.r};
    }

    void operator/=(const int &len) {
        r /= len;
        v /= len;
    }
} rt[2][22][N], tr[N],
        tr1[N], tr2[N], tr3[N],
        tr4[N], tr5[N], tr6[N];

int rv[22][N];
ll m13[N], m14[N], m23[N], m24[N];

inline void pre() {
    for (int d = 1; d <= 18; d++)
        for (int i = 1; i < (1 << d); i++)
            rv[d][i] = (rv[d][i >> 1] >> 1)
                       | ((i & 1) << (d - 1));

    for (int d = 1, t = 1; d <= 18; d++, t <<= 1)
        for (int i = 0; i < (1 << d); i++)
            rt[0][d][i] = (cmp) {cos(pi * i / t),
                                 sin(pi * i / t)};

    for (int d = 1, t = 1; d <= 18; d++, t <<= 1)
        for (int i = 0; i < (1 << d); i++)
            rt[1][d][i] = (cmp) {cos(pi * i / t),
                                 -sin(pi * i / t)};
}

inline void fft(cmp *a, int len, int d, int o) {
    for (int i = 1; i < len; i++)
        if (i < rv[d][i])
            swap(a[i], a[rv[d][i]]);
    cmp *w;
    int i;
    for (int k = 1, j = 1; k < len; k <<= 1, j++)
        for (int s = 0; s < len; s += (k << 1))
            for (i = s, w = rt[o][j]; i < s + k; i++, ++w) {
                cmp a1 = a[i + k] * (*w);
                a[i + k] = a[i] - a1;
                a[i] = a[i] + a1;
            }
    if (o)for (int i = 0; i < len; i++)a[i] /= len;
}

inline void dbdft(ll *a, int len, int d, cmp *op1, cmp *op2) {
    for (int i = 0; i < len; i++)
        tr[i] = (cmp) {(ld) (a[i] >> SF),
                       (ld) (a[i] & msk)};

    fft(tr, len, d, 0);
    tr[len] = tr[0];

    for (cmp *p1 = tr, *p2 = tr + len, *p3 = op1;
         p1 != tr + len; ++p1, --p2, ++p3)
        (*p3) = (cmp) {p1->r + p2->r,
                       p1->v - p2->v}
                * (cmp) {0.5, 0};

    for (cmp *p1 = tr, *p2 = tr + len, *p3 = op2;
         p1 != tr + len; ++p1, --p2, ++p3)
        (*p3) = (cmp) {p1->r - p2->r,
                       p1->v + p2->v}
                * (cmp) {0, -0.5};
}

inline void dbidft(cmp *tr, int len, int d, ll *a, ll *b) {
    fft(tr, len, d, 1);
    for (int i = 0; i < len; i++)
        a[i] = (ll) (tr[i].r + 0.5) % mod;

    for (int i = 0; i < len; i++)
        b[i] = (ll) (tr[i].v + 0.5) % mod;
}

inline void poly_mul(ll *a, ll *b, ll *c, int len, int d)//以上都是任意模数fft的板子
{
    dbdft(a, len, d, tr1, tr2);
    dbdft(b, len, d, tr3, tr4);
    for (int i = 0; i < len; i++)
        tr5[i] = tr1[i] * tr3[i]
                 + (cmp) {0, 1}
                   * tr2[i] * tr4[i];
    for (int i = 0; i < len; i++)
        tr6[i] = tr2[i] * tr3[i]
                 + (cmp) {0, 1}
                   * tr1[i] * tr4[i];

    dbidft(tr5, len, d, m13, m24);
    dbidft(tr6, len, d, m23, m14);

    for (int i = 0; i < len; i++)
        c[i] = m13[i] * PP % mod;
    for (int i = 0; i < len; i++)
        (c[i] += (m23[i] + m14[i]) * P + m24[i]) %= mod;
}

namespace iter {
    ll f[N];
    ll g[N];
    ll h[N];
    ll ifac[N];

    inline void ih() {
        ifac[0] = ifac[1] = 1;
        for (ll i = 2; i < min(N, mod); i++)
            ifac[i] = (mod - mod / i) * ifac[mod % i] % mod;
        for (ll i = 1; i < min(N, mod); i++)
            (ifac[i] *= ifac[i - 1]) %= mod;
    }

    inline void calch(ll del, int cur, ll *ip, ll *op) {
        int d = 0;
        int len = 1;
        while (len <= cur + cur + cur)len <<= 1, d++;
        for (int i = 0; i <= cur; i++)
            f[i] = ip[i] * ifac[i] % mod * ifac[cur - i] % mod;
        for (int i = cur - 1; i >= 0; i -= 2)
            f[i] = (mod - f[i]) % mod;
        for (int i = 0; i <= cur + cur; i++)
            g[i] = fpow((del + mod - cur + i) % mod, mod - 2);
        for (int i = cur + 1; i < len; i++)
            f[i] = 0;
        for (int i = cur + cur + 1; i < len; i++)
            g[i] = 0;

        poly_mul(f, g, h, len, d);//卷积求出h'
        ll xs = 1;
        ll p1 = del - cur;
        ll p2 = del;
        for (ll i = p1; i <= p2; i++)(xs *= i) %= mod;
        for (ll i = 0; i <= cur; i++, p1++, p2++)//双指针求出系数
        {
            op[i] = h[i + cur] * xs % mod;
            (xs *= fpow(p1, mod - 2)) %= mod,
                    (xs *= (p2 + 1)) %= mod;
        }
    }
}
ll val[N];
ll fv1[N];
ll fv2[N];

inline void solve(int n)//倍增
{
    int hb = 0;
    for (int p = n; p; p >>= 1)hb++;
    val[0] = 1;
    for (int z = hb, cur = 0; z >= 0; z--) {
        if (cur != 0)//把d乘2
        {
            iter::calch(cur + 1, cur, val, fv1);
            for (int i = 0; i <= cur; i++)
                val[cur + i + 1] = fv1[i];

            val[cur << 1 | 1] = 0;
            iter::calch(cur * fpow(n, mod - 2) % mod,
                        cur << 1, val, fv2);
            cur <<= 1;
            for (int i = 0; i <= cur; i++)
                (val[i] *= fv2[i]) %= mod;
        }
        if ((n >> z) & 1)//把d加1
        {
            for (int i = 0; i <= cur; i++)
                (val[i] *= (ll) (n * i) + cur + 1) %= mod;
            cur |= 1;
            val[cur] = 1;
            for (int i = 1; i <= cur; i++)
                (val[cur] *= (ll) cur * n + i) %= mod;
        }
    }
}

int kase;

int main() {
    pre();
    int n;
    scanf("%d", &kase);
    while (kase--) {
        scanf("%d%lld", &n, &mod);
        iter::ih();//用了全局变量mod
        int bl = sqrt(n);
        PP = (ll) P * P % mod;
        solve(bl);
        ll res = 1;
        for (ll i = 0, id = 0;; i += bl, id++)//分块
        {
            if (i + bl > n) {
                for (int j = i + 1; j <= n; j++)
                    (res *= j) %= mod;
                break;
            }
            (res *= val[id]) %= mod;
        }
        printf("%lld\n", res);
    }
    return 0;//拜拜程序~
}
/*

3
16777216 998244353
2333333 19260817
1919810 2147481811

 "n and mod"
 */