#include <bits/stdc++.h>
using namespace std;
const int MAXSIZE = 100005;
struct Pir
{
    int x,y;
};
struct Zpt
{
    struct Node
    {
        int l,r,fa,dis,rt;
        Pir k;
    }node[MAXSIZE];
    int cmp(Pir x,Pir y)
    {
        if (x.x!=y.x) return (x.x<y.x) ? -1 : 1;
        if (x.y!=y.y) return (x.y<y.y) ? -1 : 1;
        return 0;
    }
    int findrt(int x)
    {
        if (x==node[x].rt) return x;
        return node[x].rt=findrt(node[x].rt);
    }
    void pushup(int now)
    {
        if (!now) return;
        int t=min(node[node[now].l].dis,node[node[now].r].dis)+1;
        if (node[now].dis!=t)
        {
            node[now].dis=t;
            pushup(node[now].fa);
        }
    }
    void ins(int x,int id)
    {
        node[id].l=node[id].r=node[id].fa=0;node[id].dis=1;node[id].rt=id;
        node[id].k.x=x;node[id].k.y=id;
    }
    int merge(int x,int y)
    {
        if (x==0 || y==0) return x+y;
        if (cmp(node[x].k,node[y].k)==1) swap(x,y);
        int r;
        if (node[node[x].l].dis<node[node[x].r].dis)
        {
            node[x].l=merge(node[x].l,y);
            node[node[x].l].fa=x;
        }
        else
        {
            node[x].r=merge(node[x].r,y);
            node[node[x].r].fa=x;
        }
        pushup(x);
        return x;
    }
    int del(int now)
    {
        node[node[now].l].fa=node[node[now].r].fa=0;
        int t=merge(node[now].l,node[now].r);
        node[node[now].l].rt=node[node[now].r].rt=node[now].rt=t;
        return t;
    }
}zpt;
int flag[MAXSIZE];
int n;
int main()
{
    int Q,op,x,y;
    cin>>n>>Q;
    for (int i=1,x;i<=n;++i)
    {
        scanf("%d",&x);
        flag[i]=1;
        zpt.ins(x,i);
    }
    while (Q--)
    {
        scanf("%d",&op);
        if (op==1)
        {
            scanf("%d%d",&x,&y);
            if (!flag[x] || !flag[y]) continue;
            x=zpt.findrt(x);y=zpt.findrt(y);
            if (x!=y)
            {
                zpt.node[x].rt=zpt.node[y].rt=zpt.merge(x,y);
            }
            continue;
        }
        if (op==2)
        {
            scanf("%d",&x);
            if (!flag[x]) {puts("-1");continue;}
            x=zpt.findrt(x);
            printf("%d\n",zpt.node[x].k.x);
            flag[x]=0;
            int t=zpt.del(x);
            continue;
        }
        assert(0);
    }
    return 0;
}
