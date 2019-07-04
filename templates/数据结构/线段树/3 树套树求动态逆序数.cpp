//数据范围1-n的全排列 
#include<bits/stdc++.h>
#define inf 0x7fffffff
#define N 100005
#define M 5000005
using namespace std;
typedef long long ll;
ll ans;
int n,m,sz,a[100],b[100],val[N],pos[N],a1[N],a2[N];
int c[N*10],rt[N],ls[M],rs[M],sumv[M];
inline int lowbit(int x){return x&(-x);}
inline int ask(int x){
    int ans=0;
    for(int i=x;i;i-=lowbit(i))ans+=c[i];
    return ans;
}
void change(int &o,int l,int r,int q){
    if(!o)o=++sz;sumv[o]++;
    if(l==r)return;
    int mid=(l+r)>>1;
    if(q<=mid)change(ls[o],l,mid,q);
    else change(rs[o],mid+1,r,q);
}
int querysub(int x,int y,int v){
    int cnta=0,cntb=0;int ans=0;x--;
    for(int i=x;i;i-=lowbit(i))a[++cnta]=rt[i];
    for(int i=y;i;i-=lowbit(i))b[++cntb]=rt[i];
    int l=1,r=n;
    while(l!=r){
        int mid=(l+r)>>1;
        if(v<=mid){
            for(int i=1;i<=cnta;i++)ans-=sumv[rs[a[i]]];
            for(int i=1;i<=cntb;i++)ans+=sumv[rs[b[i]]];
            for(int i=1;i<=cnta;i++)a[i]=ls[a[i]];
            for(int i=1;i<=cntb;i++)b[i]=ls[b[i]];
            r=mid;
        }
        else{
            for(int i=1;i<=cnta;i++)a[i]=rs[a[i]];
            for(int i=1;i<=cntb;i++)b[i]=rs[b[i]];
            l=mid+1;
        }
    }
    return ans;
}
int querypre(int x,int y,int v){
    int cnta=0,cntb=0,ans=0;x--;
    for(int i=x;i;i-=lowbit(i))a[++cnta]=rt[i];
    for(int i=y;i;i-=lowbit(i))b[++cntb]=rt[i];
    int l=1,r=n;
    while(l!=r){
        int mid=(l+r)>>1;
        if(v>mid){
            for(int i=1;i<=cnta;i++)ans-=sumv[ls[a[i]]];
            for(int i=1;i<=cntb;i++)ans+=sumv[ls[b[i]]];
            for(int i=1;i<=cnta;i++)a[i]=rs[a[i]];
            for(int i=1;i<=cntb;i++)b[i]=rs[b[i]];
            l=mid+1;
        }
        else{
            for(int i=1;i<=cnta;i++)a[i]=ls[a[i]];
            for(int i=1;i<=cntb;i++)b[i]=ls[b[i]];
            r=mid;
        }
    }
    return ans;
}
inline int read(){
    int f=1,x=0;char ch;
    do{ch=getchar();if(ch=='-')f=-1;}while(ch<'0'||ch>'9');
    do{x=x*10+ch-'0';ch=getchar();}while(ch>='0'&&ch<='9');
    return f*x;
}
int main(){
    n=read();m=read();
    for(int i=1;i<=n;i++){
        val[i]=read();pos[val[i]]=i;
        a1[i]=ask(n)-ask(val[i]);
        ans+=a1[i];
        for(int j=val[i];j<=n;j+=lowbit(j))c[j]++;
    }
    memset(c,0,sizeof(c));
    for(int i=n;i;i--){
        a2[i]=ask(val[i]-1);
        for(int j=val[i];j<=n;j+=lowbit(j))c[j]++;
    }
    for(int i=1;i<=m;i++){
        printf("%lld\n",ans);
        int x=read();x=pos[x];
        ans-=(a1[x]+a2[x]-querysub(1,x-1,val[x])-querypre(x+1,n,val[x]));
        for(int j=x;j<=n;j+=lowbit(j))change(rt[j],1,n,val[x]);
    }
    return 0;
}

