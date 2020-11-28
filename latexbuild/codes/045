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
int lowbit(const int & x) {return x&(-x);}
struct Tree_Array
{
    ll x[N],n;
    void ins(int id,ll t)
    {
        for (int i=id;i<=n;i+=lowbit(i)) x[i]+=t;
    }
    ll prefix(int id)
    {
        ll res=0LL;
        for (int i=id;i;i^=lowbit(i)) res+=x[i];
        return res;
    }
    ll query(const int & l,const int & r)
    {
        return prefix(r)-prefix(l-1);
    }
}tr;
int n,m;
int main()
{
    ll op,x,y,t;
    cin>>n>>m;
    tr.n=n;
    for (ll i=1,p=0;i<=n;++i,p=x) scanf("%lld",&x),tr.ins(i,x-p);
    for (int opid=1;opid<=m;++opid)
    {
        scanf("%lld%lld",&op,&x);
        if (op==1)
        {
            scanf("%lld%lld",&y,&t);
            tr.ins(x,t);tr.ins(y+1,-t);
        }else
        {
            printf("%lld\n",tr.prefix(x));
        }
    }
    return 0;
}
