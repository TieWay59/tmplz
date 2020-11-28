#include <bits/stdc++.h>
using namespace std;
int n;
struct Directed_Graph
{
    int v_n,e_n;
    int head[1005];
    struct Edge
    {
        int st,ed,nxt;
    }e[250005];
    void init()
    {
        v_n=e_n=0;
        memset(head,0,sizeof(head));
    }
    void addedge(int u,int v)
    {
        ++e_n;
        e[e_n].st=u;
        e[e_n].ed=v;
        e[e_n].nxt=head[u];
        head[u]=e_n;
    }
    int flag[1005],match[1005];
    int augment(int x)
    {
        if (x==0) return 1;
        for (int i=head[x];i;i=e[i].nxt)
        if (!flag[e[i].ed])
        {
            int y=e[i].ed;
            flag[y]=1;
            if (!augment(match[y])) continue;
            match[y]=x;
            return 1;
        }
        return 0;
    }
    int getmatch()
    {
        memset(match,0,sizeof(match));
        int match_tot=0;
        for (int i=1;i<=n;++i)
        {
            memset(flag,0,sizeof(flag));
            match_tot+=augment(i);
        }
        return match_tot;
    }
}g1;
int main()
{
    g1.init();
    int m,edgenum;
    cin>>n>>m>>edgenum;
    g1.v_n=n+m;
    for (int i=1;i<=edgenum;++i)
    {
        int u,v;
        scanf("%d%d",&u,&v);
        g1.addedge(u,v+n);
    }
    cout<<g1.getmatch()<<endl;
    return 0;
}
