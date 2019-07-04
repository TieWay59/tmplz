// 限制某一点的度数不能超过K
#include<cstring>
#include<map>
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<set>
using namespace std;
#define me(ar) memset(ar,0,sizeof(ar))
const  int    INF = 1e8;
//......................................................
const  int LEN = 30;
int K;
int n,m;
struct Edge
{
    int x,y;
    int weight;
    bool operator <(const Edge &a) const 
    {
        return weight < a.weight;
    }
} edge[LEN*LEN+10];//邻接表存边,Kruskal 算法要用
int dis[LEN][LEN];//邻接矩阵
int sign[LEN][LEN];//记录那些边已经在生成树里面了
int vis[LEN];//记录是否相连
int F[LEN];//并查集所用
int Father[LEN];//由i到i+1度限制生成树需要用动态规划求解,用来状态转移
int Best[LEN];//Best[i] 指的是由当前节点到park这些边中最长边是多少
int Find(int x)//并查集所用Find函数
{
    return x == F[x]?x:F[x] = Find(F[x]);
}
void  Dfs(int x)//Dfs动态规划记忆化搜索
{
//    vis[x] = 1;
    for(int i = 1;i <= n; ++i )
    {
        if(sign[i][x]&!vis[i])//如果有边相连并且下一个节点没有被访问
        {
            if(x==0)
            	Best[i] = -INF;//与park 直接相连的边不能删除
            
            else
              	Best[i] = max(Best[x],dis[x][i]);//状态转移方程            
            Father[i] = x;
            vis[i] = 1;
            Dfs(i);
        }
    }
}
void init(){
	  for(int i = 0;i < LEN; ++i)
            F[i] = i;
        me(sign);//初始化标记数组
        me(vis);
        //初始化邻接矩阵
        for(int i = 0;i < LEN; ++i)
            for(int j = 0;j < LEN; ++j)
             dis[i][j] = INF;
}
int main(void)
{
    while(cin>>m)
    {
        //初始化并查集数组
        init();
        n = 0;//用来记录共有多少个节点
        // set<string> se;
        map<string,int> ma;//将地点编号
        ma["Park"] = 0;//将park 加入节点
        string s1,s2;
        int a,b;
        int weight = 0;
        for(int i = 0; i < m; ++i)
        {
            cin>>s1>>s2>>weight;
            if(s1 == "Park"||ma[s1] != 0)
                a = ma[s1];//如果节点已编号,则直接使用
            else
                a = ma[s1] = ++n;//如果没有编号,编号
            if(s2 =="Park"||ma[s2]!=0)
                b = ma[s2];
            else
                b = ma[s2] = ++n;
            dis[a][b] = dis[b][a] = weight;
            edge[i].x = a;
            edge[i].y = b;
            edge[i].weight = weight;
        }
        //求最小生成树
        int ans = 0;//kruskal 算法求最小生成树
        sort(edge,edge+m);
        for(int i = 0;i < m; ++i)
        {
            int x = edge[i].x;
            int y = edge[i].y;
             weight = edge[i].weight;
            if(x==0||y==0)//去除掉park这个点
                continue;
            int xx = Find(x);
            int yy = Find(y);
            if(xx!=yy)
            {
                F[xx] = F[yy];
                ans += weight;
                sign[x][y] = sign[y][x] = 1;
            }
        }


        cin>>K;//最小k度生成树
        int Min[LEN];//用来记录每一个最小生成树到park点的最小路径
        for(int i = 0;i < LEN; ++i)
            Min[i] = INF;//初始化
        int index[LEN];//用来记录最小路径的点
        for(int i = 1;i <= n; ++i)
        {
            if(dis[i][0]<Min[Find(i)])
            {
                Min[Find(i)] = dis[i][0];
                index[Find(i)] = i;
            }
        }
////        cout<<se.size()<<endl;
        int m = 0;//用来记录除去park点即0点之后共有多少个连通分量
        for(int i = 1;i <= n; ++i)
        {
            if(Min[i] != INF)
            {
                ans += Min[i];
                sign[index[i]][0] = sign[0][index[i]] = 1;//将这个最小路径的点与park相连
                m++;
            }
        }
        int MMin = ans;
        for(int i = m + 1; i <= K; ++i)//从m+1到K求最小i度生成树
        {
            me(vis);
            vis[0] = 1;
            Dfs(0);
            int select = -1;//select用来记录选择哪个与park点相连是最小的
            int sum = INF;
            for(int i = 1;i <= n; ++i)
            {
                if(!sign[0][i] && dis[0][i] != INF)
                {
                    if(dis[i][0]-Best[i]<sum)
                    {
                        select  = i;
                        sum = dis[i][0]-Best[i];
                    }
                }
            }
            if(select == -1)//如果找不到,就跳出循环
                break;
            ans += sum;
            sign[select][0] = sign[0][select] = 1;
            MMin = min(MMin,ans);
            for(int i = select; i != 0; i = Father[i])
            {
                if(dis[Father[i]][i]==Best[select])
                {
                    sign[i][Father[i]] = sign[Father[i]][i] = 0;
                    break;
                }
            }
            cout<<ans<<endl;

        }
        printf("Total miles driven: %d\n",MMin);
       // cout<<MMin<<endl;
    }
    return 0;
}

