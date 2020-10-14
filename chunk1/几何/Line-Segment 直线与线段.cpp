/**
 *  @Source: team
 *  @Author: Artiprocher(Zhongjie Duan) -> tieway59
 *  @Description:
 *      直线与线段的相关计算。
 *
 *  @Example:
 *
 *  @Verification:
 *
 */
//定义直线
struct line {
    point a, b;
};


//线段相交（不包括端点）
bool Intersect(Point A, Point B, Point C, Point D) {
    double t1 = Cross(C - A, D - A) * Cross(C - B, D - B);
    double t2 = Cross(A - C, B - C) * Cross(A - D, B - D);
    return dcmp(t1) < 0 && dcmp(t2) < 0;
}

//线段相交（包括端点）
bool StrictIntersect(Point A, Point B, Point C, Point D) {
    return dcmp(max(A.x, B.x) - min(C.x, D.x)) >= 0
           && dcmp(max(C.x, D.x) - min(A.x, B.x)) >= 0
           && dcmp(max(A.y, B.y) - min(C.y, D.y)) >= 0
           && dcmp(max(C.y, D.y) - min(A.y, B.y)) >= 0
           && dcmp(Cross(C - A, D - A) * Cross(C - B, D - B)) <= 0
           && dcmp(Cross(A - C, B - C) * Cross(A - D, B - D)) <= 0;
}

//点A到直线MN的距离, Error: MN=0
double DistanceToLine(Point A, Point M, Point N) {
    return fabs(Cross(A - M, A - N) / Distance(M, N));
}

//两直线的交点
Point GetLineIntersection(Point P, Vector v, Point Q, Vector w) {
    Vector u = P - Q;
    double t = Cross(w, u) / Cross(v, w);
    return P + v * t;
}