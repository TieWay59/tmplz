
int getLineCircleIntersection(Point A, Point B, Point C, double r, double& t1, double& t2,vector<Point> &sol){
  // 初始方程：(A.x + t(B.x - A.x) - C.x)^2 + (A.y + t(B.y - A.y) - C.y)^2 = r^2
  // 整理得：(at + b)^2 + (ct + d)^2 = r^2
  double a = B.x - A.x;
  double b = A.x - C.x;
  double c = B.y - A.y;
  double d = A.y - C.y;
  // 展开得：(a^2 + c^2)t^2 + 2(ab + cd)t + b^2 + d^2 - r^2 = 0，即et^2 + ft + g = 0
  double e = a * a + c * c;
  double f = 2 * (a * b + c * d);
  double g = b * b + d * d - r * r;
  double delta = f * f - 4 * e * g; // 判别式
  if(dcmp(delta) < 0) return 0; // 相离
  if(dcmp(delta) == 0){ // 相切
    t1 = t2 = -f / (2 * e);
    sol.push_back(A+(B-A)*t1);
    return 1;
  }
  t1 = (-f - sqrt(delta)) / (2 * e);
  t2 = (-f + sqrt(delta)) / (2 * e);
   sol.push_back(A+(B-A)*t1);
   sol.push_back(A+(B-A)*t2);
  return 2;
}
