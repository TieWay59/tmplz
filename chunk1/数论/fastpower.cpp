//
// Created by acm-33 on 2019/9/19.
//


template<typename var= long long>
var fpow(var a, var b, var m) {
    var ret = 1;
    while (b) {
        if (b & 1)ret = ret * a % m;
        a = a * a % m;
        b >>= 1;
    }
    return ret;
}

long long fpow(long long a, long long b, long long m) {
    long long ret = 1;
    while (b) {
        if (b & 1)ret = ret * a % m;
        a = a * a % m;
        b >>= 1;
    }
    return ret;
}

