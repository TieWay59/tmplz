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
struct Complex
{
    db x,y;
};
Complex operator + (const Complex & x , const Complex & y)
{
    return (Complex){x.x + y.x , x.y + y.y};
}
Complex operator - (const Complex & x , const Complex & y)
{
    return (Complex){x.x - y.x , x.y - y.y};
}
Complex operator * (const Complex & x , const Complex & y)
{
    return (Complex){x.x * y.x - x.y * y.y , x.y * y.x + x.x * y.y};
}
namespace FFT
{
    const db pi = acos(-1.0);
    const db eps = (1e-9);
    const int N = 5000005;
    Complex a[N],b[N];
    int ans[N],rev[N];
    int n,len;
    void prepare()
    {
        int t=1;
        len=0;
        while (t<n) t<<=1,len++;
        n=t;
        for (int i=0;i<n;++i) rev[i]=(rev[i >> 1] >> 1) | ((i & 1) << (len - 1));
    }
    void FFT(Complex * a,int type)
    {
        for (int i=1;i<n;++i) if (i<rev[i]) swap(a[i],a[rev[i]]);
        for (int i=1;i<n;i<<=1)
        {
            Complex wn = (Complex){cos(pi / i) , sin(pi / i) * type};
            for (int j=0;j<n;j+=(i<<1))
            {
                Complex w = (Complex){1 , 0};
                for (int k=0;k < i;++k)
                {
                    Complex x = a[j + k],y = w * a[j + k + i];
                    a[j + k] = x + y;
                    a[j + k + i] = x - y;
                    w = w * wn;
                }
            }
        }
        if (type == -1)
        {
            //for (int i=0;i < n;++i) a[i].x;
        }
        return;
    }
    void FFT_work()
    {
        FFT(a,1);
        FFT(b,1);
        for (int i=0;i<n;++i) a[i] = a[i] * b[i];
        FFT(a,-1);
        for (int i=0;i<n;++i) ans[i]=(int)(a[i].x / n + 0.5);
    }
}
namespace NTT
{
    const int MOD = 998244353;
    const int N = 5000005;
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
    int a[N],b[N];
    int ans[N],rev[N];
    int n,len,g;
    inline int getmod(const int & x)
    {
        return (x>=MOD) ? x - MOD : x;
    }
    void prepare()
    {
        int t=1;
        len=0;
        while (t<n) t<<=1,len++;
        n=t;
        for (int i=0;i<n;++i) rev[i]=(rev[i >> 1] >> 1) | ((i & 1) << (len - 1));
        g=3;
    }
    void NTT(int * a,int type)
    {
        for (int i=1;i<n;++i) if (i<rev[i]) swap(a[i],a[rev[i]]);
        for (int i=1;i<n;i<<=1)
        {
            int wn = power(g , (MOD - 1) / (i<<1));
            if (type==-1) wn = power(wn , MOD - 2);
            for (int j=0;j<n;j+=(i<<1))
            {
                int w = 1;
                for (int k=0;k < i;++k)
                {
                    int x = a[j + k],y = 1LL * w * a[j + k + i] % MOD;
                    a[j + k] = getmod(x + y);
                    a[j + k + i] = getmod(MOD + x - y);
                    w = 1LL * w * wn % MOD;
                }
            }
        }
        if (type == -1)
        {
            //for (int i=0;i < n;++i) a[i].x;
        }
        return;
    }
    void NTT_work()
    {
        NTT(a,1);
        NTT(b,1);
        for (int i=0;i<n;++i) a[i] = 1LL * a[i] * b[i] % MOD;
        NTT(a,-1);
        ll nyn = power(n , MOD - 2);
        for (int i=0;i<n;++i) ans[i]=nyn * a[i] % MOD;
    }
}
const int N = 5000005;
int a[N],b[N];
void solve_FFT()
{
    int n,m;
    cin>>n>>m;
    ++n;++m;
    FFT::n=n+m-1;
    FFT::prepare();
    for (int i=0;i<n;++i) scanf("%d",&a[i]);
    for (int i=0;i<m;++i) scanf("%d",&b[i]);
    for (int i=0;i<FFT::n;++i) FFT::a[i]=(Complex){(db)a[i],0};
    for (int i=0;i<FFT::n;++i) FFT::b[i]=(Complex){(db)b[i],0};
    FFT::FFT_work();
    for (int i=0;i<n+m-1;++i) printf("%d ",FFT::ans[i]);puts("");
    return;
}
void solve_NTT()
{
    int n,m;
    cin>>n>>m;
    ++n;++m;
    NTT::n=n+m-1;
    NTT::prepare();
    for (int i=0;i<n;++i) scanf("%d",&a[i]);
    for (int i=0;i<m;++i) scanf("%d",&b[i]);
    for (int i=0;i<NTT::n;++i) NTT::a[i]=a[i];
    for (int i=0;i<NTT::n;++i) NTT::b[i]=b[i];
    NTT::NTT_work();
    for (int i=0;i<n+m-1;++i) printf("%d ",NTT::ans[i]);puts("");
    return;
}
int main()
{
    ///solve_FFT();
    solve_NTT();
    return 0;
}
