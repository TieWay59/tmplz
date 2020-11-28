#include <bits/stdc++.h>
using std::cin;
using std::cout;
using std::endl;
using std::set;
using std::map;
using std::min;
using std::max;
using std::vector;
using std::deque;
using std::min;
using std::max;
using std::swap;
using std::string;
typedef long long ll;
typedef double db;
const int MOD = 998244353;
const db eps = 1e-9;
const int N = 100005;
ll power(const ll & x,const ll & mi)
{
    ll s1=1LL,s2=x,m=mi;
    while (m)
    {
        if (m&1) s1=s1*s2%MOD;
        s2=s2*s2%MOD;
        m>>=1;
    }
    return s1;
}
struct Point
{
    db x,y;
}a[N];
Point operator + (const Point & x,const Point & y)
{
    return (Point){x.x+y.x,x.y+y.y};
}
Point operator - (const Point & x,const Point & y)
{
    return (Point){x.x-y.x,x.y-y.y};
}
Point operator * (const db & k,const Point & x)
{
    return (Point){k*x.x,k*x.y};
}
db dot(const Point & x,const Point & y)
{
    return x.x*y.x+x.y*y.y;
}
db cross(const Point & x,const Point & y)
{
    return x.x*y.y-x.y*y.x;
}
db dis(const Point & x,const Point & y)
{
    return sqrt((x.x-y.x)*(x.x-y.x)+(x.y-y.y)*(x.y-y.y));
}
int n;
db E_calc(const Point & t)
{
    db res=0;
    for (int i=1;i<=n;++i) res+=dis(a[i],t);
    return res;
}
Point SA(const db & T0,const db & Tk,const db & Td,const Point & t0)
{
    Point now=t0,nw;
    db E_now=E_calc(now),E_nw;
    for (db T=T0;T>Tk;T*=Td)
    {
        db xita=rand(),r=rand()*T,delta;
        nw=now+(Point){cos(xita)*r,sin(xita)*r};
        E_nw=E_calc(nw);
        delta=E_nw-E_now;
        if (delta<0)
        {
            now=nw;
            E_now=E_nw;
            continue;
        }
        if (exp(-fabs(delta)/T)*RAND_MAX>rand()) now=nw,E_now=E_nw;
    }
    return now;
}
void solve()
{
    cin>>n;
    Point t=(Point){0,0};
    for (int i=1;i<=n;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        a[i].x=x;a[i].y=y;
        t=t+a[i];
    }
    t=(1.0/n)*t;
    Point ans=SA(3000,1e-15,0.996,t);///Simulated_Annealing
    db totdis=0;
    for (int i=1;i<=n;++i) totdis+=dis(ans,a[i]);
    printf("%d\n",(int)(totdis+0.5));
    return;
}
int main()
{
    srand(19260817);
    int T=1;
    cin>>T;
    while (T--)
    {
        solve();
        if (T) puts("");
    }
    return 0;
}

