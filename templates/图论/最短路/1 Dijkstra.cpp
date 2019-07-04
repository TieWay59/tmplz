
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
//typedef unsigned long long ULL;
//const int    prime = 999983;
//const int    INF = 0x7FFFFFFF;
//const LL     INFF =0x7FFFFFFFFFFFFFFF;
//const double pi = acos(-1.0);
//const double inf = 1e18;
//const double eps = 1e-6;
//const LL     mod = 1e9 + 7;
//LL qpow(LL a,LL b){LL s=1;while(b>0){if(b&1)s=s*a%mod;a=a*a%mod;b>>=1;}return s;}
//LL gcd(LL a,LL b) {return b?gcd(b,a%b):a;}
//int dr[2][4] = {1,-1,0,0,0,0,-1,1};
//typedef pair<int,int> P;
struct Dijkstra{
     #define maxn 1234
     #define INF   123456789
     int n,m;
     int s,t;
 
     int dis[maxn],M[maxn][maxn];
     bool vis[maxn];
     void init(){
     	scanf("%d %d %d %d",&n,&m,&s,&t);
     	int u,v,c;
        for(int i = 1;i <= n; ++i)
          for(int j = 1;j <= n; ++j)
            if(i != j)
               M[i][j] = INF;
     	for(int i = 0;i < m; ++i){
     		scanf("%d %d %d",&u,&v,&c);
     		M[u][v] = M[v][u] = min(M[u][v],c);
		 }
	 }
	void solve(){
	    memset(vis,0,sizeof(vis));
		fill(dis+1,dis+n+1,INF);
		dis[s] = 0;
		for(int i = 1;i <= n; ++i){
			int x,Min = INF;
			for(int j = 1;j <= n; ++j){
				if(!vis[j]&&dis[j] <= Min)
				  Min = dis[x=j];
			}
			vis[x] = 1;
		    
		    for(int j = 1;j <= n; ++j){
		    	if(!vis[j]&&dis[j] > dis[x]+M[x][j])
		    	  dis[j] = dis[x]+M[x][j];
			}
		
		}
			printf("%d\n",dis[t]);
	}
};
Dijkstra Dij;
int main(void)
{
  Dij.init();
  Dij.solve();

   return 0;
}
// 加了堆优化的dij

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


int dr[2][4] = {1,-1,0,0,0,0,-1,1};
typedef pair<int,int> P;
struct Edge{
	int u,v,d;
	Edge(int uu,int vv,int dd):u(uu),v(vv),d(dd){
	}
};
struct Dijstra{
	#define maxn 123456
	#define INF  123456789
	int N,M,S,T;
	
	typedef pair<int,int> P;
	vector<Edge> edges;
	vector<int> G[maxn];
	bool done[maxn];
	int d[maxn];
	int p[maxn];
	void init(){
		for(int i = 1;i <= N; ++i) G[i].clear();
		edges.clear();
		scanf("%d %d %d %d",&N,&M,&S,&T);
	//	cout<<N<<M<<S<<T<<endl;
		int u,v,w;
		for(int i = 1;i <= M; ++i){
			scanf("%d %d %d",&u,&v,&w);
			AddEdge(u,v,w);
			AddEdge(v,u,w);
		}
		
	}
	void AddEdge(int u,int v,int d){
		edges.push_back(Edge(u,v,d));
		int m = edges.size();
		G[u].push_back(m-1);	
	}
	void solve(){
		priority_queue<P,vector<P>,greater<P>> Q;
		for(int i = 1;i <= N; ++i) d[i] = INF;
		d[S] = 0;
		memset(done,0,sizeof(done));
		Q.push(P(0,S));
		while(!Q.empty()){
			P x = Q.top(); Q.pop();
			int u = x.second;
			if(done[u]) continue;
			done[u] = true;
			for(int i = 0;i <G[u].size(); ++i){
				Edge &e = edges[G[u][i]];
				if(!done[e.v]&&d[e.v] > d[u]+e.d){
					d[e.v] = d[u]+e.d;
					p[e.v] = G[u][i];
					Q.push(P(d[e.v],e.v));
				}
			}
		}
	
		printf("%d\n",d[T]);
	}
};
Dijstra Dij;
int main(void)
{
  Dij.init();
  Dij.solve();

   return 0;
}



