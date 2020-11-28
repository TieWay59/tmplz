#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MOD = 998244353;
const int N = 500005;
const ll inf = (1LL<<60);
#define pb push_back
inline int lowbit(const int & x) {return x&(-x);}
struct Bit
{
    ll x[N];
    int n;
    inline void clear()
    {
        int t=min(max(n,5),N-2);
        memset(x,0,sizeof(long long)*t);
    }
    inline void ins(int id,ll t)
    {
        for (int i=id;i<=n;i+=lowbit(i)) x[i]+=t;
    }
    inline ll prefix(int id)
    {
        ll res=0LL;
        for (int i=id;i;i^=lowbit(i)) res+=x[i];
        return res;
    }
    inline ll query(const int & l,const int & r)
    {
        return prefix(r)-prefix(l-1);
    }
}tr;
int n,m;
int main()
{
    ll op,x,y;
    cin>>n>>m;
    tr.n=n;
    for (int i=1;i<=n;++i) scanf("%lld",&x),tr.ins(i,x);
    for (int opid=1;opid<=m;++opid)
    {
        scanf("%lld%lld%lld",&op,&x,&y);
        if (op==1)
        {
            tr.ins(x,y);
        }else
        {
            printf("%lld\n",tr.query(x,y));
        }
    }
    return 0;
}
