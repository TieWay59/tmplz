#include <bits/stdc++.h>
using std::set;
using std::cin;
using std::cout;
using std::endl;
typedef long long ll;
typedef double db;
struct Node_
{
    int l,r;
    mutable int v;
    inline bool operator < (const Node_ &t) const {return l<t.l;}
};
set <Node_> odt;
int n,tot_weekday;
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
void modify(int l,int r,int v)
{
    auto itr=split(r+1),itl=split(l);
    int t=0;
    for (auto it=itl;it!=itr;++it)
    {
        t+=(it->v) * (it->r - it->l + 1);
    }
    tot_weekday+=t-v*(r-l+1);
    odt.erase(itl,itr);
    odt.insert((Node_){l,r,v});
}
void solve()
{
    int x,y,k;
    scanf("%d%d%d",&x,&y,&k);
    k&=1;
    modify(x,y,k);
    printf("%d\n",tot_weekday);
}
int main()
{
    cin>>n;
    odt.insert((Node_){1,n,0});
    tot_weekday=n;
    int m;
    cin>>m;
    while (m--) solve();
    return 0;
}
