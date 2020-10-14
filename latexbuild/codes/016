/* @head of double-compare modules */
const double EPS = 1e-8;

inline int dcmp(const double &x) {
    if (fabs(x) < EPS)return 0;
    else return x < EPS ? -1 : 1;
}

// not necessary
inline bool lt(const double &x, const double &y) { return dcmp(x - y) < 0; }

inline bool le(const double &x, const double &y) { return dcmp(x - y) <= 0; }

inline bool eq(const double &x, const double &y) { return dcmp(x - y) == 0; }

inline bool ge(const double &x, const double &y) { return dcmp(x - y) >= 0; }

inline bool gt(const double &x, const double &y) { return dcmp(x - y) > 0; }

// not recommended
inline bool dcmp(const double &x, const string &mode, const double &y) {
    if (mode == "lt") return dcmp(x - y) < 0;
    if (mode == "le") return dcmp(x - y) <= 0;
    if (mode == "eq") return dcmp(x - y) == 0;
    if (mode == "ge") return dcmp(x - y) >= 0;
    if (mode == "gt") return dcmp(x - y) > 0;
    exit(0);
}
/* @tail of double-compare modules */