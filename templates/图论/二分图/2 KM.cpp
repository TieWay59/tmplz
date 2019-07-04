const int maxn = 500+5;
struct KM{
	int n;
	vector<int> G[maxn];
	int W[maxn][maxn];
	int Lx[maxn];
	int Ly[maxn];
	int Left[maxn];
	bool S[maxn],T[maxn];
	void init(int n){
		this->n = n;
		for(int i = 1;i <= n; ++i) G[i].clear();
		memset(W,0,sizeof(W));
	}
	void AddEdge(int u,int v,int w){
		G[u].push_back(v);
		W[u][v] = w;
	}
	bool match(int u){
		S[u] = true;
		for(int i =0;i < G[u].size(); ++i){
			int v = G[u][i];
			if(Lx[u]+Ly[v] == W[u][v]&&!T[v]){
				T[v] = true;
				if(Left[v] == -1||match(Left[v])){
				   Left[v] = u;
				   return true;	
				}
			}
		}
		return false;
	}
	void update(){
		int a = INF;
		for(int u = 0;u < n; ++u) 
		 if(S[u])
		   for(int i = 0;i < G[u].size(); ++i){
		   	int v = G[u][i];
		   	if(!T[v])
		   	  a = min(a,Lx[u]+Ly[v]-W[u][v]);
		   }
		for(int i = 0;i < n; ++i){
			if(S[i]) Lx[i] -= a;
			if(T[i]) Ly[i] += a;
		}
	}
	void solve(){
		for(int i = 0;i < n; ++i){
			Lx[i] = *max_element(W[i],W[i]+n);
			Left[i] = -1;
			Ly[i] = 0;
		}
		for(int u = 0;u < n; ++u){
			for(;;){
				for(int i = 0;i < n; ++i) S[i] = T[i]  = 0;
				if(match(u)) break;
				else update();
			}
		}
	}
};
