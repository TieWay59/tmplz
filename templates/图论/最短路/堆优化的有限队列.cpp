#include <cstdio>
#include <iostream>
#include <algorithm>
#include <ext/pb_ds/priority_queue.hpp>
#define N 1000010
#define M 10000010
#define inf 100000000000000ll

using namespace std;
using namespace __gnu_pbds;

typedef long long ll;
typedef pair<ll,int> pairs;
typedef __gnu_pbds::priority_queue<pairs,greater<pairs>,pairing_heap_tag> heap;

heap Q;
heap::point_iterator p[N];
int n,m,t,cnt;
ll rxa,rxc,rya,ryc,rp;
int G[N],vis[N];
ll dis[N];
struct edge{
  int t,nx;
  ll w;
}E[M];

inline void InserT(int x,int y,ll w){
  E[++cnt].t=y;E[cnt].nx=G[x];E[cnt].w=w;G[x]=cnt;
}

inline void dijkstra(){
  for(int i=1;i<=n;i++) dis[i]=inf;
  dis[1]=0; vis[1]=0; p[1]=Q.push(pairs(0,1));
  while(!Q.empty()){
    int x=Q.top().second; Q.pop(); vis[x]=0;
    for(int i=G[x];i;i=E[i].nx)
      if(dis[E[i].t]>dis[x]+E[i].w){
    dis[E[i].t]=dis[x]+E[i].w;
    if(vis[E[i].t]) Q.modify(p[E[i].t],pairs(dis[E[i].t],E[i].t));
    else p[E[i].t]=Q.push(pairs(dis[E[i].t],E[i].t)),vis[E[i].t]=1;
      }
  }
}

int main(){
  freopen("1.in","r",stdin);
  freopen("1.out","w",stdout);
  scanf("%d%d%d%d%d%d%d%d",&n,&m,&t,&rxa,&rxc,&rya,&ryc,&rp);
  ll x=0,y=0,z=0,a,b;
  for(int i=1;i<=t;i++){
    x=(x*rxa+rxc)%rp;
    y=(y*rya+ryc)%rp;
    a=min(x%n+1,y%n+1);
    b=max(y%n+1,y%n+1);
    InserT(a,b,1e8-100*a);
  }
  for(int i=1;i<=m-t;i++){
    scanf("%lld%lld%lld",&x,&y,&a);
    InserT(x,y,a);
  }
  dijkstra();
  printf("%lld\n",dis[n]);
}
