#define _debug(x) cerr<<#x<<" = "<<x<<endl

#include <bits/stdc++.h>

using namespace
std;
typedef long long ll;


template<
typename _Tp,
const int MAXMatrixSize
>

struct Matrix {
    _Tp m[MAXMatrixSize][MAXMatrixSize];
    _Tp mod = 0;

    Matrix() {
        memset(m, 0, sizeof m);
    }

    Matrix(int _mod) : mod(_mod) {
        memset(m, 0, sizeof m);
    }

    void init1() {
        //*this = Matrix(mod);
        set(0, 0, 1);
        set(1, 1, 1);
//        for (int i = 0; i < MAXMatrixSize; i++)
//            m[i][i] = 1;
    }

    inline void set(const int

    &r, const int &c, const _Tp &v) { this->m[r][c] = v; }

    inline _Tp get(const int

    &r, const int &c) { return this->m[r][c]; }

    inline void setMod(const _Tp

    &_mod) { this->mod = _mod; }

    inline Matrix operator
    *(
    const Matrix t
    ) {
        Matrix res(mod);//= Matrix(mod);
        res.setMod(mod);
        for (int i = 0; i < MAXMatrixSize; i++)
            for (int j = 0; j < MAXMatrixSize; j++)
                for (int k = 0; k < MAXMatrixSize; k++)
                    res.m[i][j] = (res.m[i][j] + m[i][k] * t.m[k][j]) % mod;
        return res;
    }
};

typedef Matrix<ll, 2> mat;

mat A, B;
ll mo, len;
char n[1000059];

inline mat fpow(mat base, ll exp) {
    mat res(mo);
    res.init1();
    while (exp) {
        if (exp & 1)res = res * base;
        exp >>= 1;
        base = base * base;
    }
    return res;
}

inline ll calc() {

    len = strlen(n);
    //reverse(n, n + len);

    mat res(mo);
    res.init1();
    mat base = B;

    for (int i = len - 1; i >= 0; --i) {
        if (n[i] > '0')
            res = res * fpow(base, n[i] - '0');
        base = fpow(base, 10);
    }

    res = A * res;
    return res.get(0, 0);
}

//https://ac.nowcoder.com/acm/contest/885/B
/*
 * input n is a long char string.(1e6)
 * mo is global Mod.
 * other parameters are just Matrix elements.
 *
 *
 */
ll x0, x1, a, b;

int main() {

    scanf("%lld%lld%lld%lld", &x0, &x1, &a, &b);
    scanf("%s %lld", n, &mo);

    A = mat(mo);
    A.set(0, 0, x0);
    A.set(0, 1, x1);

    B = mat(mo);
    B.set(0, 0, 0);
    B.set(0, 1, b);
    B.set(1, 0, 1);
    B.set(1, 1, a);

    printf("%lld\n", calc());
    return 0;
}
/*




 * */
