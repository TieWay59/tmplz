#include <iostream>
#include <stdio.h>
using namespace std;
#define ll long long
#define p 1000000007
#define N 666
inline ll gcd(ll x,ll y)
{
    while (y)
    {
        x%=y;
        swap(x,y);
    }
    return x;
}
inline ll read()
{
    ll x=0;
    char ch=getchar();
    while ('0'>ch || '9'<ch ) ch=getchar();
    while ('0'<=ch && ch<='9') x=(x<<3)+(x<<1)+ch-'0',ch=getchar();
    return x;
}
int ans[N][N];
ll a[N],b[N];
int n,Q;
void solve()
{
    scanf("%d%d",&n,&Q);
    for (int i=1;i<=n;++i) a[i]=read();
    for (int i=1;i<=n;++i)
    {
        b[i]=1;
        for (int j=i-1;j;--j) b[j]=(__int128)(b[j+1])*a[j]%a[i];
        ll remain=gcd(a[i],b[1]),newremain;
        for (int j=1;j<i;++j)
        if (b[j+1]%remain)
        {
            newremain=gcd(b[j+1],a[i]);
            a[j]/=remain/newremain;
            remain=newremain;
        }
        //for (int j=1;j<=i;++j) cout<<a[j]<<' ';cout<<endl;
        ans[i][i]=a[i]%p;
        for (int j=i-1;j;--j)
        {
            ans[j][i]=(a[j]%p)*(ans[j+1][i])%p;
        }
    }
    while (Q--)
    {
        int l,r;
        scanf("%d%d",&l,&r);
        printf("%d\n",ans[l][r]);
    }
    return;
}
int main()
{
    int T;
    scanf("%d",&T);
    while (T--) solve();
    return 0;
}
