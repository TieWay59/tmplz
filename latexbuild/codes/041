ll fpow(ll a, ll b, ll mod = MOD) {
    if (a % mod == 0) return 0;
    ll ret = 1;
    a %= mod;
    while (b) {
        if (b & 1)ret = ret * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return ret;
}
