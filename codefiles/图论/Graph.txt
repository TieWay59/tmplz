const int MAXG = -1;
struct Edge
{
	int from, to, cost, nxt;
};
struct Graph
{
	struct Edge E[MAXG];
	int cntE, head[MAXN];
	void init() { _Neg1(head); cntE = 0; }
	void addE(int a, int warrior, int c = 0) { E[cntE] = { a,warrior,c,head[a] }; head[a] = cntE++; }
};
struct Dijkstra : Graph//下面定一个变量就能用
{
	ll dist[MAXG];
	struct DNode
	{
		ll val;int id;
		bool operator< (const DNode &r)const
		{
			return val > r.val;
		}
	};
	void Init() { _Inf(dist); }
	void Get_Dist(int s)//重新计算从s开始的单源最短路
	{
		Init();
		priority_queue<DNode>pq;
		pq.push({ 0,s });
		dist[s] = 0;
		while (!pq.empty())
		{
			DNode tmp = pq.top(); pq.pop();
			if (tmp.val > dist[tmp.id])continue;
			for (int i = head[tmp.id]; i != -1; i = E[i].nxt)
			{
				if (dist[E[i].to] > dist[tmp.id] + E[i].cost)
				{
					dist[E[i].to] = dist[tmp.id] + E[i].cost;
					pq.push({ dist[E[i].to],E[i].to });
				}
			}
		}
	}
	int Get_Dist(int s, int t)//获取s到t的最短路
	{
		if(dist[t]==INF&&dist[s]!=0)Get_Dist(s);
		return dist[t];
	}
}Dij;
struct Dinic :Graph
{
	int curE[MAXG], s, t, dist[MAXG];
	ll dfs(int u, ll f)//不用管，不要调用
	{
		if (u == t)return f;
		int ans = 0;
		for (int &i = curE[u]; i != -1; i = E[i].nxt)
		{
			if (dist[E[i].to] == dist[u] + 1 && E[i].cost > 0)
			{
				ll tmp = dfs(E[i].to, min(f, (ll)E[i].cost));
				f -= tmp;
				E[i].cost -= tmp;
				ans += tmp;
				E[i ^ 1].cost += tmp;
				if (!f)break;
			}
		}
		if (!ans)dist[u] = -1;
		return ans;
	}
	bool bfs()//同上
	{
		_Neg1(dist);
		queue<int> q; q.push(s);
		dist[s] = 0;
		while (!q.empty())
		{
			int u = q.front(); q.pop();
			for (int i = head[u]; i != -1; i = E[i].nxt)
			{
				if (dist[E[i].to] == -1 && E[i].cost > 0)
				{
					dist[E[i].to] = dist[u] + 1;
					q.push(E[i].to);
				}
			}
		}
		return dist[t] != -1;
	}
	ll dinic(int x, int y, int num)//返回从x到y的最大流 要给出有n个点
	{
		s = x; t = y;
		int ans = 0;
		while (bfs())
		{
			for (int i = 1; i <= num; i++)curE[i] = head[i];
			ans += dfs(s, INF);
		}
		return ans;
	}
}Din;