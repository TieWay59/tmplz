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
const int N = 1000005;
const ll inf = (1LL<<60);
#define pb push_back
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
char st[N];
int st1[N],st2[N];
int n1,n2;
int fail[N];
int kmp_match(int x,int c)
{
    if (st2[x+1]==c) return x+1;
    if (!x) return 0;
    return kmp_match(fail[x],c);
}
int main()
{
    scanf("%s",st);
    n1=strlen(st);for (int i=1;i<=n1;++i) st1[i]=st[i-1];
    scanf("%s",st);
    n2=strlen(st);for (int i=1;i<=n2;++i) st2[i]=st[i-1];
    fail[1]=0;
    for (int i=2;i<=n2;++i) fail[i]=kmp_match(fail[i-1],st2[i]);
    for (int i=1,j=0;i<=n1;++i)
    {
        j=kmp_match(j,st1[i]);
        if (j==n2) printf("%d\n",i-n2+1);
    }
    for (int i=1;i<=n2;++i) printf("%d ",fail[i]);puts("");
    return 0;
}
