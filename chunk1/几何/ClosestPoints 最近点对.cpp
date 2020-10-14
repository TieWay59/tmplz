/**
 *  @Source: ClosestPoints
 *  @Author: syksykCCC -> tieway59
 *  @Description:
 *      时间复杂度 O(NlogN) 有一些难以预料的常数
 *
 *  @Example:
 *      3
 *      1 1
 *      1 2
 *      2 2
 *
 *      // ans = 1.0000
 *
 *  @Verification:
 *      https://www.luogu.com.cn/problem/solution/P1429
 */

const double EPS = 1e-6;//eps用于控制精度
const double Pi = acos(-1.0);//pi

//精度三态函数(>0,<0,=0)
inline int dcmp(double x) {
    if (fabs(x) < EPS)return 0;
    else if (x > 0)return 1;
    return -1;
}

//点或向量 (iostream选择性抄写)
struct Point {
    double x, y;

    Point() {}

    Point(double x, double y) : x(x), y(y) {}

    bool operator<(const Point &r) const {
        if (dcmp(x - r.x) == 0)
            return dcmp(y - r.y) < 0;
        return dcmp(x - r.x) < 0;
    }

    friend ostream &operator<<(ostream &ut, Point &r) { return ut << r.x << " " << r.y; }

    friend istream &operator>>(istream &in, Point &r) { return in >> r.x >> r.y; }
};

typedef Point Vector;

//两点间距离
inline double Distance(Point a, Point b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

//Point temp[MAXN];
double MAXD = INF;

double merge(vector <Point> &p, int l, int r) {
    double d = MAXD;
    if (l == r)
        return d;
    if (l + 1 == r)
        return Distance(p[l], p[r]);

    int mid = (l + r) >> 1;
    double d1 = merge(p, l, mid);
    double d2 = merge(p, mid + 1, r);
    d = min(d, min(d1, d2));

    vector<int> t;
//    t.reserve(r - l + 1);

    for (int i = l; i <= r; i++)
        if (fabs(p[mid].x - p[i].x) < d)
            t.emplace_back(i);

    sort(t.begin(), t.end(),
         [&p](const int &i, const int &j) {
             return dcmp(p[i].y - p[j].y) < 0;
         });

    for (int i = 0; i < t.size(); i++) {
        for (int j = i + 1; j < t.size() && p[t[j]].y - p[t[i]].y < d; j++) {
            d = min(d, Distance(p[t[i]], p[t[j]]));
        }
    }

    return d;
}

double ClosestPoints(vector <Point> &p) {
    assert(p.size() >= 2);
    sort(p.begin(), p.end());
    for (int i = 3; i < p.size(); ++i) {
        MAXD = min(MAXD, Distance(p[i], p[i - 1]));
        MAXD = min(MAXD, Distance(p[i], p[i - 2]));
        MAXD = min(MAXD, Distance(p[i], p[i - 3]));
    }
    return merge(p, 0, p.size() - 1);
}
