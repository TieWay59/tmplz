const int MAXN = 1e6 + 59;
const int MOD = 1e9 + 7;
ll fac[MAXN];
ll inv[MAXN];

inline void initC(const int &sz) {
    fac[0] = 1;
    for (int i = 1; i <= sz; i++)
        fac[i] = fac[i - 1] * i % MOD;
    inv[sz] = fpow<ll>(fac[sz], MOD - 2, MOD);
    // printf inv[BCSize] to get & save it;
    for (int i = sz - 1; ~i; i--)
        inv[i] = inv[i + 1] * (i + 1) % MOD;
}

inline ll C(const int &n, const int &m) {
    return fac[n] * inv[m] % MOD * inv[n - m] % MOD;
}

// Lucas
inline ll C(int n, int m, const int &P) {
    ll res = 1;
    while (n | m)res = res * C(n % P, m % P) % P, n /= P, m /= P;
    return res;
}

int main() {
    initC(100000);

    cout << C(4, 3, 1000000007) << endl;
    cout << C(4, 1, 1000000007) << endl;
    cout << C(5, 2, 1000000007) << endl;
    return 0;
}