// Size[u] 代表以节点u为根的子树节点个数
// dp[u] 代表去除u节点后最大子树的节点个数
const int maxn = 2e4+100;
vector<int> G[maxn];
int dp[maxn];
int Size[maxn];
int n;
int ans;
void  dfs(int u,int fa){
	dp[u] = Size[u] = 0;
	for(int i = 0;i < G[u].size(); ++i){
		if(fa==G[u][i])continue;
		dfs(G[u][i],u);
		// sum += tmp;
		Size[u] += Size[G[u][i]];
		dp[u] = max(dp[u],Size[G[u][i]]);
	}
	Size[u]++;
	dp[u] = max(n-Size[u],dp[u]);
	if(dp[u] < dp[ans]) ans = u;
}
int main(void)
{
	int T;
	cin>>T;
	while(T--){
		scanf("%d",&n);
		for(int i = 1;i <= n; ++i) G[i].clear();
		for(int i = 1;i <= n-1; ++i){
			int u,v;
			scanf("%d%d",&u,&v);
			G[u].push_back(v);
			G[v].push_back(u);
		}
		ans = 0;
		dp[0] = INF;
		dfs(1,-1);
		printf("%d %d\n",ans,dp[ans]);
	}
   return 0;
}
