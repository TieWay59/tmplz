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
    db x[15];
}a[15];
int n;
Point operator + (const Point & x,const Point & y)
{
    Point res;
    for (int i=1;i<=n;++i) res.x[i]=x.x[i]+y.x[i];
    return res;
}
Point operator - (const Point & x,const Point & y)
{
    Point res;
    for (int i=1;i<=n;++i) res.x[i]=x.x[i]-y.x[i];
    return res;
}
Point operator * (const db & k,const Point & x)
{
    Point res;
    for (int i=1;i<=n;++i) res.x[i]=k*x.x[i];
    return res;
}
db dis(const Point & x,const Point & y)
{
    db res=0;
    for (int i=1;i<=n+1;++i) res+=(x.x[i]-y.x[i])*(x.x[i]-y.x[i]);
    return sqrt(res);
}
db sqr(const db & x)
{
    return x*x;
}
db E_calc(const Point & t)
{
    db av=0,res=0;
    for (int i=1;i<=n+1;++i) av+=dis(a[i],t);
    av/=n+1;
    for (int i=1;i<=n+1;++i) res+=sqr(dis(a[i],t)-av);
    return res;
}
Point SA(const db & T0,const db & Tk,const db & Td,const Point & t0)
{
    Point now=t0,nw;
    db E_now=E_calc(now),E_nw;
    for (db T=T0;T>Tk;T*=Td)
    {
        db delta;
        for (int i=1;i<=n;++i) nw.x[i]=now.x[i]+T*(rand()*2-RAND_MAX);
        E_nw=E_calc(nw);
        cout<<std::setprecision(10)<<now.x[1]<<' '<<now.x[2]<<' '<<E_now<<' '<<E_nw<<endl;
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
    for (int i=1;i<=n+1;++i)
    {
        int x,y;
        for (int j=1;j<=n;++j) scanf("%lf",&a[i].x[j]);
        t=t+a[i];
    }
    t=(1.0/n)*t;
    Point ans=SA(3000,1e-15,0.996,t);///Simulated_Annealing
    db totdis=0;
    for (int i=1;i<=n;++i) totdis+=dis(ans,a[i]);
    printf("%d\n",(int)(totdis+0.5));
    for (int i=1;i<=n;++i) printf("%.3f ",ans.x[i]);puts("");
    return;
}
int main()
{
    srand(19260817);
    int T=1;
    while (T--)
    {
        solve();
        if (T) puts("");
    }
    return 0;
}

