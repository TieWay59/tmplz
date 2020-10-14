/**
 *  @Source: team
 *  @Author: Artiprocher(Zhongjie Duan) -> tieway59
 *  @Description:
 *      多边形相关的计算。
 *  @Example:
 *
 *  @Verification:
 *
 */

Point P[1005]; // P[]为多边形的所有顶点，下标为0~n-1
int n;         // n为多边形边数
// 求多边形面积（叉积和计算法）
double PolygonArea() {
    double sum = 0;
    Point O = Point(0, 0);
    for (int i = 0; i < n; i++)
        sum += Cross(P[i] - O, P[(i + 1) % n] - O);
    if (sum < 0)sum = -sum;
    return sum / 2;
}

// STL：求多边形面积（叉积和计算法）
double PolygonArea(const vector <Point> &P) {
    int n = P.size();
    // assert(n > 2);
    double sum = 0;
    Point O = Point(0, 0);
    for (int i = 0; i < n; i++)
        sum += Cross(P[i] - O, P[(i + 1) % n] - O);
    if (sum < 0) sum = -sum;
    return sum / 2;
}

/*模板说明：P[]为多边形的所有顶点，下标为0~n-1，n为多边形边数*/
//判断点是否在凸多边形内（角度和判别法）
Point P[1005];
int n;

bool InsidePolygon(Point A) {
    double alpha = 0;
    for (int i = 0; i < n; i++)
        alpha += fabs(Angle(P[i] - A, P[(i + 1) % n] - A));
    return dcmp(alpha - 2 * pi) == 0;
}