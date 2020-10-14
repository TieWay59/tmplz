// 多项式乘法
// http://acm.hdu.edu.cn/showproblem.php?pid=1402
// https://www.luogu.com.cn/problem/P1919
// 来源：https://oi-wiki.org/math/poly/fft/
#include <math.h>
#include <algorithm>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <vector>

using namespace std;
const double PI = acos(-1.0);

struct Complex {
    double x, y;

    Complex(double _x = 0.0, double _y = 0.0) {
        x = _x;
        y = _y;
    }

    Complex operator-(const Complex &b) const {
        return Complex(x - b.x, y - b.y);
    }

    Complex operator+(const Complex &b) const {
        return Complex(x + b.x, y + b.y);
    }

    Complex operator*(const Complex &b) const {
        return Complex(x * b.x - y * b.y, x * b.y + y * b.x);
    }
};

/*
 * 进行 FFT 和 IFFT 前的反置变换
 * 位置 i 和 i 的二进制反转后的位置互换
 *len 必须为 2 的幂
 */
void fftChange(Complex *y, int len) {
    for (int i = 1, j = (len >> 1); i < len - 1; i++) {
        if (i < j) swap(y[i], y[j]);
        int k = len >> 1;
        while (j >= k) {
            j = j - k;
            k = k >> 1;
        }
        if (j < k) j += k;
    }
}

/*
 *  做 FFT
 *  len 必须是 2^k 形式
 *  dir == 1 时是 DFT，dir == -1 时是 IDFT
 */
void fft(Complex y[], int len, int dir) {
    fftChange(y, len);
    for (int h = 2; h <= len; h <<= 1) {
        Complex wn(cos(2.0 * PI / h), sin(dir * 2.0 * PI / h));
        // Omega ^ n
        for (int j = 0; j < len; j += h) {
            Complex w(1, 0);
            for (int k = j; k < j + h / 2; k++) {
                Complex u = y[k];
                Complex t = w * y[k + h / 2];
                y[k] = u + t;
                y[k + h / 2] = u - t;
                w = w * wn;
            }
        }
    }

    if (dir == -1) {
        for (int i = 0; i < len; i++) {
            y[i].x /= len;
        }
    }
}

inline int fftLength(int len1, int len2) {
    int len = 1;
    while (len < len1 * 2 || len < len2 * 2) {
        len <<= 1;
    }
    return len;
}

// rewrite
void fftAssign(Complex *x, int len, char *s, int slen) {
    for (int i = 0; i < slen; i++) {
        double v = s[slen - 1 - i] - '0';
        x[i] = Complex(v, 0.0);
    }
    for (int i = slen; i < len; i++) {
        x[i] = Complex(0.0, 0.0);
    }
}

// rewrite
void fftMul(Complex x1[], Complex x2[], int len) {
    for (int i = 0; i < len; i++)
        x1[i] = x1[i] * x2[i];
}

const int MAXN = 2.1e6 + 59; // 尽量去取到2的幂。
Complex x2[MAXN];
Complex x1[MAXN];
char str1[MAXN / 2];
char str2[MAXN / 2];
int sum[MAXN];

int main() {
    scanf("%s%s", str1, str2);
    int len1 = strlen(str1);
    int len2 = strlen(str2);
    int len = fftLength(len1, len2);

    fftAssign(x1, len, str1, len1);
    fftAssign(x2, len, str2, len2);
    fft(x1, len, 1);
    fft(x2, len, 1);
    fftMul(x1, x2, len);
    fft(x1, len, -1);

    for (int i = 0; i < len; i++) {
        sum[i] = int(x1[i].x + 0.5);
    }

    for (int i = 0; i < len; i++) {
        sum[i + 1] += sum[i] / 10;
        sum[i] %= 10;
    }

    len = len1 + len2 - 1;
    while (sum[len] == 0 && len > 0)
        len--;

    for (int i = len; i >= 0; i--) {
        printf("%c", sum[i] + '0');
    }

    printf("\n");

    return 0;
}