// 对于100%的数据，n≤40000，m≤n/2，且保证第二行n个数互不相同，第三行m个数互不相同。
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<cstring>
#include<queue>
#include<vector>
#define ll long long 
const int maxn=100000+9999;
using namespace std;
int n,m,num[maxn],H[maxn],Q[maxn],cnt,root[maxn*50],t[maxn],pos[maxn];
int A[100],B[100];
ll ans;
int LO(int x){return x&-x;}
int qsum(int x){
    int tmp=0;
    for(int i=x;i;i-=LO(i))
    tmp+=t[i];
    return tmp;
}
int read(){
    int an=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while('0'<=ch&&ch<='9'){an=an*10+ch-'0';ch=getchar();}
    return an*f;
}
struct saber{
int r,l,sum;
}T[maxn*50];
int askmore(int x,int y,int wi){
    int cnt1,cnt2,tmp=0;cnt1=cnt2=0;
    for(int i=x;i;i-=LO(i))cnt1++,A[cnt1]=root[i];
    for(int i=y;i;i-=LO(i))cnt2++,B[cnt2]=root[i];
    int l=1,r=n;
    while(l!=r){
        int mid=(l+r)>>1;
        if(wi<=mid){
            for(int i=1;i<=cnt1;i++)tmp-=T[ T[ A[i] ].r ].sum;
            for(int i=1;i<=cnt2;i++)tmp+=T[ T[ B[i] ].r ].sum;
            for(int i=1;i<=cnt1;i++)A[i]=T[ A[i] ].l;
            for(int i=1;i<=cnt2;i++)B[i]=T[ B[i] ].l;
            r=mid;
        }
        else {
            for(int i=1;i<=cnt1;i++)A[i]=T[ A[i] ].r;
            for(int i=1;i<=cnt2;i++)B[i]=T[ B[i] ].r;
            l=mid+1;
        }
    }
    return tmp;
}
int askless(int x,int y,int wi){
    int cnt1,cnt2,tmp=0;
    cnt1=cnt2=0;x--;
    for(int i=x;i;i-=LO(i))cnt1++,A[cnt1]=root[i];
    for(int i=y;i;i-=LO(i))cnt2++,B[cnt2]=root[i];
    int l=1,r=n;
    while(l!=r){
        int mid=(l+r)>>1;
        if(wi>mid){
            for(int i=1;i<=cnt1;i++)tmp-=T[ T[ A[i] ].l ].sum;
            for(int i=1;i<=cnt2;i++)tmp+=T[ T[ B[i] ].l ].sum;
            for(int i=1;i<=cnt1;i++)A[i]=T[ A[i] ].r;
            for(int i=1;i<=cnt2;i++)B[i]=T[ B[i] ].r;
            l=mid+1;
        }
        else {
            for(int i=1;i<=cnt1;i++)A[i]=T[ A[i] ].l;
            for(int i=1;i<=cnt2;i++)B[i]=T[ B[i] ].l;
            r=mid;
        }
    }
    return tmp;
}
void add(int &y,int l,int r,int wi){
    if(!y)cnt++,y=cnt;
    T[y].sum++;
    if(l==r)return ;
    int mid=(l+r)>>1;
    if(wi<=mid)add(T[y].l,l,mid,wi);
    else add(T[y].r,mid+1,r,wi);
}
struct da{
int wi,i;
}data[maxn];
bool cmp1(da x,da y){
    return x.wi<y.wi;
}
bool cmp2(da x,da y){
    return x.i<y.i;
}
void prepare(){
    n=read();m=read();
    for(int i=1;i<=n;i++){
        data[i].wi=read();
        data[i].i=i;
    }
    sort(data+1,data+1+n,cmp1);
    for(int i=1;i<=n;i++){
        data[i].wi=i;
    }
    sort(data+1,data+1+n,cmp2);
    for(int i=1;i<=n;i++)
    num[i]=data[i].wi;
}
int main(){
    prepare();
    for(int i=1;i<=n;i++){
        Q[i]=qsum(n)-qsum(num[i]);//Q在i这个点前面比it大的数贡献 
        ans+=Q[i];
        for(int j=num[i];j<=n;j+=LO(j)){
            t[j]++;
        }
    }
    memset(t,0,sizeof(t));
    for(int i=n;i;i--){
        H[i]=qsum(num[i]-1);
        for(int j=num[i];j<=n;j+=LO(j))
        t[j]++;
    }
    printf("%lld ",ans);
    while(m){m--;
    int x=read();
        ans-=(H[x]+Q[x]-askmore(0,x-1,num[x])-askless(x+1,n,num[x]) );
        for(int j=x;j<=n;j+=LO(j))add(root[j],1,n,num[x]);
    printf("%lld ",ans);
    }
    return 0;
}
