
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
const int    INF = 0x7FFFFFFF;
const LL     INFF =0x7FFFFFFFFFFFFFFF;
const double pi = acos(-1.0);
const double inf = 1e18;
const double eps = 1e-6;
const LL     mod = 1e9 + 7;
LL qpow(LL a,LL b) {
    LL s=1;
    while(b>0) {
        if(b&1)
            s=s*a%mod;
        a=a*a%mod;
        b>>=1;
    }
    return s;
}
LL gcd(LL a,LL b) {
    return b?gcd(b,a%b):a;
}
int dr[2][4] = {1,-1,0,0,0,0,-1,1};
typedef pair<int,int> P;
struct Edge{
	int from,to,dist;
	Edge(int u,int v,int d):from(u),to(v),dist(d){
	}
};
struct Bellman_ford {
    #define maxn  1234567
    bool inq[maxn];// 用来记录入队次数 
    int  cnt[maxn], d[maxn], p[maxn];
    // cnt 来记录入队次数，大于n就退出，d用来记录最短距离，p用来记录路径 
	int n,m;
	int s,t;
	vector<Edge> edges;
	vector<int> G[maxn];
	void AddEdge(int from,int to,int dist){
		edges.push_back(Edge(from,to,dist));
		edges.push_back(Edge(to,from,dist));
	    int 	m = edges.size();
		G[from].push_back(m-2);
		G[to].push_back(m-1);
	} 
    void init(){
        
    	scanf("%d %d %d %d",&n,&m,&s,&t);
    	int u,v,c;
    	for(int i = 0;i < m; ++i){
    	  scanf("%d %d %d",&u,&v,&c);
		  AddEdge(u,v,c);
		}
	///	cout<<"test"<<endl;
	}
    bool bellman_ford() {
        queue<int> Q;
        memset(inq,0,sizeof(inq));
        memset(cnt,0,sizeof(cnt));
        for(int i = 1; i <= n; ++i)
            d[i] = INF;
        d[s] = 0;
        inq[s] = true;
        Q.push(s);

        while(!Q.empty()) {
            int u = Q.front();
            Q.pop();
            inq[u] = false;
            for(int i = 0; i < G[u].size(); ++i) {
                Edge &e = edges[G[u][i]];
                if(d[u] < INF&& d[e.to]  > d[u]+e.dist) {
                    d[e.to] = d[u]+e.dist;
                    p[e.to] = G[u][i];
                    if(!inq[e.to]) {
                        Q.push(e.to);
                        inq[e.to] = true;
                        if(++cnt[e.to] > n)
                            return false;
                    }
                }
            }
        }
        printf("%d\n",d[t]);
        
       }
};
Bellman_ford bell;
int main(void) {
   bell.init();
   bell.bellman_ford();
    
    return 0;
}

