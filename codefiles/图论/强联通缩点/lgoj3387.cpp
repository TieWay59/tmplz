#include <bits/stdc++.h>
using namespace std;
const int N = 10005;
vector <int> adj[N];
stack <int> stk;
int dfn[N],low[N],index;
void tarjan(int x)
{
    dfn[x]=low[x]=++index;
    stk.push(x);
    for (auto y:adj[x])
    {
        if (!dfn[y])
        {
            tarjan(y);
            low[x]=min(low[x],low[y]);
        }else
        {
            //if (instk[y]) low[x]=min(low[x],dfn[y]);
        }
    }
    if (dfn[x]==low[x])
    {
        int u;
        do
        {
            u=stk.top();
            stk.pop();
        }while (u!=x);
    }
}
int n,m;
int main()
{
    cin>>n>>m;
    for (int i=1;i<=m;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        adj[x].push_back(y);
    }
    for (int i=1;i<=n;++i) if (!dfn[i]) tarjan(i);
    return 0;
}
