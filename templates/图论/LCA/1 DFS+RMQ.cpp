#include<cstdio>
#include<cstring>
#include<vector>
#include<cmath>
#include<iostream>
using namespace std;

const int maxn = 40000+100;
const int maxlogv = 17;
struct Edge{
	int to,weight;
	Edge(int t,int w):to(t),weight(w){};
};
vector<Edge> G[maxn];

int id[maxn],dis[maxn];
int vs[maxn*2],depth[maxn*2];
int dp[maxn*2][maxlogv];
void dfs(int node,int fa,int d,int &k){
   	id[node] = k;
   	vs[k] = node;
 	depth[k++] = d;
 	// dis[node] = distance;
 	for(int i = 0;i < G[node].size(); ++i){
 		Edge &t = G[node][i];
 		if(t.to == fa) continue;
 		dis[t.to] = dis[node]+t.weight;
 		dfs(t.to,node,d+1,k);
        vs[k] = node;
        depth[k++] = d;
 	}
}

void init_rmq(int n){
	
	for(int i = 0;i < n ; ++i) dp[i][0] = i;
    for(int j = 1;(1<<j) <= n; ++j){
    	for(int i = 0;i + (1<<j)-1 < n; ++i){
    		if(depth[dp[i][j-1]]< depth[dp[i+(1<<(j-1))][j-1]])
    			dp[i][j] = dp[i][j-1];
    		else
    			dp[i][j] = dp[i+(1<<(j-1))][j-1];

    	}
    }
}
int query(int l,int r){
	int k = 0;
	while((1<<(k+1)) <= r-l+1) k++;
 	if(depth[dp[l][k]] < depth[dp[r-(1<<k)+1][k]])
 		return dp[l][k];
 	else 
 		return dp[r-(1<<k)+1][k];
}
int lca(int u,int v){
	return vs[query(min(id[u],id[v]),max(id[u],id[v]))];
}
void init(int n){
	int k = 0;
	dfs(0,-1,0,k);
	init_rmq(2*n-1);
}
int main(void){
    int n,m,q;
    while(~scanf("%d%d",&n,&m)){
    	for(int i = 0;i < n; ++i) G[i].clear();
    	int u,v,w;
    	for(int i = 0;i < m; ++i){
    		scanf("%d%d%d",&u,&v,&w);
    		u--,v--;
    		G[u].push_back(Edge(v,w));
    		G[v].push_back(Edge(u,w));
    	}
    	init(n);
    	scanf("%d",&q);
    	while(q--){
    		int u,v;
    		scanf("%d %d",&u,&v);
    		u--,v--;
    		int f = lca(u,v);
    		printf("%d\n",dis[u]+dis[v]-2*dis[f]);
    	}
    }
	return 0;
}
