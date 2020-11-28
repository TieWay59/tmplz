#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MOD = 998244353;
const int N = 20000005;
void Exkmp(int * a,int n,int * z)
{
    z[1]=n;
    for (int i=2,l=0,r=0;i<=n;++i)
    {
        if (i<=r) z[i]=min(z[i-l+1],r-i+1);
        while (a[i+z[i]]==a[z[i]+1] && i+z[i]<=n) ++z[i];
        if (i+z[i]-1>r) l=i,r=i+z[i]-1;
    }
    return;
}
string s1,s2;
int a[N],b[N];
int Z_b[N],lcp[N];
int n,m;
ll calcans(int *a,int n)
{
    ll res=0;
    for (int i=1;i<=n;++i)
    {
        res^=1LL*i*(a[i]+1);
    }
    return res;
}
int main()
{
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    cin>>s1>>s2;
    n=s1.size();
    for (int i=1;i<=n;++i) a[i]=s1[i-1];
    m=s2.size();
    for (int i=1;i<=m;++i) b[i]=s2[i-1];
    Exkmp(b,m,Z_b);
    for (int i=1,l=0,r=0;i<=n;++i)
    {
        if (i<=r) lcp[i]=min(Z_b[i-l+1],r-i+1);
        while (a[i+lcp[i]]==b[1+lcp[i]] && i+lcp[i]<=n && 1+lcp[i]<=m) ++lcp[i];
        if (i+lcp[i]-1>r) l=i,r=i+lcp[i]-1;
    }
    cout<<calcans(Z_b,m)<<'\n';
    cout<<calcans(lcp,n)<<'\n';
    //for (int i=1;i<=m;++i) cout<<Z_b[i]<<' ';cout<<endl;
    //for (int i=1;i<=n;++i) cout<<lcp[i]<<' ';cout<<endl;
    return 0;
}
