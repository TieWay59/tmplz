/**
 *  @Source: https://loj.ac/submission/566777
 *  @Author: g21gsj
 *  @Complexity: $O(n^{\frac{1}{2})$ 常数多一点
 *  @Description:
 *      求素数前缀和的替代方案
 *      稍微慢一些，但是也已经非常快了。
 *      double是因为数据范围到1e11
 *
 *  @Example:
 *      see below
 *
 *  @Verification:
 *      https://loj.ac/problem/6202
 */
#define N 1000005
#define ll long long
#define eps 1e-8
using namespace std;
ll l, r;
double n, now, f1[N], f2[N], inv[N];

double calc(ll x) { return 1.0 * x * (x + 1) / 2; }

double solve(ll n) {
    int S = sqrt(n);
    if (!n)
        return 0;
    for (int i = 1; i <= S; ++i)
        f1[i] = calc(i), f2[i] = calc(n / i), inv[i] = 1.0 / i;
    for (int p = 2; p <= S; ++p) {
        if (fabs(f1[p] - f1[p - 1]) <= eps)
            continue;
        int lim = min((ll) S, n / p / p);
        now = n / p;
        for (int i = 1; i * p <= S; ++i)
            f2[i] -= (f2[i * p] - f1[p - 1]) * p;
        for (int i = S / p + 1; i <= lim; ++i)
            f2[i] -= (f1[(int) (now * inv[i] + 1e-7)] - f1[p - 1]) * p;
        for (int i = S; i >= (ll) p * p; --i)
            f1[i] -= (f1[(int) (i * inv[p] + 1e-7)] - f1[p - 1]) * p;
    }
    return f2[1];
}

int main() {
    scanf("%lld%lld", &l, &r);
    printf("%.0lf\n", solve(r) - solve(l - 1));
    return 0;
}
