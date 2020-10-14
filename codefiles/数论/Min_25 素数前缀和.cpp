/**
 *  @Source: https://loj.ac/submission/795951
 *  @Author: Min_25 Japan
 *  @Complexity: $O(n^{\frac{1}{2})$ 似乎常数很低
 *  @Description:
 *      奇快无比的素数前缀和（Min_25本人写的）
 *      数据范围到1e11
 *
 *  @Example:
 *      see below
 *
 *  @Verification:
 *      https://loj.ac/problem/6202
 */
#include <cstdio>
#include <cmath>
#include <vector>
using namespace std;

using i64 = long long;
using u64 = long long unsigned;
using i128 = __int128_t;
using u128 = __uint128_t;

int isqrt(i64 n) { return sqrtl(n); }

template<typename T, typename S>
S sum1(T n) {
    return S(n) * (n + 1) >> 1;
}

template<typename T, typename S>
S sum1o(T n) {
    return sum1<T, S>(n) - 2 * sum1<T, S>(n >> 1);
}

__attribute__((target("avx"), optimize("O3", "unroll-loops")))
i128 prime_sum(const i64 N) {
    if (N <= 1)
        return 0;
    const int v = isqrt(N);
    vector<int> s0(v + 1);
    for (int i = 2; i <= v; ++i) s0[i] = (i + 1) / 2;
    vector<i64> s1(v + 1);
    for (int i = 2; i <= v; ++i) s1[i] = sum1o<int, i64>(i) + 1;
    int s = (v + 1) / 2;
    vector<int> roughs(s);
    for (int i = 0; i < s; ++i) roughs[i] = 2 * i + 1;
    vector<i128> l1(s);
    for (int i = 0; i < s; ++i) l1[i] = sum1o<i64, i128>(N / roughs[i]) + 1;
    vector<bool> skip(v + 1);
    auto divide = [](i64 N, i64 d) -> int { return double(N) / d; };

    i64 ps = 0;
    for (int p = 3; p <= v; ++p)
        if (s0[p] > s0[p - 1]) {
            int q = p * p, pc = s0[p - 1];
            ps = s1[p - 1];
            if (i64(q) * q > N)
                break;
            skip[p] = true;
            for (int i = q; i <= v; i += 2 * p) skip[i] = true;
            int ns = 0;
            for (int k = 0; k < s; ++k) {
                int i = roughs[k];
                if (skip[i])
                    continue;
                i64 d = i64(i) * p;
                l1[ns] = l1[k] - i128((d <= v ? l1[s0[d] - pc] : s1[divide(N, d)]) - ps) * p;
                roughs[ns++] = i;
            }
            s = ns;
            for (int i = v, j = v / p; j >= p; --j) {
                int c0 = s0[j] - pc;
                for (int t = i, e = j * p; t >= e; --t) s0[t] -= c0;
                i64 c1 = (s1[j] - ps) * p;
                for (int e = j * p; i >= e; --i) s1[i] -= c1;
            }
        }

    i64 ps1 = ps;
    for (int k = 1; k < s; ++k) {
        const int p1 = roughs[k];
        const i64 M = N / p1;
        i128 s = l1[k];
        i64 ps2 = ps;
        for (int l = 1; l < k; ++l) {
            const int p2 = roughs[l];
            if (i64(p2) * p2 > M)
                break;
            s -= i128(s1[divide(M, p2)] - ps2) * p2;
            ps2 += p2;
        }
        l1[0] -= (s - ps1) * p1;
        ps1 += p1;
    }
    return l1[0];
}

void put_u128(u128 n) {
    constexpr u64 ten19 = 1e19;
    constexpr u128 ten38 = u128(ten19) * ten19;
    if (n >= ten38) {
        printf("%llu", u64(n / ten38));
        n %= ten38;
        printf("%019llu%019llu\n", u64(n / ten19), u64(n % ten19));
    } else if (n >= ten19) {
        printf("%llu%019llu\n", u64(n / ten19), u64(n % ten19));
    } else {
        printf("%llu\n", u64(n));
    }
}

int main() {
    i64 L, R;
    while (EOF != scanf("%lld %lld", &L, &R)) {
        auto ans = prime_sum(R) - prime_sum(L - 1);
        put_u128(ans);
    }
}
