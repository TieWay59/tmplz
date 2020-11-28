#include <bits/stdc++.h>
using namespace std;
typedef double typedis;
const double eps = 1e-9;
const typedis MAXDIS = 1000000000;
const int N = 5005;
const int M = 1000005;
#define pb push_back
struct Edge
{
    int u,v;typedis t;
};
bool operator < (Edge x,Edge y)
{
    return x.t>y.t;
}
priority_queue <Edge> heap;
vector <Edge> radj[N],feishubian[N];
typedis dis[N];
int flag[N],father[N],shubian[N];
vector <int> zdlt[N];
queue <int> qu;
struct PersistentLeftistTree
{
    struct Node
    {
        int l,r,dis,id;
        typedis k;
    }node[M*20];
    int rt[N];
    int nodecnt;
    void init()
    {
        nodecnt=0;
    }
    int newnode()
    {
        int cur=++nodecnt;
        return cur;
    }
    int merge(int x,int y)
    {
        if ((!x) || (!y)) return x+y;
        if (node[x].k>node[y].k) swap(x,y);
        int cur=newnode();
        node[cur]=node[x];
        node[cur].r=merge(node[cur].r,y);
        if (node[node[cur].l].dis<node[node[cur].r].dis) swap(node[cur].l,node[cur].r);
        node[cur].dis=node[node[cur].r].dis+1;
        return cur;
    }
}zpt;
typedis E;
void KthShortestPath(Edge * e,int n,int m,int K,int S,int T,vector <typedis> & ans)
{
    ///chu shi hua
    ans.clear();
    for (int i=1;i<=n;++i)
    {
        zdlt[i].clear();feishubian[i].clear();radj[i].clear();
        dis[i]=MAXDIS,flag[i]=1,father[i]=shubian[i]=0;
    }
    ///fan xiang tu
    for (int i=1;i<=m;++i) radj[e[i].v].pb((Edge){i,e[i].u,e[i].t});
    ///zui duan lu
    dis[T]=0;
    while (!heap.empty()) heap.pop();
    Edge t;
    t=(Edge){T,0,0};
    heap.push(t);
    while (!heap.empty())
    {
        t=heap.top();heap.pop();
        if (!flag[t.u]) continue;
        flag[t.u]=0;
        for (auto i:radj[t.u])
        if (dis[i.v]>dis[t.u]+i.t)
        {
            dis[i.v]=dis[t.u]+i.t;
            father[i.v]=t.u;
            shubian[i.v]=i.u;
            heap.push((Edge){i.v,0,dis[i.v]});
        }
    }
    for (int i=1;i<=m;++i) if (i!=shubian[e[i].u])
    {
        ///!!!
        ///if (e[i].u==T) continue;///attention
        ///!!!
        feishubian[e[i].u].pb((Edge){i,e[i].v,dis[e[i].v]-dis[e[i].u]+e[i].t});
        ///cout<<"add edge : "<<e[i].u<<" - > "<<e[i].v<<"     "<<dis[e[i].v]-dis[e[i].u]+e[i].t<<endl;
    }
    for (int i=1;i<=n;++i) if (father[i]) zdlt[father[i]].pb(i);
    while (!qu.empty()) qu.pop();
    qu.push(T);
    zpt.init();
    while (!qu.empty())
    {
        int x=qu.front();qu.pop();
        zpt.rt[x]=zpt.rt[father[x]];
        for (auto i:feishubian[x])
        {
            int cur=zpt.newnode();
            zpt.node[cur].l=zpt.node[cur].r=0;
            zpt.node[cur].dis=1;
            zpt.node[cur].k=i.t;
            zpt.node[cur].id=i.u;
            zpt.rt[x]=zpt.merge(zpt.rt[x],cur);
        }
        for (auto y:zdlt[x]) qu.push(y);
    }
    heap.push((Edge){S,0,dis[S]});
    for (int i=1,nw;i<=K && !heap.empty();++i)
    {
        Edge t=heap.top();heap.pop();
        ///!!!
        if (t.t>E+eps) continue;///attention!
        E-=t.t;
        ///!!!
        ans.pb(t.t);
        nw=zpt.rt[t.u];
        if (nw)
            heap.push((Edge){e[zpt.node[nw].id].v,nw,zpt.node[nw].k+t.t});
        nw=zpt.node[t.v].l;
        if (nw)
            heap.push((Edge){e[zpt.node[nw].id].v,nw,zpt.node[nw].k-zpt.node[t.v].k+t.t});
        nw=zpt.node[t.v].r;
        if (nw)
            heap.push((Edge){e[zpt.node[nw].id].v,nw,zpt.node[nw].k-zpt.node[t.v].k+t.t});
    }
    ///for (int i=1;i<=n;++i) cout<<i<<' '<<dis[i]<<' '<<father[i]<<' '<<shubian[i]<<endl;
}
vector <typedis> ans;
Edge e[M];
int n,m;
int main()
{
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    cin>>n>>m>>E;
    for (int i=1;i<=m;++i)
    {
        int x,y;typedis t;
        cin>>x>>y>>t;
        e[i]=(Edge){x,y,t};
    }
    int S=1,T=n;
    KthShortestPath(e,n,m,10000000,S,T,ans);
    cout<<ans.size()<<endl;
    ///for (int i=0;i<ans.size();++i) cout<<"i="<<i<<' '<<ans[i]<<endl;
    return 0;
}
