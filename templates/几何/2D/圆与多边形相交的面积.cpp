#include <iostream>  
#include <cstdio>  
#include <string>  
#include <cmath>  
#include <iomanip>  
#include <ctime>  
#include <climits>  
#include <cstdlib>  
#include <cstring>  
#include <algorithm>  
#include <queue>  
#include <vector>  
#include <set>  
#include <map>  
using namespace std;  
typedef unsigned int UI;  
typedef long long LL;  
typedef unsigned long long ULL;  
typedef long double LD;  
const double pi = acos(-1.0);  
const double e = exp(1.0);  
const double eps = 1e-8;  
const int maxn = 400;  
double x, y, h;  
double vx, vy;  
double R;  
int n;  
struct point  
{  
    double x, y;  
    point(double _x=0.0, double _y=0.0)  
        : x(_x), y(_y) {}  
    point operator - (const point & p)  
    {  
        return point(x-p.x, y-p.y);  
    }  
    double sqrx()  
    {  
        return sqrt(x*x+y*y);  
    }  
} p[maxn];  
  
double xmult(point & p1, point & p2, point & p0);  
double distancex(point & p1, point & p2);  
point intersection(point u1, point u2, point v1, point v2);  
void intersection_line_circle(point c, double r, point l1, point l2, point & p1, point & p2);  
point ptoseg(point p, point l1, point l2);  
double distp(point & a, point & b);  
double Direct_Triangle_Circle_Area(point a, point b, point o, double r);  
  
 
double xmult(point & p1, point & p2, point & p0)  
{  
    return (p1.x-p0.x)*(p2.y-p0.y)-(p1.y-p0.y)*(p2.x-p0.x);  
}  
  
double distancex(point & p1, point & p2)  
{  
    return sqrt((p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y));  
}  
  
point intersection(point u1, point u2, point v1, point v2)  
{  
    point ret = u1;  
    double t = ((u1.x-v1.x)*(v1.y-v2.y)-(u1.y-v1.y)*(v1.x-v2.x))  
             / ((u1.x-u2.x)*(v1.y-v2.y)-(u1.y-u2.y)*(v1.x-v2.x));  
    ret.x += (u2.x-u1.x)*t;  
    ret.y += (u2.y-u1.y)*t;  
    return ret;  
}  
  
void intersection_line_circle(point c, double r, point l1, point l2, point & p1, point & p2)  
{  
    point p = c;  
    double t;  
    p.x += l1.y-l2.y;  
    p.y += l2.x-l1.x;  
    p = intersection(p, c, l1, l2);  
    t = sqrt(r*r-distancex(p, c)*distancex(p, c))/distancex(l1, l2);  
    p1.x = p.x+(l2.x-l1.x)*t;  
    p1.y = p.y+(l2.y-l1.y)*t;  
    p2.x = p.x-(l2.x-l1.x)*t;  
    p2.y = p.y-(l2.y-l1.y)*t;  
}  
  
point ptoseg(point p, point l1, point l2)  
{  
    point t = p;  
    t.x += l1.y-l2.y;  
    t.y += l2.x-l1.x;  
    if (xmult(l1, t, p)*xmult(l2, t, p)>eps)  
        return distancex(p, l1)<distancex(p, l2) ? l1 : l2;  
    return intersection(p, t, l1, l2);  
}  
  
double distp(point & a, point & b)  
{  
    return (a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y);  
}  
  
