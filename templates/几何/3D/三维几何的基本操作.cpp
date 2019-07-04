#include <bits/stdc++.h>

using namespace std;
struct Point3
{
    double x,y,z;
    Point3(double x = 0,double y = 0,double z = 0):x(x),y(y),z(z) {}
};
typedef Point3 Vector3;

Vector3 operator +(Vector3 v1,Vector3 v2)
{
    return Vector3(v1.x+v2.x,v1.y+v2.y,v1.z+v2.z);
}
Vector3 operator -(Vector3 v1,Vector3 v2)
{
    return Vector3(v1.x-v2.x,v1.y-v2.y,v1.z-v2.z);
}
Vector3 operator *(Vector3 v,double c)
{
    return Vector3(v.x*c,v.y*c,v.z*c);
}
Vector3 operator /(Vector3 v,double c)
{
    return Vector3(v.x/c,v.y/c,v.z/c);
}
double  Dot(Vector3 A,Vector3 B)
{
    return  A.x*B.x+A.y*B.y+A.z*B.z;
}
double Length(Vector3 A)
{
    return  sqrt(Dot(A,A));
}
double Angle(Vector3 A,Vector3 B)
{
   return acos(Dot(A,B)/(2*Length(A)*Length(B)));
}
double DistanceToplane(const Point3 &p,const Point3 &p0,const Vector3& n)
{
    return fabs(Dot(p-p0,n))/Length(n);
}
Point3  GetPlaneProjection(const Point3&p,const Point3&p0,const Vector3&n)
{
    return p-n*Dot(p-p0,n);
}
//直线p1-p2 到平面p0-n的交点。 假定交点唯一存在
Point3 LinePlaneIntetsection(Point3 p1,Point3 p2,Point3 p0,Vector3 n)
{
    Vector3 v= p2 - p1;
//    /*if(dcmp(Dot(v,n))==0)
//    {
//        if(dcmp(Dot(p1-p0,n))==0)
//            直线在平面上
//        else
//            直线与平面平行
//    }
//    */
    double t  = Dot(n,p0-p1)/Dot(n,p2-p1);
    return p1 + v*t;
}
