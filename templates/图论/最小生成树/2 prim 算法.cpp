
/*
prim 算法是进行加点，使用于稠密图，可以选择用堆或者不用
不用堆 O（V*V);
用堆   O(E * log(V));
https://vjudge.net/problem/HDU-1863
*/


typedef pair<int,int> P;
const int LEN = 2e6+100;
int Away[LEN];//记录从当前已选结点到j节点的路径的最小值
bool  vis[LEN];
int N,M;//N 道路数目, M村庄个数
vector<vector<P> > vec(LEN);
int main()
{
        cin>>M>>N;

        int from,to,weight;
        while(N--)
        {
            scanf("%d %d %d",&from,&to,&weight);
            vec[from].push_back(P(weight,to));
            vec[to].push_back(P(weight,from));
        }// 添加边
        
        
        for(int i = 2; i <= M; ++i)
            Away[i] = INF;//初始化Away数组
        Away[1] = 0;
        int Left = M;
        int All_cost = 0;
        priority_queue<P,vector<P>,greater<P> > q;// 小顶堆
        q.push(P(0,1));
        while(!q.empty()&&Left>0)
        {
            P tmp = q.top();q.pop();
            int To = tmp.second;
            if(vis[To])
                continue;
            vis[To] = 1;
            Left--;
            All_cost += tmp.first;
            for(int  i = 0; i < vec[To].size(); ++i)// 更新Away 数组
            {
                P &t = vec[To][i];
                if(!vis[t.second] && Away[t.second] > t.first)
                { 
                    Away[t.second] = t.first;
                    q.push(t);
                }
            }
        }
        
            cout<<All_cost<<endl;
      
   

    return 0;
}
