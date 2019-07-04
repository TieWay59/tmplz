
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#include<vector>
#define SF scanf
#define PF printf
#define MAXN 510
using namespace std;
int mk[MAXN],fa[MAXN],nxt[MAXN],q[MAXN],vis[MAXN],match[MAXN];
int fr,bk,t,n,m;
vector<int> a[MAXN];
int find(int x){
    if(fa[x]==x)
        return x;
    fa[x]=find(fa[x]);
    return fa[x];
}
int LCA(int x,int y){
    t++;
    while(1){
        if(x){
            x=find(x);
            if(vis[x]==t)
                return x;
            vis[x]=t;
            if(match[x])
                x=nxt[match[x]];
            else
                x=0;
        }
        swap(x,y);
    }
}
void Union(int x,int y){
    if(find(x)!=find(y))
        fa[fa[x]]=fa[y];
}
void gr(int a,int p){
    while(a!=p){
        int b=match[a];
        int c=nxt[b];
        if(find(c)!=p)
            nxt[c]=b;
        if(mk[b]==2){
            q[++bk]=b;
            mk[b]=1;
        }
        Union(a,b);
        Union(b,c);
        a=c;
    }
}
void aug(int S){
    for(int i=1;i<=n;i++){
        mk[i]=nxt[i]=0;
        fa[i]=i;
    }
    mk[S]=1;
    fr=bk=0;
    q[fr]=S;
    while(fr<=bk){
        int x=q[fr++];
        for(int i=0;i<a[x].size();i++){
            int y=a[x][i];
            if(match[x]==y)
                continue;
            else if(find(x)==find(y))
                continue;
            else if(mk[y]==2)
                continue;
            else if(mk[y]==1){
                int r=LCA(x,y);
                if(find(x)!=r)
                    nxt[x]=y;
                if(find(y)!=r)
                    nxt[y]=x;
                gr(x,r);
                gr(y,r);
            }
            else if(!match[y]){
                nxt[y]=x;
                for(int u=y;u;){
                    int v=nxt[u];
                    int mv=match[v];
                    match[u]=v;
                    match[v]=u;
                    u=mv;
                }
                return;
            }
            else{
                nxt[y]=x;
                mk[y]=2;
                q[++bk]=match[y];
                mk[match[y]]=1;
            }
        }
    }
}
int main(){
    SF("%d%d",&n,&m);
    int u,v;
    for(int i=1;i<=m;i++){
        SF("%d%d",&u,&v);
        a[u].push_back(v);
        a[v].push_back(u);
    }
    for(int i=1;i<=n;i++)
        if(!match[i])
            aug(i);
    int sum=0;
    for(int i=1;i<=n;i++)
        if(match[i])
            sum++;
    PF("%d\n",sum/2);
    for(int i=1;i<=n;i++)
        PF("%d ",match[i]);
}
