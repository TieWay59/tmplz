#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
const int MOD = 998244353;
const int N = 500005;
const ll inf = (1LL<<60);
inline int read()
{
    int x=0,f=1;
    char c=getchar();
    while (c<'0' || c>'9')
    {
        if (c=='-') f=-1;
        c=getchar();
    }
    while ('0'<=c && c<='9') x=(x<<3)+(x<<1)+c-'0',c=getchar();
    return x*f;
}
struct Segt
{
    struct Node
    {
        ll s,mx,mx_num,semx,mx_his,mx_add,mx_add_his,v_add,v_add_his;
    }tr[N<<2],zero;
    int L[N<<2],R[N<<2];
    Node merge(Node x,Node y)
    {
        Node res;
        res.s=x.s+y.s;
        res.mx=max(x.mx,y.mx);
        res.mx_num=(x.mx==res.mx)*(x.mx_num)+(y.mx==res.mx)*(y.mx_num);
        res.semx=((x.mx==y.mx) ? max(x.semx,y.semx) : ((x.mx>y.mx) ? max(x.semx,y.mx) : max(x.mx,y.semx)));
        res.mx_his=max(x.mx_his,y.mx_his);
        res.mx_add=res.mx_add_his=res.v_add=res.v_add_his=0;
        return res;
    }
    inline void upd(const int & p,const ll & mx_add,const ll & mx_add_his,const ll & v_add,const ll & v_add_his)
    {
        tr[p].s=tr[p].s+tr[p].mx_num*mx_add+v_add*(1LL+R[p]-L[p]-tr[p].mx_num);
        tr[p].mx_his=max(tr[p].mx_his,tr[p].mx+mx_add_his);
        tr[p].mx_add_his=max(tr[p].mx_add_his,tr[p].mx_add+mx_add_his);
        tr[p].v_add_his=max(tr[p].v_add_his,tr[p].v_add+v_add_his);
        tr[p].mx+=mx_add;tr[p].mx_add+=mx_add;tr[p].semx+=v_add;tr[p].v_add+=v_add;
    }
    inline void pd(const int & p)
    {
        int ls=p<<1,rs=p<<1|1;
        ll mx=max(tr[ls].mx,tr[rs].mx);
        if (tr[ls].mx==mx) upd(ls,tr[p].mx_add,tr[p].mx_add_his,tr[p].v_add,tr[p].v_add_his);
        else upd(ls,tr[p].v_add,tr[p].v_add_his,tr[p].v_add,tr[p].v_add_his);
        if (tr[rs].mx==mx) upd(rs,tr[p].mx_add,tr[p].mx_add_his,tr[p].v_add,tr[p].v_add_his);
        else upd(rs,tr[p].v_add,tr[p].v_add_his,tr[p].v_add,tr[p].v_add_his);
        tr[p].mx_add=tr[p].mx_add_his=tr[p].v_add=tr[p].v_add_his=0;
    }
    void add(int p,int l,int r,int x,int y,ll t)
    {
        if (l>y || x>r) return;
        if (x<=l && r<=y)
        {
            upd(p,t,t,t,t);
            return;
        }
        pd(p);
        int mid=(l+r)>>1;
        add(p<<1,l,mid,x,y,t);
        add(p<<1|1,mid+1,r,x,y,t);
        tr[p]=merge(tr[p<<1],tr[p<<1|1]);
    }
    void modify_mn(int p,int l,int r,int x,int y,ll t)
    {
        if (l>y || x>r) return;
        int mid=(l+r)>>1;
        if (x<=l && r<=y)
        {
            if (t>=tr[p].mx) return;
            if (t>tr[p].semx)
            {
                upd(p,t-tr[p].mx,t-tr[p].mx,0,0);
                return;
            }
        }
        pd(p);
        modify_mn(p<<1,l,mid,x,y,t);
        modify_mn(p<<1|1,mid+1,r,x,y,t);
        tr[p]=merge(tr[p<<1],tr[p<<1|1]);
    }
    Node query(int p,int l,int r,int x,int y)
    {
        if (l>y || x>r) return zero;
        if (x<=l && r<=y) return tr[p];
        pd(p);
        int mid=(l+r)>>1;
        return merge(query(p<<1,l,mid,x,y),query(p<<1|1,mid+1,r,x,y));
    }
    void build(int p,int l,int r,int *a)
    {
        L[p]=l;R[p]=r;
        if (l==r)
        {
            tr[p].s=a[l];
            tr[p].mx=a[l];
            tr[p].mx_num=1;
            tr[p].semx=-inf;
            tr[p].mx_his=a[l];
            tr[p].mx_add=tr[p].mx_add_his=0;
            tr[p].v_add=tr[p].v_add_his=0;
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
    seg.zero.s=0;
    seg.zero.mx=-inf;
    seg.zero.semx=-inf;
    seg.zero.mx_num=0;
    seg.zero.mx_his=-inf;
    cin>>n>>m;
    for (int i=1;i<=n;++i) scanf("%d",&a[i]);
    seg.build (1,1,n,a);
    for (int i=1;i<=m;++i)
    {
        int op=read(),l=read(),r=read(),t;
        if (op==1)
        {
            t=read();
            seg.add(1,1,n,l,r,t);
            continue;
        }
        if (op==2)
        {
            t=read();
            seg.modify_mn(1,1,n,l,r,t);
            continue;
        }
        if (op==3)
        {
            printf("%lld\n",seg.query(1,1,n,l,r).s);
            continue;
        }
        if (op==4)
        {
            printf("%lld\n",seg.query(1,1,n,l,r).mx);
            continue;
        }
        if (op==5)
        {
            printf("%lld\n",seg.query(1,1,n,l,r).mx_his);
            continue;
        }
    }
    return 0;
}
