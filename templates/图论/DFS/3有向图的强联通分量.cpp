
// tarjan算法
const int maxn = 2e4+100;

vector<int> G[maxn];
int pre[maxn],lowlink[maxn],sccno[maxn],dfs_clock,scc_cnt;
stack<int> S;
void dfs(int u){
    pre[u] = lowlink[u] = ++dfs_clock;
    S.push(u);
    for(int i = 0;i < G[u].size(); ++i){
        int v = G[u][i];
        if(!pre[v]){
            dfs(v);
            lowlink[u] = min(lowlink[u],lowlink[v]);

        }
    else if(!sccno[v]){
        lowlink[u] = min(lowlink[u],pre[v]);
        }
    }
    if(lowlink[u] == pre[u]){
        scc_cnt++;
        for(;;){
            int x = S.top(); S.pop();
            sccno[x] = scc_cnt;
            if(x == u) break;
        }
    }
    
}
void find_scc(int n){
    dfs_clock= scc_cnt = 0;
    me(sccno),me(pre);
    rep(i,0,n) if(!pre[i]) dfs(i);
}
// kosaraju



const int maxn = 2e4+100;
vector<int> G[maxn],G2[maxn];
vector<int> S;
int vis[maxn],sccno[maxn],scc_cnt;
void dfs1(int u){
	if(vis[u]) return ;
	vis[u] = 1;
	for(int i = 0;i < G[u].size(); ++i) dfs1(G[u][i]);
	S.push_back(u);
}
void dfs2(int u){
	if(sccno[u]) return  ;
	sccno[u] = scc_cnt;
  	for(int i = 0;i < G2[u].size(); ++i) dfs2(G2[u][i]);
}
void find_scc(int n){
	scc_cnt = 0;
	S.clear();
	memset(sccno,0,sizeof(sccno));
	memset(vis,0,sizeof(vis));
	for(int i = 0;i < n; ++i) dfs1(i);
    for(int i = n-1;i >= 0;--i){
    	if(!sccno[S[i]]) {
    		scc_cnt++;
    		dfs2(S[i]);
    	}
    }
}
