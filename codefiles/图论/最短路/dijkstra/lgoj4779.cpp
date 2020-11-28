#include <bits/stdc++.h>
using std::cin;
using std::cout;
using std::endl;
using std::set;
using std::map;
using std::min;
using std::max;
using std::vector;
using std::deque;
using std::min;
using std::max;
using std::swap;
using std::string;
typedef long long ll;
typedef double db;
const int MOD = 998244353;
const int N = 100005;
const ll inf = (1LL<<60);
#define pb push_back
ll power(const ll & x,const ll & mi)
{
    ll s1=1LL,s2=x,m=mi;
    while (m)
    {
        if (m&1) s1=s1*s2%MOD;
        s2=s2*s2%MOD;
        m>>=1;
    }
    return s1;
}
struct Node_
{
    int x;ll dis;
};
bool operator < (Node_ x,Node_ y)
{
    return x.dis>y.dis;
}
std::priority_queue <Node_> heap;
int flag[N];
void dijkstra(vector <Node_> * adj,int S,ll *dis,int tot_vertex)
{
    for (int i=1;i<=tot_vertex;++i) dis[i]=inf,flag[i]=1;
    dis[S]=0LL;
    while (!heap.empty()) heap.pop();
    heap.push((Node_){S,0});
    while (!heap.empty())
    {
        Node_ t=heap.top();heap.pop();
        if (flag[t.x]==0) continue;
        flag[t.x]=0;
        for (int i=0;i<adj[t.x].size();++i)
        {
            int y=adj[t.x][i].x;
            if (dis[y]<=dis[t.x]+adj[t.x][i].dis) continue;
            dis[y]=dis[t.x]+adj[t.x][i].dis;
            heap.push((Node_){y,dis[y]});
        }
    }
}
vector <Node_> adj[N];
ll dis[N];
int n,m;
void solve()
{
    int S;
    cin>>n>>m>>S;
    for (int i=1;i<=n;++i) adj[i].clear();
    for (int i=1;i<=m;++i)
    {
        int x,y;ll t;
        scanf("%d%d%lld",&x,&y,&t);
        adj[x].pb((Node_){y,t});
    }
    ll res=0LL;
    dijkstra(adj,S,dis,n);
    for (int i=1;i<=n;++i) printf("%lld ",dis[i]);puts("");
}
int main()
{
    int T=1;
    //cin>>T;
    while (T--) solve();
    return 0;
}
