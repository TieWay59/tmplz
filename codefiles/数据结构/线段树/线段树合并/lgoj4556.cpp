#include <bits/stdc++.h>
using std::cin;
using std::cout;
using std::endl;
using std::set;
using std::map;
using std::min;
using std::max;
using std::vector;
using std::deque;
using std::min;
using std::max;
using std::swap;
typedef long long ll;
typedef double db;
const int MAXNODE = 100005;
int tr_dep[MAXNODE],tr_fa[MAXNODE],tr_sz[MAXNODE];
vector <int> adj[MAXNODE];
int n,m;
void tree_build(int x,int pre)
{
    tr_dep[x]=tr_dep[pre]+1;
    tr_fa[x]=pre;
    tr_sz[x]=1;
    for (auto y:adj[x])
    if (y!=pre)
    {
        tree_build(y,x);
        tr_sz[x]+=tr_sz[y];
    }
}
int main()
{
    cin>>n>>m;
    for (int i=1,x,y;i<n;++i)
    {
        scanf("%d%d",&x,&y);
        adj[x].push_back(y);
        adj[y].push_back(x);
    }
    tree_build(1,0);
    return 0;
}
/*
sample input
5 3
1 2
3 1
3 4
5 3
2 3 3
1 5 2
3 3 3

sample output
2
3
3
0
2

n个点的树,m次在链上加一个数x,求加完后每个点上最多的数是什么
就是求众数
1<=n,m<=10w,1<=x<=10w
*/