double Direct_Triangle_Circle_Area(point a, point b, point o, double r)  
{  
    double sign = 1.0;  
    a = a-o;  
    b = b-o;  
    o = point(0.0, 0.0);  
    if (fabs(xmult(a, b, o)) < eps)  
        return 0.0;  
    if (distp(a, o) > distp(b, o))  
    {  
        swap(a, b);  
        sign = -1.0;  
    }  
    if (distp(a, o) < r*r+eps)  
    {  
        if (distp(b, o) < r*r+eps)  
            return xmult(a, b, o)/2.0*sign;  
        point p1, p2;  
        intersection_line_circle(o, r, a, b, p1, p2);  
        if (distancex(p1, b) > distancex(p2, b))  
            swap(p1, p2);  
        double ret1 = fabs(xmult(a, p1, o));  
        double ret2 = acos((p1.x*b.x+p1.y*b.y)/p1.sqrx()/b.sqrx())*r*r;  
        double ret = (ret1+ret2)/2.0;  
        if (xmult(a, b, o)<eps && sign>0.0 || xmult(a, b, o)>eps && sign<0.0)  
            ret = -ret;  
        return ret;  
    }  
    point ins = ptoseg(o, a, b);  
    if (distp(o, ins)>r*r-eps)  
    {  
        double ret = acos((a.x*b.x+a.y*b.y)/a.sqrx()/b.sqrx())*r*r/2.0;  
        if (xmult(a, b, o)<eps && sign>0.0 || xmult(a, b, o)>eps && sign<0.0)  
            ret = -ret;  
        return ret;  
    }  
    point p1, p2;  
    intersection_line_circle(o, r, a, b, p1, p2);  
    double cm = r/(distancex(o, a)-r);  
    point m = point((o.x+cm*a.x)/(1+cm), (o.y+cm*a.y)/(1+cm));  
    double cn = r/(distancex(o, b)-r);  
    point n = point((o.x+cn*b.x)/(1+cn), (o.y+cn*b.y)/(1+cn));  
    double ret1 = acos((m.x*n.x+m.y*n.y)/m.sqrx()/n.sqrx())*r*r;  
    double ret2 = acos((p1.x*p2.x+p1.y*p2.y)/p1.sqrx()/p2.sqrx())*r*r-fabs(xmult(p1, p2, o));  
    double ret = (ret1-ret2)/2.0;  
    if (xmult(a, b, o)<eps && sign>0.0 || xmult(a, b, o)>eps && sign<0.0)  
        ret = -ret;  
    return ret;  
}  
double Inter(double x,double y,double R,int n,point *area){
        area[n] = area[0];
        point temp = point(x, y);  
        double sum = 0; 
        for (int i=0; i<n-1; i++)  
            sum += Direct_Triangle_Circle_Area(area[i], area[i+1], temp, R); 
			
        sum += Direct_Triangle_Circle_Area(area[n-1], area[0], temp, R);  
        return fabs(sum);
}
double Cross(point A,point B)
{
    return A.x*B.y - A.y*B.x;
}
int N,M;
double PolygonArea (point * p,int n)
{
    double area = 0;
    for(int i = 1; i < n - 1; ++i)
    {
        area += Cross(p[i]-p[0],p[i+1]-p[0]);
    }
    return fabs(area/2);
}

int dcmp(double x)
{
    if(fabs(x)<eps)
        return 0;
    else
        return x < 0?-1:1;
}
double S ;
double xi,yi,P,Q;
bool check(double R){
	//	cout<<xi<<" "<<yi<<" "<<P<<" "<<Q<<endl;
//	printf("r = %lf Intersect = %lf\n",R,Inter(xi,yi,R,N,p) );
//	printf("%lf\n",(1-P/Q)*S);
	return  dcmp(Inter(xi,yi,R,N,p) - (1-P/Q)*S) > 0; 
} 
int main()
{

	cin>>N;
	for(int i=0;i< N;i++)
        {
            scanf("%lf%lf",&p[i].x,&p[i].y);
        }
    
    S= PolygonArea(p,N); 
    //cout<<S<<endl;
    cin>>M;
	for(int i = 0;i < M; ++i){
		
		scanf("%lf %lf %lf %lf",&xi,&yi,&P,&Q);
	
		double l = 0,r = 1e6;
		for(int j = 0;j < 100; ++j){
			double mid = l+(r-l)/2;
			if(check(mid))
			     r = mid;
			else
			     l = mid;
		 // printf("%lf %lf\n",l,r);
		}
		printf("%.8lf\n",r);
	}

    return 0;
}
