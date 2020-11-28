#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define inf (1LL<<60)
#define N 2000005
struct segt
{
    ll mn,mx,mn_se,mx_se;
    ll add_mn,add_mn_mnh,add_mn_mxh,add_mx,add_mx_mnh,add_mx_mxh,add_x,add_xmnh,add_xmxh;
    ll mn_his,mx_his;
}tr[N];
ll a[N];
int n;
void tr_add(int p,ll addx,ll addxmnh,ll addxmxh,ll addmn,ll addmnmnh,ll addmnmxh,ll addmx,ll addmxmnh,ll addmxmxh)
{
    //cout<<"p="<<p<<' '<<tr[p].mx_his<<' '<<tr[p].mx<<' '<<addmxh<<endl;
    tr[p].mn_his=min(tr[p].mn_his,tr[p].mn+addmnmnh);
    tr[p].mx_his=max(tr[p].mx_his,tr[p].mx+addmxmxh);
    tr[p].add_mn_mnh=min(tr[p].add_mn_mnh,tr[p].add_mn+addmnmnh);
    tr[p].add_mn_mxh=max(tr[p].add_mn_mxh,tr[p].add_mn+addmnmxh);
    tr[p].add_mx_mnh=min(tr[p].add_mx_mnh,tr[p].add_mx+addmxmnh);
    tr[p].add_mx_mxh=max(tr[p].add_mx_mxh,tr[p].add_mx+addmxmxh);
    tr[p].add_xmnh=min(tr[p].add_xmnh,tr[p].add_x+addxmnh);
    tr[p].add_xmxh=max(tr[p].add_xmxh,tr[p].add_x+addxmxh);
    if (tr[p].mn_se==tr[p].mx) tr[p].mn_se+=addmx;else
    if (abs(tr[p].mn_se)!=inf) tr[p].mn_se+=addx;
    if (tr[p].mx_se==tr[p].mn) tr[p].mx_se+=addmn;else
    if (abs(tr[p].mx_se)!=inf) tr[p].mx_se+=addx;
    tr[p].add_mn+=addmn;tr[p].mn+=addmn;
    tr[p].add_mx+=addmx;tr[p].mx+=addmx;
    tr[p].add_x+=addx;
}
void tr_pushup(int p)
{
    int ls=p<<1,rs=p<<1|1;
    tr[p].mn_his=min(tr[ls].mn_his,tr[rs].mn_his);
    tr[p].mn=min(tr[ls].mn,tr[rs].mn);
    if (tr[ls].mn==tr[rs].mn) tr[p].mn_se=min(tr[ls].mn_se,tr[rs].mn_se);else tr[p].mn_se=min(min(tr[ls].mn_se,tr[rs].mn_se),max(tr[ls].mn,tr[rs].mn));
    tr[p].mx_his=max(tr[ls].mx_his,tr[rs].mx_his);
    tr[p].mx=max(tr[ls].mx,tr[rs].mx);
    if (tr[ls].mx==tr[rs].mx) tr[p].mx_se=max(tr[ls].mx_se,tr[rs].mx_se);else tr[p].mx_se=max(max(tr[ls].mx_se,tr[rs].mx_se),min(tr[ls].mx,tr[rs].mx));
}
void tr_pushdown(int p)
{
    int ls=p<<1,rs=p<<1|1;
    ll mn=min(tr[ls].mn,tr[rs].mn);
    ll mx=max(tr[ls].mx,tr[rs].mx);
    //cout<<"p="<<p<<' '<<tr[p].add_mn<<' '<<tr[p].add_mn_mnh<<endl;
    if (tr[ls].mn==tr[ls].mx)
    {
        if (tr[ls].mn==mn) tr_add(ls,0,0,0,tr[p].add_mn,tr[p].add_mn_mnh,tr[p].add_mn_mxh,tr[p].add_mn,tr[p].add_mn_mnh,tr[p].add_mn_mxh);else
        if (tr[ls].mn==mx) tr_add(ls,0,0,0,tr[p].add_mx,tr[p].add_mx_mnh,tr[p].add_mx_mxh,tr[p].add_mx,tr[p].add_mx_mnh,tr[p].add_mx_mxh);else
        tr_add(ls,0,0,0,tr[p].add_x,tr[p].add_xmnh,tr[p].add_xmxh,tr[p].add_x,tr[p].add_xmnh,tr[p].add_xmxh);
    }else
    if (tr[ls].mn==mn && tr[ls].mx==mx)
    tr_add(ls,tr[p].add_x,tr[p].add_xmnh,tr[p].add_xmxh,tr[p].add_mn,tr[p].add_mn_mnh,tr[p].add_mn_mxh,tr[p].add_mx,tr[p].add_mx_mnh,tr[p].add_mx_mxh);else
    if (tr[ls].mn==mn && tr[ls].mx!=mx)
    tr_add(ls,tr[p].add_x,tr[p].add_xmnh,tr[p].add_xmxh,tr[p].add_mn,tr[p].add_mn_mnh,tr[p].add_mn_mxh,tr[p].add_x ,tr[p].add_xmnh  ,tr[p].add_xmxh  );else
    if (tr[ls].mn!=mn && tr[ls].mx==mx)
    tr_add(ls,tr[p].add_x,tr[p].add_xmnh,tr[p].add_xmxh,tr[p].add_x ,tr[p].add_xmnh,tr[p].add_xmxh    ,tr[p].add_mx,tr[p].add_mx_mnh,tr[p].add_mx_mxh);else
    if (tr[ls].mn!=mn && tr[ls].mx!=mx)
    tr_add(ls,tr[p].add_x,tr[p].add_xmnh,tr[p].add_xmxh,tr[p].add_x ,tr[p].add_xmnh,tr[p].add_xmxh    ,tr[p].add_x ,tr[p].add_xmnh  ,tr[p].add_xmxh  );
    ///.        .
    if (tr[rs].mn==tr[rs].mx)
    {
        if (tr[rs].mn==mn) tr_add(rs,0,0,0,tr[p].add_mn,tr[p].add_mn_mnh,tr[p].add_mn_mxh,tr[p].add_mn,tr[p].add_mn_mnh,tr[p].add_mn_mxh);else
        if (tr[rs].mn==mx) tr_add(rs,0,0,0,tr[p].add_mx,tr[p].add_mx_mnh,tr[p].add_mx_mxh,tr[p].add_mx,tr[p].add_mx_mnh,tr[p].add_mx_mxh);else
        tr_add(rs,0,0,0,tr[p].add_x,tr[p].add_xmnh,tr[p].add_xmxh,tr[p].add_x,tr[p].add_xmnh,tr[p].add_xmxh);
    }else
    if (tr[rs].mn==mn && tr[rs].mx==mx)
    tr_add(rs,tr[p].add_x,tr[p].add_xmnh,tr[p].add_xmxh,tr[p].add_mn,tr[p].add_mn_mnh,tr[p].add_mn_mxh,tr[p].add_mx,tr[p].add_mx_mnh,tr[p].add_mx_mxh);else
    if (tr[rs].mn==mn && tr[rs].mx!=mx)
    tr_add(rs,tr[p].add_x,tr[p].add_xmnh,tr[p].add_xmxh,tr[p].add_mn,tr[p].add_mn_mnh,tr[p].add_mn_mxh,tr[p].add_x ,tr[p].add_xmnh  ,tr[p].add_xmxh  );else
    if (tr[rs].mn!=mn && tr[rs].mx==mx)
    tr_add(rs,tr[p].add_x,tr[p].add_xmnh,tr[p].add_xmxh,tr[p].add_x ,tr[p].add_xmnh,tr[p].add_xmxh    ,tr[p].add_mx,tr[p].add_mx_mnh,tr[p].add_mx_mxh);else
    if (tr[rs].mn!=mn && tr[rs].mx!=mx)
    tr_add(rs,tr[p].add_x,tr[p].add_xmnh,tr[p].add_xmxh,tr[p].add_x ,tr[p].add_xmnh,tr[p].add_xmxh    ,tr[p].add_x ,tr[p].add_xmnh  ,tr[p].add_xmxh  );
    tr[p].add_mn=tr[p].add_mx=tr[p].add_x=tr[p].add_mn_mnh=tr[p].add_mn_mxh=tr[p].add_mx_mnh=tr[p].add_mx_mxh=tr[p].add_xmnh=tr[p].add_xmxh=0;
}
void tr_build(int p,int l,int r)
{
    tr[p].mn=tr[p].mn_se=tr[p].mn_his= inf;
    tr[p].mx=tr[p].mx_se=tr[p].mx_his=-inf;
    tr[p].add_mn=tr[p].add_mx=tr[p].add_x=tr[p].add_mn_mnh=tr[p].add_mn_mxh=tr[p].add_mx_mnh=tr[p].add_mx_mxh=tr[p].add_xmnh=tr[p].add_xmxh=0;
    if (l==r)
    {
        tr[p].mn=tr[p].mx=tr[p].mn_his=tr[p].mx_his=a[l];
        return;
    }
    int mid=(l+r)>>1;
    tr_build(p<<1,l,mid);
    tr_build(p<<1|1,mid+1,r);
    tr_pushup(p);
}
void tr_modify_add(int p,int l,int r,int x,int y,ll t)
{
    if (x>r || l>y) return;
    if (x<=l && r<=y)
    {
        tr_add(p,t,t,t,t,t,t,t,t,t);
        return;
    }
    int mid=(l+r)>>1;
    tr_pushdown(p);
    tr_modify_add(p<<1,l,mid,x,y,t);
    tr_modify_add(p<<1|1,mid+1,r,x,y,t);
    tr_pushup(p);
}
void tr_modify_min(int p,int l,int r,int x,int y,ll t)
{
    if (x>r || l>y) return;
    if (tr[p].mx<=t) return;
    if (x<=l && r<=y)
    {
        if (tr[p].mx_se<t)
        {
            if (tr[p].mn==tr[p].mx) tr_add(p,0,0,0,t-tr[p].mx,t-tr[p].mx,t-tr[p].mx,t-tr[p].mx,t-tr[p].mx,t-tr[p].mx);
            else tr_add(p,0,0,0,0,0,0,t-tr[p].mx,t-tr[p].mx,t-tr[p].mx);
            return;
        }
    }
    int mid=(l+r)>>1;
    tr_pushdown(p);
    tr_modify_min(p<<1,l,mid,x,y,t);
    tr_modify_min(p<<1|1,mid+1,r,x,y,t);
    tr_pushup(p);
}
void tr_modify_max(int p,int l,int r,int x,int y,ll t)
{
    if (x>r || l>y) return;
    if (tr[p].mn>=t) return;
    if (x<=l && r<=y)
    {
        if (tr[p].mn_se>t)
        {
            if (tr[p].mn==tr[p].mx) tr_add(p,0,0,0,t-tr[p].mn,t-tr[p].mn,t-tr[p].mn,t-tr[p].mn,t-tr[p].mn,t-tr[p].mn);
            else tr_add(p,0,0,0,t-tr[p].mn,t-tr[p].mn,t-tr[p].mn,0,0,0);
            return;
        }
    }
    int mid=(l+r)>>1;
    tr_pushdown(p);
    tr_modify_max(p<<1,l,mid,x,y,t);
    tr_modify_max(p<<1|1,mid+1,r,x,y,t);
    tr_pushup(p);
}
ll tr_query_min(int p,int l,int r,int x,int y)
{
    if (x>r || l>y) return inf;
    //cout<<"p="<<p<<' '<<tr[p].mn<<endl;
    if (x<=l && r<=y) return tr[p].mn;
    int mid=(l+r)>>1;
    tr_pushdown(p);
    return min(tr_query_min(p<<1,l,mid,x,y),tr_query_min(p<<1|1,mid+1,r,x,y));
}
ll tr_query_minh(int p,int l,int r,int x,int y)
{
    if (x>r || l>y) return inf;
    if (x<=l && r<=y) return tr[p].mn_his;
    int mid=(l+r)>>1;
    tr_pushdown(p);
    return min(tr_query_minh(p<<1,l,mid,x,y),tr_query_minh(p<<1|1,mid+1,r,x,y));
}
ll tr_query_maxh(int p,int l,int r,int x,int y)
{
    if (x>r || l>y) return -inf;
    if (x<=l && r<=y) return tr[p].mx_his;
    int mid=(l+r)>>1;
    tr_pushdown(p);
    return max(tr_query_maxh(p<<1,l,mid,x,y),tr_query_maxh(p<<1|1,mid+1,r,x,y));
}
void solve()
{
    int type,x,y;
    ll t;
    scanf("%d",&type);
    if (type==1)
    {
        scanf("%d%d%lld",&x,&y,&t);
        tr_modify_add(1,1,n,x,y,t);
        return;
    }
    if (type==2)
    {
        scanf("%d%d%lld",&x,&y,&t);
        tr_modify_max(1,1,n,x,y,t);
        return;
    }
    if (type==3)
    {
        scanf("%d%d",&x,&y);
        printf("%lld\n",tr_query_min(1,1,n,x,y));
        return;
    }
    if (type==4)
    {
        scanf("%d%d",&x,&y);
        printf("%lld\n",tr_query_minh(1,1,n,x,y));
        return;
    }
    if (type==5)
    {
        scanf("%d%d%lld",&x,&y,&t);
        tr_modify_min(1,1,n,x,y,t);
        return;
    }
    if (type==6)
    {
        scanf("%d%d",&x,&y);
        printf("%lld\n",tr_query_maxh(1,1,n,x,y));
        return;
    }
}
int main()
{
    int Q;
    cin>>n>>Q;
    for (int i=1;i<=n;++i) scanf("%lld",&a[i]);
    tr_build(1,1,n);
    while (Q--) solve();
    return 0;
}
