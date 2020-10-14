
inline void read(int &x) {
    char ch;
    bool flag = false;
    for (ch = getchar(); !isdigit(ch); ch = getchar())if (ch == '-') flag = true;
    for (x = 0; isdigit(ch); x = (x << 1) + (x << 3) + ch & 15, ch = getchar());
    x = flag ? -x : x;
}

inline void write(int x) {
    static const int maxlen = 100;
    static char s[maxlen];
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    if (!x) {
        putchar('0');
        return;
    }
    int len = 0;
    for (; x; x /= 10) s[len++] = x % 10 + '0';
    for (int i = len - 1; i >= 0; --i) putchar(s[i]);
}
