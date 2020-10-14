#include<stdio.h>
#include<algorithm>
#include<string.h>
#include<set>
#include<queue>
#include<map>
#include<ctype.h>
#include<math.h>
#include<time.h>
#include<stdlib.h>
#include<unordered_map>
#include<list>
#include<complex>
#include<unordered_set>
#include<stack>
#include<string>
#include<iostream>
#define _Inf(a) memset(a,0x3f,sizeof(a))
#define _Neg1(a) memset(a,-1,sizeof(a))
#define _Rep(i,a,b) for(int (i)=a;(i)<=(b);(i)++)
using namespace std;
typedef long long ll;
const int INF = 0x3f3f3f3f;
typedef double db;
typedef complex<db> cp;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef pair<db, db> pdd;
const int MOD = 998244353;
const db EPS = 1e-8;
const db PI = acos(-1);
int sign(db x) { return x<-EPS ? -1 : x>EPS; }
int dbcmp(db l, db r) { return sign(l - r); }
ll gcd(ll a, ll b) { return b ? gcd(b, a%b) : a; }
const int MAXN = 1e5 + 54;

const int MAXG = 1e5 + 50;
struct Edge
{
    int from, to, cost, nxt;
};
struct Graph
{
    struct Edge E[MAXG];
    int cntE, head[MAXN];
    void init() { _Neg1(head); cntE = 0; }
    void addE(int a, int b, int c = 0) { E[cntE] = { a,b,c,head[a] }; head[a] = cntE++; }
};

struct Dijkstra : Graph//下面定一个变量就能用
{
    ll dist[MAXG];
    struct DNode
    {
        ll val;int id;
        bool operator< (const DNode &r)const
        {
            return val > r.val;
        }
    };
    void Init() { _Inf(dist); }

    void Get_Dist(int s)//重新计算从s开始的单源最短路
    {
        Init();
        priority_queue<DNode>pq;
        pq.push({ 0,s });
        dist[s] = 0;
        while (!pq.empty())
        {
            DNode tmp = pq.top(); pq.pop();
            if (tmp.val > dist[tmp.id])continue;
            for (int i = head[tmp.id]; i != -1; i = E[i].nxt)
            {
                if (dist[E[i].to] > dist[tmp.id] + E[i].cost)
                {
                    dist[E[i].to] = dist[tmp.id] + E[i].cost;
                    pq.push({ dist[E[i].to],E[i].to });
                }
            }
        }
    }

    int Get_Dist(int s, int t)//获取s到t的最短路
    {
        if(dist[t]==INF&&dist[s]!=0)Get_Dist(s);
        return dist[t];
    }
}Dij;
struct Dinic :Graph
{
    int curE[MAXG], s, t, dist[MAXG];

    ll dfs(int u, ll f)//不用管，不要调用
    {
        if (u == t)return f;
        int ans = 0;
        for (int &i = curE[u]; i != -1; i = E[i].nxt)
        {
            if (dist[E[i].to] == dist[u] + 1 && E[i].cost > 0)
            {
                ll tmp = dfs(E[i].to, min(f, (ll)E[i].cost));
                f -= tmp;
                E[i].cost -= tmp;
                ans += tmp;
                E[i ^ 1].cost += tmp;
                if (!f)break;
            }
        }
        if (!ans)dist[u] = -1;
        return ans;
    }

    bool bfs()//同上
    {
        _Neg1(dist);
        queue<int> q; q.push(s);
        dist[s] = 0;
        while (!q.empty())
        {
            int u = q.front(); q.pop();
            for (int i = head[u]; i != -1; i = E[i].nxt)
            {
                if (dist[E[i].to] == -1 && E[i].cost > 0)
                {
                    dist[E[i].to] = dist[u] + 1;
                    q.push(E[i].to);
                }
            }
        }
        return dist[t] != -1;
    }

    ll dinic(int x, int y, int n)//返回从x到y的最大流 要给出有n个点
    {
        s = x; t = y;
        int ans = 0;
        while (bfs())
        {
            for (int i = 1; i <= n; i++)curE[i] = head[i];
            ans += dfs(s, INF);
        }
        return ans;
    }
}Din;
int main()
{
    int T;
    scanf("%d", &T);
    while (T--)
    {
        Dij.init();Din.init();
        int n, m;
        scanf("%d%d", &n, &m);
        _Rep(i, 1, m)
        {
            int a, b, c;
            scanf("%d%d%d", &a, &b, &c);
            Dij.addE(a, b, c);
        }
        Dij.Get_Dist(1);
        for (int i = 0; i < Dij.cntE; i++)
        {
            Edge &ed = Dij.E[i];
            if (Dij.dist[ed.from] + ed.cost == Dij.dist[ed.to])
            {
                Din.addE(ed.from, ed.to, ed.cost);
                Din.addE(ed.to, ed.from, 0);
            }
        }
        printf("%lld\n",Din.dinic(1,n,n));

    }
}

/*
9 28
6 4 411
1 5 690
9 3 304
5 1 206
3 9 144
2 1 799
2 9 832
3 9 857
6 7 897
3 4 313
8 9 470
6 4 751
1 4 599
5 1 139
3 4 811
7 2 433
2 3 171
9 7 380
7 7 497
2 6 400
6 8 959
7 7 82
5 1 333
5 9 850
3 6 780
8 5 111
9 9 159
4 4 896
*/