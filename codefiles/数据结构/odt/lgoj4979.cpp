#include <bits/stdc++.h>
using std::set;
using std::cin;
using std::cout;
using std::endl;
using std::string;
typedef long long ll;
typedef double db;
struct Node_
{
    int l,r;
    mutable int v;
    inline bool operator < (const Node_ &t) const {return l<t.l;}
};
set <Node_> odt;
int n;
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
    auto it2=split(r+1),it1=split(l);
    while (it1!=odt.begin() && prev(it1)->v==v) --it1,l=it1->l;
    while (it2!=odt.end() && it2->v==v) r=it2->r,++it2;
    odt.erase(it1,it2);
    odt.insert((Node_){l,r,v});
}
char st[500005];
void solve()
{
    int x,y;
    scanf("%s%d%d",st,&x,&y);
    if (st[0]=='B')
    {
        auto it1=--odt.upper_bound((Node_){x,0,0}),it2=--odt.upper_bound((Node_){y,0,0});
        if (it1!=it2) {puts("No");return;}
        if (x==1 || y==n) {puts("Yes");return;}
        if (x==it1->l) --it1;
        if (y==it2->r) ++it2;
        if (it1->v!=it2->v) puts("Yes");else puts("No");
        return;
    }
    scanf("%s",st);
    int ch=st[0];
    modify(x,y,ch);
}
int main()
{
    cin>>n;
    scanf("%s",st);
    for (int i=1,pos=1;i<=n;i=pos+1)
    {
        int ch=st[i-1];
        while (pos<n && st[pos-1+1]==ch) ++pos;
        odt.insert((Node_){i,pos,ch});
    }
    int m;
    cin>>m;
    while (m--) solve();
    return 0;
}
