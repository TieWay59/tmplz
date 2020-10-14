/**
 *  @Source: blog.csdn.net/liyuanbhu/article/details/52891868
 *  @Author: tieway59
 *  @Description:
 *      注意排除三点共线。
 *      if (dcmp(Cross(pi, pj)) == 0) continue;
 *
 *  @Example:
 *      circumcenter(Point(0, 1), Point(1, 1), Point(1, 0));
 *      // 0.5 0.5
 *
 *  @Verification:
 *      https://ac.nowcoder.com/acm/contest/5667/B
 *      (solution) ac.nowcoder.com/acm/contest/view-submission?submissionId=44337916
 *
 */

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