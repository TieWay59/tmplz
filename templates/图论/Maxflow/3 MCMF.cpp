// 最小费用最大流，下标从1 开始 

#include <bits/stdc++.h>
#define mem(ar,num) memset(ar,num,sizeof(ar))
#define me(ar) memset(ar,0,sizeof(ar))
#define lowbit(x) (x&(-x))
#define Pb push_back
#define  FI first
#define  SE second
#define For(i,a,b) for(int i = a; i < b; ++i)
#define IOS ios::sync_with_stdio(false)
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
const int    prime = 999983;
const int    INF = 1e8;
const LL     INFF =0x7FFFFFFFFFFFFFFF;
const double pi = acos(-1.0);
const double inf = 1e18;
const double eps = 1e-6;
const LL     mod = 1e9 + 7;
LL qpow(LL a,LL b){LL s=1;while(b>0){if(b&1)s=s*a%mod;a=a*a%mod;b>>=1;}return s;}
LL gcd(LL a,LL b) {return b?gcd(b,a%b):a;}
int dr[2][4] = {1,-1,0,0,0,0,-1,1};
typedef pair<int,int> P;
struct Edge{
   int from,to,cap,flow,cost;
}; 
const int maxn = 5000+100;
struct MCMF{
	int n,m,s,t;
	vector<Edge> edges;
	vector<int> G[maxn];
	int inq[maxn];
	int d[maxn];
	int p[maxn];
	int a[maxn];
	void init(int n){
		this->n = n;
		for(int i = 0;i < n; ++i) G[i].clear();
		edges.clear();
	} 
	void AddEdge(int from,int to,int cap,int cost){
		edges.push_back((Edge){from,to,cap,0,cost});
		edges.push_back((Edge){to,from,0,0,-cost});
		int m = edges.size();
		G[from].push_back(m-2);
		G[to].push_back(m-1);
		
	}
	bool BellmanFord(int s,int t,int &flow,int &cost){
		for(int i = 0;i < n; ++i) d[i] = INF;
		memset(inq,0,sizeof(inq));
		d[s] = 0,inq[s] = 1;p[s] = 0,a[s] = INF;
		
		queue<int> Q;
		Q.push(s);
		while(!Q.empty()){
		
			int u = Q.front(); Q.pop();
			inq[u] = 0;
			for(int i = 0;i < G[u].size(); ++i){
				Edge& e = edges[G[u][i]];
				if(e.cap > e.flow &&d[e.to] > d[u]+e.cost){
					d[e.to] = d[u]+e.cost;
					p[e.to] = G[u][i];
					a[e.to] = min(a[u],e.cap-e.flow);
					if(!inq[e.to]) {
						Q.push(e.to); inq[e.to] = 1;
					}
				}
			} 
		}
	
		if(d[t] == INF) return false;
	    
		flow += a[t];
		cost += d[t]*a[t];
		int u = t;
		while(u != s){
			edges[p[u]].flow += a[t];
			edges[p[u]^1].flow -= a[t];
			u = edges[p[u]].from;
		} 
		return true;
	} 
	int Mincost(int s,int t,int &flow,int &cost){
		 flow = 0,cost = 0;
		
		while(BellmanFord(s,t,flow,cost));
		return cost;
	}
	
};
MCMF mcmf;
int main(void)
{
	int n,m,s,t;
	scanf("%d %d %d %d",&n,&m,&s,&t);
	int u,v,w,c;
	mcmf.init(n+1);
	while(m--){
		scanf("%d %d %d %d",&u,&v,&w,&c);
		mcmf.AddEdge(u,v,w,c);
	}
    int flow,cost;
    flow = 0,cost = 0;
    mcmf.Mincost(s,t,flow,cost);
	printf("%d %d\n",flow,cost);


   return 0;
}
