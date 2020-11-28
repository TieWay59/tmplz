#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
const int MOD = 998244353;
const int N = 100005;
struct Segt
{
    struct Node
    {
        ll s,sz,tag;
    }tr[N<<2];
    inline Node merge(const Node & x,const Node & y)
    {
        return (Node){x.s+y.s,x.sz+y.sz,0};
    }
    inline void pushdown(const int p)
    {
        if (!tr[p].tag) return;
        int ls=p<<1,rs=p<<1|1;
        tr[ls].tag+=tr[p].tag;tr[ls].s+=tr[p].tag*tr[ls].sz;
        tr[rs].tag+=tr[p].tag;tr[rs].s+=tr[p].tag*tr[rs].sz;
        tr[p].tag=0;
    }
    void add(int p,int l,int r,int x,int y,ll t)
    {
        if (l>y || x>r) return;
        if (x<=l && r<=y)
        {
            tr[p].s+=t*tr[p].sz;
            tr[p].tag+=t;
            return;
        }
        pushdown(p);
        int mid=(l+r)>>1;
        add(p<<1,l,mid,x,y,t);
        add(p<<1|1,mid+1,r,x,y,t);
        tr[p]=merge(tr[p<<1],tr[p<<1|1]);
    }
    Node query(int p,int l,int r,int x,int y)
    {
        if (l>y || x>r) return (Node){0,0,0};
        if (x<=l && r<=y) return tr[p];
        pushdown(p);
        int mid=(l+r)>>1;
        return merge(query(p<<1,l,mid,x,y),query(p<<1|1,mid+1,r,x,y));
    }
    void build(int p,int l,int r,int *a)
    {
        tr[p].s=tr[p].tag=0;
        if (l==r)
        {
            tr[p].s=a[l];
            tr[p].sz=1;
            return;
        }
        int mid=(l+r)>>1;
        build(p<<1,l,mid,a);
        build(p<<1|1,mid+1,r,a);
        tr[p]=merge(tr[p<<1],tr[p<<1|1]);
    }
}seg;
int a[N];
int n,m;
int main()
{
    cin>>n>>m;
    for (int i=1;i<=n;++i) scanf("%d",&a[i]);
    seg.build(1,1,n,a);
    for (int cas=1;cas<=m;++cas)
    {
        ll op,x,y,k;
        scanf("%lld",&op);
        if (op==1)
        {
            scanf("%lld%lld%lld",&x,&y,&k);
            seg.add(1,1,n,x,y,k);
            continue;
        }
        if (op==2)
        {
            scanf("%lld%lld",&x,&y);
            printf("%lld\n",seg.query(1,1,n,x,y).s);
            continue;
        }
        puts("ERROR");
    }
    return 0;
}

