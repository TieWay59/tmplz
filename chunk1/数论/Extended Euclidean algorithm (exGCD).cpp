ll exGCD(ll a, ll b, ll &x, ll &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    ll gcd = exGCD(b, a % b, x, y);
    ll old_x = x;
    x = y;
    y = old_x - (a / b) * x;
    return gcd;
}
// co-prime(a,m)
ll modInv(ll a, ll m) {
    ll x, y;
    ll g = exGCD(a, m, x, y);
    if (g != 1) {
        return -1;
    } else {
        ll res = (x % m + m) % m;
        return res;
    }
}

