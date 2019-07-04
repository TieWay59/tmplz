// POJ1330
// LCA的倍增算法 

#include<vector>
#include<cstdio>
#include<cstring>
using namespace std;

const int maxn = 1e4+100;
const int maxlogv = 14;
vector<int> G[maxn];
int root;

int parent[maxlogv][maxn];
int depth[maxn];

void dfs(int v,int p,int d){
	parent[0][v] = p;
	depth[v] = d;
	for(int i = 0;i < G[v].size(); ++i){
		if(G[v][i] != p){
			dfs(G[v][i],v,d+1);
		}
	}
}
void init(int V){
	dfs(root,-1,0);
	for(int k = 0;k+1 < maxlogv; ++k){
		for(int v = 0; v < V; ++v){
			if(parent[k][v] < 0) parent[k+1][v] = -1;
			else parent[k+1][v] =  parent[k][parent[k][v]];

		}
	}
}

int lca(int u,int v){
	if(depth[u] > depth[v]) swap(u,v);
	for(int k = 0;k < maxlogv; ++k){
		if(((depth[v] - depth[u]) >> k)& 1){
			v = parent[k][v];
		}

	}
	if(u == v) return u;
	for(int k = maxlogv-1; k >= 0; --k){
		if(parent[k][u] != parent[k][v]){
			u = parent[k][u];
			v = parent[k][v];
		}
	}
	return parent[0][u];
}
bool OUT[maxn];
int main(void)
{

	int T;
    scanf("%d",&T);
    while(T--){
    	int n;
    	for(int i = 0;i < n; ++i) G[i].clear();
    	memset(OUT,0,sizeof(OUT));
    	scanf("%d",&n);
    	for(int i = 1;i  < n; ++i) {
    		int u,v;
    		scanf("%d %d",&u,&v);
    		u--,v--;
    		G[u].push_back(v);
            OUT[v] = 1;
    	}
    	for(int i = 0;i < n; ++i) if(!OUT[i]){
            root = i;
            break;
    	}
    	init(n);
    	int u,v;
    	scanf("%d %d",&u,&v);
    	u--,v--;
        printf("%d\n",lca(u,v)+1);
    }
   
   return 0;
}
