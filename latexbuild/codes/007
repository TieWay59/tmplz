/**
 *  @Source: team
 *  @Author: Artiprocher(Zhongjie Duan) -> tieway59
 *  @Description:
 *      点与向量相关的多种计算。
 *  @Example:
 *
 *  @Verification:
 *
 */


//#include <bits/stdc++.h>
//using namespace std;
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

inline bool operator==(const Point &a, const Point &b) {
    return dcmp(a.x - b.x) == 0 && dcmp(a.y - b.y) == 0;
}

//内积
inline double Dot(Vector a, Vector b) {
    return a.x * b.x + a.y * b.y;
}

//外积
inline double Cross(Vector a, Vector b) {
    return a.x * b.y - a.y * b.x;
}

//模
inline double Length(Vector a) {
    return sqrt(Dot(a, a));
}

//夹角,弧度制
inline double Angle(Vector a, Vector b) {
    return acos(Dot(a, b) / Length(a) / Length(b));
}

//逆时针旋转
inline Vector Rotate(Vector a, double rad) {
    return Vector(a.x * cos(rad) - a.y * sin(rad), a.x * sin(rad) + a.y * cos(rad));
}

//两点间距离
inline double Distance(Point a, Point b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

//三角形面积
inline double Area(Point a, Point b, Point c) {
    return fabs(Cross(b - a, c - a) / 2);
}