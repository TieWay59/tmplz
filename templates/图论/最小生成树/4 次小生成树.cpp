#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<cmath>
#include<vector>
#include<queue>
#define ll long long
using namespace std;

int getint()
{
    int i=0,f=1;char c;
    for(c=getchar();(c<'0'||c>'9')&&c!='-';c=getchar());
    if(c=='-')f=-1,c=getchar();
    for(;c>='0'&&c<='9';c=getchar())i=(i<<3)+(i<<1)+c-'0';
    return i*f;
}

const int N=100005,M=300005;
struct node
{
    int x,y,w;
    inline friend bool operator < (const node &a,const node &b)
    {
        return a.w<b.w;
    }
}bian[M];
int n,m;
int id[N],fa[N][20],mx1[N][20],mx2[N][20],dep[N];
int tot,first[N],nxt[N<<1],to[N<<1],w[N<<1];
ll totlen,ans;
bool chs[M];

void add(int x,int y,int z)
{
    nxt[++tot]=first[x],first[x]=tot,to[tot]=y,w[tot]=z;
}

int find(int x)
{
    return id[x]==x?x:id[x]=find(id[x]);
}

void kruskal()
{
    for(int i=1;i<=n;i++)id[i]=i;
    sort(bian+1,bian+m+1);
    int cnt=0;
    for(int i=1;i<=m;i++)
    {
        int x=find(bian[i].x),y=find(bian[i].y);
        if(x!=y)
        {
            cnt++;
            totlen+=bian[i].w;
            chs[i]=true;
            add(bian[i].x,bian[i].y,bian[i].w);
            add(bian[i].y,bian[i].x,bian[i].w);
            id[y]=x;
            if(cnt==n-1)break;
        }
    }
}

void dfs(int u)
{
    for(int i=1;i<20;i++)fa[u][i]=fa[fa[u][i-1]][i-1];
    for(int i=1;i<20;i++)mx1[u][i]=max(mx1[u][i-1],mx1[fa[u][i-1]][i-1]);
    for(int i=1;i<20;i++)
    {
        mx2[u][i]=max(mx2[u][i-1],mx2[fa[u][i-1]][i-1]);
        if(mx1[u][i-1]<mx1[fa[u][i-1]][i-1]&&mx2[u][i]<mx1[u][i-1])
            mx2[u][i]=mx1[u][i-1];
        if(mx1[u][i-1]>mx1[fa[u][i-1]][i-1]&&mx1[fa[u][i-1]][i-1]>mx2[u][i])
            mx2[u][i]=mx1[fa[u][i-1]][i-1];
    }
    for(int e=first[u];e;e=nxt[e])
    {
        int v=to[e];
        if(v==fa[u][0])continue;
        fa[v][0]=u;mx1[v][0]=w[e];
        dep[v]=dep[u]+1;
        dfs(v);
    }
}

int Find(int x,int y,int len)
{
    int Mx1=0,Mx2=0;
    if(dep[x]<dep[y])swap(x,y);
    int delta=dep[x]-dep[y];
    for(int i=19;i>=0;i--)
        if(delta&(1<<i))
        {
            if(Mx1>mx1[x][i]&&mx1[x][i]>Mx2)Mx2=mx1[x][i];
            if(Mx1<mx1[x][i])Mx2=max(Mx1,mx2[x][i]),Mx1=mx1[x][i];
            x=fa[x][i];
        }
    if(x==y)return Mx1==len?Mx2:Mx1;
    for(int i=19;i>=0;i--)
        if(fa[x][i]!=fa[y][i])
        {
            if(Mx1>mx1[x][i]&&mx1[x][i]>Mx2)Mx2=mx1[x][i];
            if(Mx1<mx1[x][i])Mx2=max(Mx1,mx2[x][i]),Mx1=mx1[x][i];
            x=fa[x][i];
            if(Mx1>mx1[y][i]&&mx1[y][i]>Mx2)Mx2=mx1[y][i];
            if(Mx1<mx1[y][i])Mx2=max(Mx1,mx2[y][i]),Mx1=mx1[y][i];
            y=fa[y][i];
        }
    if(Mx1>mx1[x][0]&&mx1[x][0]>Mx2)Mx2=mx1[x][0];
    if(Mx1<mx1[x][0])Mx2=max(Mx1,mx2[x][0]),Mx1=mx1[x][0];
    x=fa[x][0];
    if(Mx1>mx1[y][0]&&mx1[y][0]>Mx2)Mx2=mx1[y][0];
    if(Mx1<mx1[y][0])Mx2=max(Mx1,mx2[y][0]),Mx1=mx1[y][0];
    y=fa[y][0];
    return Mx1==len?Mx2:Mx1;
}

void solve(int e)
{
    int x=bian[e].x,y=bian[e].y,len=bian[e].w;
    int tmp=Find(x,y,len);
    ans=min(ans,totlen-tmp+len);
}

int main()
{
    //freopen("lx.in","r",stdin);
    n=getint(),m=getint();
    for(int i=1;i<=m;i++)
    {
        bian[i].x=getint();
        bian[i].y=getint();
        bian[i].w=getint();
    }
    kruskal();
    dfs(1);
    ans=1e18;
    for(int i=1;i<=m;i++)
        if(!chs[i])solve(i);
    printf("%lld",ans);
}
