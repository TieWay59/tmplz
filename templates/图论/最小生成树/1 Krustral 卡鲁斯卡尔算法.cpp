/*
复杂度 E*log(E),适用于稀疏图
https://vjudge.net/problem/HDU-1863
*/


#include<bits/stdc++.h>

using namespace std;

const int maxn = 100+100;
struct Edge//边
{
    int from,to,cost;
    bool operator< ( const Edge & a)
    {
        return cost < a.cost;
    }
};
Edge edge[maxn];
int F[maxn];
int Find(int x)//并查集算法
{
    return x == F[x] ? x:F[x] = Find(F[x]);
}
int main(void)
{
    int N,M;
    while(cin>>N>>M&&N)// N代表的是道路数量，M代表村庄的数量
    {
        for(int i = 0; i <= M; ++i)
            F[i] = i;
        for(int i = 0; i <  N; ++i)
        {
             Edge &t = edge[i];
            scanf("%d %d %d",&t.from,&t.to,&t.cost);
        }
        sort(edge,edge+N);// 对边进行排序
        int sum = 0;
        int num = M;
        for(int i = 0;i < N ; ++i)// 一个个将边加进去
        {
            Edge t = edge[i];
            if(Find(t.from) == Find(t.to))
                continue;
            F[Find(t.from)] = F[Find(t.to)];
            sum += t.cost;
            num--;
        }
        if(num == 1)
            cout<<sum<<endl;
        else
            cout<<"?"<<endl;
    }


    return 0;
}
