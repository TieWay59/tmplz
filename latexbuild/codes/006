/**
 *  @Source: https://www.luogu.com.cn/problem/solution/P1742
 *  @Author: snowbody -> tieway59
 *  @Description:
 *      时间复杂度 O(N)
 *      为了减少中途过度开根，距离都是先按照平方计算的。
 *
 *  @Example:
 *      vector<Point> p(n);
 *      for (auto &pi : p) cin >> pi;
 *      Circle circle;
 *      MinCircleCover(p, circle);
 *
 *      6
 *      8.0 9.0
 *      4.0 7.5
 *      1.0 2.0
 *      5.1 8.7
 *      9.0 2.0
 *      4.5 1.0
 *      // r = 5.0000000000 (5.0000000000,5.0000000000)
 *
 *  @Verification:
 *      https://www.luogu.com.cn/problem/P1742
 */



//点或向量 (iostream选择性抄写)
struct Point {
    double x, y;

    Point() {}

    Point(double x, double y) : x(x), y(y) {}

    friend ostream &operator<<(ostream &ut, Point &r) { return ut << r.x << " " << r.y; }

    friend istream &operator>>(istream &in, Point &r) { return in >> r.x >> r.y; }
};

typedef Point Vector;

inline Vector operator+(Vector a, Vector b) {
    return Vector(a.x + b.x, a.y + b.y);
}

inline Vector operator-(Vector a, Vector b) {
    return Vector(a.x - b.x, a.y - b.y);
}

//向量数乘
inline Vector operator*(Vector a, double p) {
    return Vector(a.x * p, a.y * p);
}

//向量数除
inline Vector operator/(Vector a, double p) {
    return Vector(a.x / p, a.y / p);
}

//两点间距离
inline double Distance(Point a, Point b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

inline double Distance2(Point a, Point b) {
    return ((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

struct Circle {
    Point c;
    double r;

    Point point(double a)//基于圆心角求圆上一点坐标
    {
        return Point(c.x + cos(a) * r, c.y + sin(a) * r);
    }
};

template<typename tp>
inline tp pow2(const tp &x) {
    return x * x;
}

inline Point circumcenter(Point p1, Point p2, Point p3) {
    double a = p1.x - p2.x;
    double b = p1.y - p2.y;
    double c = p1.x - p3.x;
    double d = p1.y - p3.y;
    double e = (pow2(p1.x) - pow2(p2.x) +
                pow2(p1.y) - pow2(p2.y)) / 2;
    double f = (pow2(p1.x) - pow2(p3.x) +
                pow2(p1.y) - pow2(p3.y)) / 2;
    return Point((d * e - b * f) /
                 (a * d - b * c),
                 (a * f - c * e) /
                 (a * d - b * c));
}


void MinCircleCover(vector <Point> &p, Circle &res) {
    int n = p.size();
    random_shuffle(p.begin(), p.end());
    // avoid *sqrt* too much killing your precision.
    for (int i = 0; i < n; i++) {
        if (Distance2(p[i], res.c) <= res.r) continue;
        res.c = p[i];
        res.r = 0;
        for (int j = 0; j < i; j++) {
            if (Distance2(p[j], res.c) <= res.r)continue;
            res.c = (p[i] + p[j]) / 2;
            res.r = Distance2(p[j], res.c);
            for (int k = 0; k < j; k++) {
                if (Distance2(p[k], res.c) <= res.r)continue;
                res.c = circumcenter(p[i], p[j], p[k]);
                res.r = Distance2(p[k], res.c);
            }
        }
    }
    res.r = sqrt(res.r);
}

void solve(int kaseId = -1) {
    int n;
    cin >> n;
    vector <Point> p(n);
    for (auto &pi : p) cin >> pi;
    Circle circle;
    MinCircleCover(p, circle);
    cout << fixed << setprecision(10) << circle.r << endl;
    cout << circle.c.x << " " << circle.c.y << endl;
}
