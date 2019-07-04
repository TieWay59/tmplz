// 无向图的点联通分量

const int maxn= 1000+10;
int pre[maxn],iscut[maxn],bccno[maxn],dfs_clock,bcc_cnt;
vector<int> G[maxn],bcc[maxn];

stack<Edge> S;
int dfs(int u,int fa){
  int lowu = pre[u] = ++dfs_clock;
  int child = 0;
  for(int i = 0;i < G[u].size(); ++i){
    int v = G[u][i];
    Edge e = (Edge) {u,v};
    if(!pre[v]){
      S.push(e);
      child++;
      int lowv = dfs(v,u);
      lowu = min(lowu,lowv);
      if(lowv >= pre[u]){
        iscut[u] = true;
        bcc_cnt++;
        bcc[bcc_cnt].clear();
        for(;;){
          Edge x = S.top(); S.pop();
          if(bccno[x.u] != bcc_cnt) {bcc[bcc_cnt].push_back(x.u); bccno[x.u] = bcc_cnt;}
          if(bccno[x.v] != bcc_cnt) {bcc[bcc_cnt].push_back(x.v); bccno[x.v] = bcc_cnt;}
          if(x.u == u&&x.v == v) break;

        }
      }
    }
    else if(pre[v] < pre[u]&&v != fa){
      S.push(e);lowu = min(pre[v],lowu);
    }
  }
  if(fa < 0&& child == 1) iscut[u] = 0;
  return lowu;
}
void find_bcc(int n){
  memset(pre,0,sizeof(pre));
  memset(iscut,0,sizeof(iscut));
  memset(bccno,0,sizeof(bccno));
  dfs_clock = bcc_cnt = 0;
  for(int i = 0;i < n; ++i) if(!pre[i]) dfs(i,-1);

}

//无向图的边-双联通分量
// 第一边dfs求出所有的割边，然后第二边dfs求出所有边—双连通分量（不经过割边）
