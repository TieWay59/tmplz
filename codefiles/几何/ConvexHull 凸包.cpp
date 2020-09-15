/**
 *  @Source: Graham_s_scan
 *  @Author: Artiprocher(Zhongjie Duan) -> tieway59
 *  @Description:
 *      n       点数
 *      P[]     点数组 index0
 *      top     栈顶, 凸包顶点数
 *      H[]     凸包的顶点 index0
 *      小心重复的凸包顶点, 也会加入凸包。
 *      H[]逆时针顺序
 *      数组形式，理论上常数会小？
 *
 *  @Example:
 *      4
 *      4 8
 *      4 12
 *      5 9.3 (exclude)
 *      7 8
 *
 *  @Verification:
 *      https://www.luogu.com.cn/record/35363811
 *
 */
int n, top;
const int PSIZE = 100005;
Point P[PSIZE], H[PSIZE];

bool cmp(Point A, Point B) {
    double ans = Cross(A - P[0], B - P[0]);
    if (dcmp(ans) == 0)
        return dcmp(Distance(P[0], A) - Distance(P[0], B)) < 0;
    else
        return ans > 0;
}

//Graham凸包扫描算法
void Graham() {
    for (int i = 1; i < n; i++)//寻找起点
        if (P[i].y < P[0].y || (dcmp(P[i].y - P[0].y) == 0 && P[i].x < P[0].x))
            swap(P[i], P[0]);
    sort(P + 1, P + n, cmp);//极角排序，中心为起点
    H[0] = P[0];
    H[1] = P[1];
    top = 2;
    for (int i = 2; i < n; i++) {
        while (top >= 2 && Cross(H[top - 1] - H[top - 2], P[i] - H[top - 2]) < 0)
            top--;
        H[top++] = P[i];
    }
}


/**
 *  @Source: Graham_s_scan
 *  @Author: Artiprocher(Zhongjie Duan) -> tieway59
 *  @Description:
 *      小心重复的凸包顶点, 也会加入凸包。
 *      H[]逆时针顺序
 *      数组形式，理论上常数会小？
 *
 *  @Example:
 *      4
 *      4 8
 *      4 12
 *      5 9.3 (exclude)
 *      7 8
 *
 *  @Verification:
 *      https://www.luogu.com.cn/record/35363811
 *
 */

// HEAD begin
const double EPS = 1e-6;

struct Point//点或向量
{
    double x, y;

    Point() {}

    Point(double x, double y) : x(x), y(y) {}

    friend ostream &operator<<(ostream &ut, Point &r) { return ut << r.x << " " << r.y; }

    friend istream &operator>>(istream &in, Point &r) { return in >> r.x >> r.y; }
};

typedef Point Vector;

inline double Distance(Point a, Point b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

inline Vector operator+(Vector a, Vector b) {
    return Vector(a.x + b.x, a.y + b.y);
}

inline Vector operator-(Vector a, Vector b) {
    return Vector(a.x - b.x, a.y - b.y);
}

//外积
inline double Cross(Vector a, Vector b) {
    return a.x * b.y - a.y * b.x;
}

//精度三态函数(>0,<0,=0)
inline int dcmp(double x) {
    if (fabs(x) < EPS)return 0;
    else if (x > 0)return 1;
    return -1;
}

// HEAD end
void ConvexHull(vector <Point> &P, vector <Point> &H) {
    int n = int(P.size());
    for (int i = 1; i < n; i++)//寻找起点
        if (P[i].y < P[0].y || (dcmp(P[i].y - P[0].y) == 0 && P[i].x < P[0].x))
            swap(P[i], P[0]);

    //极角排序，中心为起点
    sort(P.begin() + 1, P.end(), [&P](Point A, Point B) {
        double ans = Cross(A - P[0], B - P[0]);
        if (dcmp(ans) == 0)
            return dcmp(Distance(P[0], A) - Distance(P[0], B)) < 0;
        else
            return ans > 0;
    });

    H.assign(n + n, {});
    H[0] = P[0];
    H[1] = P[1];
    int top = 2;
    for (int i = 2; i < n; i++) {
        while (top >= 2 && Cross(H[top - 1] - H[top - 2], P[i] - H[top - 2]) < 0)
            top--;
        H[top++] = P[i];
    }
    H.resize(top);
}

/**
 *  @Source: Andrew_s_monotone_chain
 *  @Author: Artiprocher(Zhongjie Duan) -> tieway59
 *  @Description:
 *      Andrew_s_monotone_chain
 *      从左下角开始逆时针排列，去除凸包边上的点。
 *      求出来的凸包是逆时针的。
 *      points in h[] are counter-clockwise
 *
 *  @Example:
 *      vector<Point> p(n);
 *      for (auto &pi : p) cin >> pi;
 *      vector<Point> r;
 *      ConvexHull(p, r);
 *
 *      4
 *      4 8
 *      4 12
 *      5 9.3 (exclude)
 *      7 8
 *
 *  @Verification:
 *      https://www.luogu.com.cn/problem/P2742
 */

// HEAD begin
const double EPS = 1e-6;

struct Point//点或向量
{
    double x, y;

    Point() {}

    Point(double x, double y) : x(x), y(y) {}

    friend ostream &operator<<(ostream &ut, Point &r) { return ut << r.x << " " << r.y; }

    friend istream &operator>>(istream &in, Point &r) { return in >> r.x >> r.y; }
};

typedef Point Vector;

inline double Distance(Point a, Point b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

inline Vector operator+(Vector a, Vector b) {
    return Vector(a.x + b.x, a.y + b.y);
}

inline Vector operator-(Vector a, Vector b) {
    return Vector(a.x - b.x, a.y - b.y);
}

//外积
inline double Cross(Vector a, Vector b) {
    return a.x * b.y - a.y * b.x;
}

//精度三态函数(>0,<0,=0)
inline int dcmp(double x) {
    if (fabs(x) < EPS)return 0;
    else if (x > 0)return 1;
    return -1;
}
// HEAD end

inline bool pcmp(Point a, Point b) {
    if (dcmp(a.x - b.x) == 0)
        return a.y < b.y;
    return a.x < b.x;
}

void ConvexHull(vector <Point> &p, vector <Point> &h) {
    int n = p.size(), k = 0;
    h.assign(2 * n, {});
    sort(p.begin(), p.end(), pcmp);
    for (int i = 0; i < n; i++) {
        while (k >= 2 && dcmp(Cross(
                h[k - 1] - h[k - 2],
                p[i] - h[k - 2])) < 0) {
            k--;
        }
        h[k++] = p[i];
    }

    int t = k + 1;
    for (int i = n - 1; i > 0; i--) {
        while (k >= t && dcmp(Cross(
                h[k - 1] - h[k - 2],
                p[i - 1] - h[k - 2])) < 0) {
            k--;
        }
        h[k++] = p[i - 1];
    }

    h.resize(k - 1);
}