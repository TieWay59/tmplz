// dinic
#include <cstdio>//C语言io
#include <cstring>//以下是c语言常用头文件
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <cctype>
#include <cstring>
#include <cmath>
#include <iostream>//c++IO
#include <sstream>
#include <string>
#include <list>//c++常用容器
#include <vector>
#include <set>
#include <map>
#include <queue>
#include <stack>
#include <algorithm>//c++泛型的一些函数
#include <functional>//用来提供一些模版
#define fo0(i,n) for(int i = 0;i < n; ++i)
#define fo1(i,n) for(int i = 1;i <= n; ++i)
#define mem(ar,num) memset(ar,num,sizeof(ar))
#define me(ar) memset(ar,0,sizeof(ar))
#define lowbit(x) (x&(-x))
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
const int    prime = 999983;
const int    INF = 0x7FFFFFFF;
const LL     INFF =0x7FFFFFFFFFFFFFFF;
const double pi = acos(-1.0);
const double inf = 1e18;
const double eps = 1e-6;
const LL     mod = 1e9 + 7;
const int LEN = 20000+1000;
const int maxn = 1e8;
struct Edge{
  int from,to,cap,flow;
  Edge(int u,int v,int w,int f): from(u),to(v),cap(w),flow(f){}
};
struct Dinic{
   int n,m,s,t;
   vector<Edge> edges;
   vector<int> G[LEN];
   int a[LEN];
   int vis[LEN];
   int d[LEN];
   int cur[LEN];//好吧就是点, 代表该点在一次求增广的过程中搜索到了那条边,意思就是从这条边往下肯定搜索不到结果了
   void init(int n)
   {
       this->n  = n;
       for(int i = 0;i < n; ++i)
        G[i].clear();
       edges.clear();
   }
   void Add(int u,int v,int w)
   {
       edges.push_back(Edge(u,v,w,0));
       edges.push_back(Edge(v,u,0,0));
       m = edges.size();
       G[u].push_back(m-2);
       G[v].push_back(m-1);
   }
   bool Bfs(void)//分层
   {
      me(d);
      me(vis);
      d[s] = 0;
      vis[s] = 1;

      queue<int> Q;
      Q.push(s);
      while(!Q.empty())
      {
          int q = Q.front();Q.pop();

          for(size_t i = 0;i < G[q].size();++i)
          {
              Edge &tmp = edges[G[q][i]];
              if(!vis[tmp.to]&&tmp.cap>tmp.flow)
              {
                  vis[tmp.to] = 1;
                  d[tmp.to] = d[q] + 1;
                  Q.push(tmp.to);
              }
          }
      }
      return vis[t];
   }
   int Dfs(int node,int a)
   {

       if(node == t||a == 0)
        return a;
       int flow =  0,f;
       for(int &i = cur[node];i < G[node].size();++i)
       {
          Edge &tmp = edges[G[node][i]];
          if(d[tmp.to]==d[node]+1&&(f=Dfs(tmp.to,min(a,tmp.cap-tmp.flow)))>0)
          {
              flow += f;
              tmp.flow += f;
              edges[G[node][i]^1].flow -= f;
              a -= f;
              if(a==0)
                break;
          }
       }
       return flow;
   }
   int MaxFlow(int s,int t)
   {
       this->s = s;
       this->t = t;
       int flow = 0;
       while(Bfs())
       {
           me(cur);
           flow += Dfs(s,maxn);
       }
       return flow;

   }


};
Dinic dinic;
int main()
{
    int N,M,S,T;
    while(cin>>N>>M)
    {
        S =1, T = N;
        dinic.init(N);
        int u,v,w;
        for(int i = 0;i < M;++i)
        {
            scanf("%d %d %d",&u,&v,&w);
            dinic.Add(u,v,w);
        }
        int ans = 0;
        ans = dinic.MaxFlow(S,T);
        printf("%d\n",ans);

    }



    return 0;
}
