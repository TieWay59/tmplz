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
const int N = 500005;
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
inline int getid(int x,int n)
{
    if (x%n==0) return n;
    return x%n;
}
int Mnid(int *a,int n)
{
    int mnid=1;
    for (int i=2,k;i<=n;)
    {
        for (k=1;k<=n;++k) if (a[getid(i+k-1,n)]!=a[getid(mnid+k-1,n)]) break;
        if (k>n) break;
        if (a[getid(i+k-1,n)]<a[getid(mnid+k-1,n)])
        {
            int ii=i;
            i=max(mnid+k,ii+1);
            mnid=ii;
        }else i+=k;
    }
    //cout<<mnid<<endl;
    return mnid;
}
int a[N];
int n;
int main()
{
    cin>>n;
    for (int i=1;i<=n;++i) scanf("%d",&a[i]);
    int mnid=Mnid(a,n);
    for (int i=mnid;i<mnid+n;++i) printf("%d ",a[getid(i,n)]);puts("");
    return 0;
}
