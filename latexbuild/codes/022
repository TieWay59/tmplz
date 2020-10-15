//没实现负数
const int BUF_SIZE = (int) 1e4 + 10;

struct fastIO {
    char buf[BUF_SIZE];
    int cur;
    FILE *in, *out;

    fastIO() {
        cur = BUF_SIZE;
        in = stdin;
        out = stdout;
    }

    inline char nC() {
        if (cur == BUF_SIZE) {
            fread(buf, BUF_SIZE, 1, in);
            cur = 0;
        }
        return buf[cur++];
    }

    inline bool id(char a) { return a >= '0' && a <= '9'; }

    inline int nI() {
        char c;
        while (!id(c = nC()));
        int x = c - '0';
        while (id(c = nC())) x = ((x + (x << 2)) << 1) + c - '0';
        return x;
    }

    inline ll nll() {
        char c;
        while (!id(c = nC()));
        ll x = c - '0';
        while (id(c = nC())) x = ((x + (x << 2)) << 1) + c - '0';
        return x;
    }

    inline void pC(char ch) {
        buf[cur++] = ch;
        if (cur == BUF_SIZE) {
            fwrite(buf, BUF_SIZE, 1, out);
            cur = 0;
        }
    }

    inline void pI(int x) {
        if (x > 9) pI(x / 10);
        pC(x % 10 + '0');
    }

    inline void close() { if (cur) fwrite(buf, cur, 1, out), cur = 0; }
} IO;