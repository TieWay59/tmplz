#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define pb push_back
struct pll
{
    ll x,y;
};
struct dijkcmp
{
    bool operator () (pll a,pll b)
    {
        if (a.y!=b.y) return (a.y>b.y);
        return a.x>b.x;
    }
};
const ll MAXDIS = 1000000000;
const int N = 3005;
const int M = 6005;
struct Edge
{
    int u,v;
    ll t;
};
ll height[N];
int inq[N],vis[N];
queue <int> q;
vector <pll> adj[N];
priority_queue <pll,vector<pll>,dijkcmp> heap;
int spfa(Edge * e,int n,int m)
{
    while (!q.empty()) q.pop();
    for (int i=1;i<=n;++i)
    {
        height[i]=vis[i]=0;
        q.push(i);
        inq[i]=1;
        adj[i].clear();
    }
    for (int i=1;i<=m;++i) adj[e[i].u].pb((pll){e[i].v,e[i].t});
    while (!q.empty())
    {
        int u=q.front(),v;q.pop();
        inq[u]=0;
        for (auto i:adj[u])
        {
            v=i.x;
            if (height[v]>height[u]+i.y)
            {
                height[v]=height[u]+i.y;
                if (!inq[v])
                {
                    q.push(v);
                    inq[v]=1;
                    ++vis[v];
                    if (vis[v]>n) return -1;
                }
            }
        }
    }
    //cout<<"height=";for (int i=1;i<=n;++i) cout<<height[i]<<' ';cout<<endl;
    return 1;
}
void dijkstra(vector <pll> * adj,int n,int m,int S,ll * dis)
{
    while (!heap.empty()) heap.pop();
    for (int i=1;i<=n;++i) vis[i]=0,dis[i]=MAXDIS;
    dis[S]=0;
    heap.push((pll){S,dis[S]});
    while (!heap.empty())
    {
        pll u = heap.top();heap.pop();
        if (vis[u.x]) continue;
        vis[u.x]=1;
        for (auto i:adj[u.x])
        if (dis[i.x]>dis[u.x]+i.y)
        {
            dis[i.x]=dis[u.x]+i.y;
            heap.push((pll){i.x,dis[i.x]});
        }
    }
}
ll dis[N][N];
int johnson(Edge * e,int n,int m)
{
    if (spfa(e,n,m)==-1) return -1;
    for (int i=1;i<=n;++i) adj[i].clear();
    for (int i=1;i<=m;++i)
    {
        adj[e[i].u].pb((pll){e[i].v,height[e[i].u]-height[e[i].v]+e[i].t});
    }
    for (int i=1;i<=n;++i)
    {
        dijkstra(adj,n,m,i,dis[i]);
        for (int j=1;j<=n;++j) if (dis[i][j]<MAXDIS) dis[i][j]+=height[j]-height[i];
    }
    return 1;
}
Edge e[M];
int n,m;
int main()
{
    cin>>n>>m;
    for (int i=1;i<=m;++i) scanf("%d%d%lld",&e[i].u,&e[i].v,&e[i].t);
    if (johnson(e,n,m)==-1) {puts("-1");return 0;}
    for (int i=1;i<=n;++i)
    {
        ll res=0;
        for (int j=1;j<=n;++j) res+=dis[i][j]*j;
        printf("%lld\n",res);
    }
    return 0;
}
