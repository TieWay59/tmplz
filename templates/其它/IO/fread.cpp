namespace io {
    const int L = 1 << 20 | 1;
    char ibuf[L], *iS, *iT, c, obuf[L], *oS = obuf, *oT = obuf + L - 1, qu[55]; int f, qr;
#ifdef whzzt
    #define gc() getchar()
#else
    #define gc() (iS == iT ? (iT = (iS = ibuf) + fread (ibuf, 1, L, stdin), iS == iT ? EOF : *iS ++) : *iS ++)
#endif
    template <class I>
    inline void gi (I &x) {
        for (f = 1, c = gc(); c < '0' || c > '9'; c = gc()) if (c == '-') f = -1;
        for (x = 0; c <= '9' && c >= '0'; c = gc()) x = x * 10 + (c & 15); x *= f;
    }
    inline void flush () {
        fwrite (obuf, 1, oS - obuf, stdout);
    }
    inline void putc (char x) {
        *oS ++ = x;
        if (oS == oT) flush (), oS = obuf;
    }
    template <class I>
    void print (I x) {
        if (!x) putc ('0'); if (x < 0) putc ('-'), x = -x;
        while (x) qu[++ qr] = x % 10 + '0', x /= 10;
        while (qr) putc (qu[qr --]);
    }
    struct io_ff { ~io_ff() { flush(); } } _io_ff_;
}
using io :: gi;
using io :: putc;
using io :: print;
