#include <bits/stdc++.h>
using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::pair;
using std::set;
using std::map;
typedef long long ll;
typedef double db;
const int N = 100005;
struct Node_
{
    int l,r;
    mutable ll v;
    inline bool operator < (const Node_ &t) const {return l<t.l;}
};
set <Node_> odt;
ll a[N];
ll n,m,seed,vmax;
auto split(int x)
{
    if (x>n) return odt.end();
    auto it=--odt.upper_bound((Node_){x,0,0});
    if (it->l==x) return it;
    Node_ t=(*it);
    odt.erase(it);
    odt.insert((Node_){t.l,x-1,t.v});
    return odt.insert((Node_){x,t.r,t.v}).first;
}
ll rnd()
{
    ll ret = seed;
    seed = (seed * 7 + 13) % 1000000007;
    return ret;
}
ll power(ll x,ll m,ll p)
{
    ll s1=1LL,s2=x%p;
    while (m)
    {
        if (m&1) s1=s1*s2%p;
        m>>=1;
        s2=s2*s2%p;
    }
    return s1;
}
vector <pair<ll,int> > temp;
int main()
{
    int tot=0;
    cin>>n>>m>>seed>>vmax;
    for (int i=1;i<=n;++i) a[i] = (rnd() % vmax) + 1;
    for (int i=1,pos;i<=n;i=pos+1)
    {
        pos=i;
        while (pos<n && a[pos+1]==a[i]) ++pos;
        odt.insert((Node_){i,pos,a[i]});
    }
    ll op,l,r,x,y;
    for (int i=1;i<=m;++i)
    {
        op = (rnd() % 4) + 1;
        l = (rnd() % n) + 1;
        r = (rnd() % n) + 1;
        if (l > r) std::swap(l, r);
        if (op == 3) x = (rnd() % (r - l + 1)) + 1;else x = (rnd() % vmax) + 1;
        if (op == 4) y = (rnd() % vmax) + 1;
        auto it2=split(r+1),it1=split(l);
        if (op==1)
        {
            for (auto it=it1;it!=it2;++it) it->v+=x;
        }
        if (op==2)
        {
            odt.erase(it1,it2);
            odt.insert((Node_){(int)l,(int)r,x});
        }
        if (op==3)
        {
            //cout<<++tot<<' '<<3<<endl;
            temp.clear();
            for (auto it=it1;it!=it2;++it)
            {
                temp.push_back(pair<ll,int>{it->v,it->r - it->l + 1});
            }
            std::sort(temp.begin(),temp.end());
            for (auto it=temp.begin();it!=temp.end();++it)
            {
                x-=it->second;
                if (x<=0) {printf("%lld\n",it->first);break;}
            }
        }
        if (op==4)
        {
            //cout<<++tot<<' '<<4<<' '<<x<<' '<<y<<endl;
            ll res=0;
            for (auto it=it1;it!=it2;++it)
            {
                (res+=power(it->v,x,y)*(it->r - it->l + 1))%=y;
            }
            printf("%lld\n",res);
        }
    }
    return 0;
}
