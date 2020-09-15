/**
 *  @Source: team
 *  @Author: Artiprocher(Zhongjie Duan) -> tieway59
 *  @Description:
 *      圆形计算相关。
 *  @Example:
 *
 *  @Verification:
 *
 */

struct Circle {
    Point c;
    double r;

    Point point(double a)//基于圆心角求圆上一点坐标
    {
        return Point(c.x + cos(a) * r, c.y + sin(a) * r);
    }
};

double Angle(Vector v1) {
    if (v1.y >= 0)return Angle(v1, Vector(1.0, 0.0));
    else return 2 * pi - Angle(v1, Vector(1.0, 0.0));
}

int GetCC(Circle C1, Circle C2)//求两圆交点
{
    double d = Length(C1.c - C2.c);
    if (dcmp(d) == 0) {
        if (dcmp(C1.r - C2.r) == 0)return -1;//重合
        else return 0;
    }
    if (dcmp(C1.r + C2.r - d) < 0)return 0;
    if (dcmp(fabs(C1.r - C2.r) - d) > 0)return 0;
    double a = Angle(C2.c - C1.c);
    double da = acos((C1.r * C1.r + d * d - C2.r * C2.r) / (2 * C1.r * d));
    Point p1 = C1.point(a - da), p2 = C1.point(a + da);
    if (p1 == p2)return 1;
    else return 2;
}