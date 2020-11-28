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
namespace FWT
{
    const int MOD = 998244353;
    const int MAXN = 1<<17;
    int a[MAXN],b[MAXN],ans[MAXN];
    int n;
    ll x,y;
    void print()
    {
        for (int i=0;i<n;++i) cout<<a[i]<<' ';cout<<endl;
        for (int i=0;i<n;++i) cout<<b[i]<<' ';cout<<endl;
        for (int i=0;i<n;++i) cout<<ans[i]<<' ';cout<<endl;
    }
    void geta(int *t)
    {
        for (int i=0;i<n;++i) a[i]=t[i];
    }
    void getb(int *t)
    {
        for (int i=0;i<n;++i) b[i]=t[i];
    }
    void Or(int *a,int p)
    {
        for (int i=1;i<n;i<<=1)
        {
            for (int j=0;j<n;j+=(i<<1))
            {
                for (int k=0;k<i;++k)
                {
                    x=a[j+k];y=a[i+j+k];
                    a[j+k]=x;
                    a[i+j+k]=(x*p+y)%MOD;
                }
            }
        }
    }
    void Work_Or(int *A,int *B,int *Ans,int nn)
    {
        for (n=1;n<nn;n<<=1) ;
        geta(A);getb(B);
        Or(a,1);
        Or(b,1);
        for (int i=0;i<n;++i) ans[i]=1LL*a[i]*b[i]%MOD;
        Or(ans,-1);
        for (int i=0;i<n;++i) Ans[i]=(ans[i]+MOD)%MOD;
    }
    void And(int *a,int p)
    {
        for (int i=1;i<n;i<<=1)
        {
            for (int j=0;j<n;j+=(i<<1))
            {
                for (int k=0;k<i;++k)
                {
                    x=a[j+k];y=a[i+j+k];
                    a[j+k]=(x+y*p)%MOD;
                    a[i+j+k]=y;
                }
            }
        }
    }
    void Work_And(int *A,int *B,int *Ans,int nn)
    {
        for (n=1;n<nn;n<<=1) ;
        geta(A);getb(B);
        And(a,1);
        And(b,1);
        for (int i=0;i<n;++i) ans[i]=1LL*a[i]*b[i]%MOD;
        And(ans,-1);
        for (int i=0;i<n;++i) Ans[i]=(ans[i]+MOD)%MOD;
    }
    void Xor(int *a,int p)
    {
        for (int i=1;i<n;i<<=1)
        {
            for (int j=0;j<n;j+=(i<<1))
            {
                for (int k=0;k<i;++k)
                {
                    x=a[j+k];y=a[i+j+k];
                    a[j+k]=(x+y)%MOD;
                    a[i+j+k]=(x-y+MOD)%MOD;
                    if (p==-1)
                    {
                        if (a[j+k]&1) a[j+k]+=MOD;
                        if (a[i+j+k]&1) a[i+j+k]+=MOD;
                        a[j+k]>>=1;
                        a[i+j+k]>>=1;
                    }
                }
            }
        }
    }
    void Work_Xor(int *A,int *B,int *Ans,int nn)
    {
        for (n=1;n<nn;n<<=1) ;
        geta(A);getb(B);
        Xor(a,1);
        Xor(b,1);
        for (int i=0;i<n;++i) ans[i]=1LL*a[i]*b[i]%MOD;
        Xor(ans,-1);
        for (int i=0;i<n;++i) Ans[i]=(ans[i]+MOD)%MOD;
    }
    void Xnor(int *a,int p)
    {
        for (int i=1;i<n;i<<=1)
        {
            for (int j=0;j<n;j+=(i<<1))
            {
                for (int k=0;k<i;++k)
                {
                    x=a[j+k];y=a[i+j+k];
                    a[j+k]=(y-x+MOD)%MOD;
                    a[i+j+k]=(y+x)%MOD;
                    if (p==-1)
                    {
                        if (a[j+k]&1) a[j+k]+=MOD;
                        if (a[i+j+k]&1) a[i+j+k]+=MOD;
                        a[j+k]>>=1;
                        a[i+j+k]>>=1;
                    }
                }
            }
        }
    }
    void Work_Xnor(int *A,int *B,int *Ans,int nn)
    {
        for (n=1;n<nn;n<<=1) ;
        geta(A);getb(B);
        Xnor(a,1);
        Xnor(b,1);
        for (int i=0;i<n;++i) ans[i]=1LL*a[i]*b[i]%MOD;
        Xnor(ans,-1);
        for (int i=0;i<n;++i) Ans[i]=(ans[i]+MOD)%MOD;
    }
}
const int MOD = 998244353;
const int N = 1<<17;
int a[N],b[N],ans[N];
void solve_FWT()
{
    int n;
    cin>>n;
    n=1<<n;
    for (int i=0;i<n;++i) scanf("%d",&a[i]);
    for (int i=0;i<n;++i) scanf("%d",&b[i]);
    FWT::Work_Or(a,b,ans,n);
    for (int i=0;i<n;++i) printf("%d ",ans[i]);puts("");
    FWT::Work_And(a,b,ans,n);
    for (int i=0;i<n;++i) printf("%d ",ans[i]);puts("");
    FWT::Work_Xor(a,b,ans,n);
    for (int i=0;i<n;++i) printf("%d ",ans[i]);puts("");
    //FWT::Work_Xnor(a,b,ans,n);
    //for (int i=0;i<n;++i) printf("%d ",ans[i]);puts("");
    return;
}
int main()
{
    solve_FWT();
    return 0;
}
