#include <bits/stdc++.h>
#define ll long long
namespace KM
{
    ///感谢yyb的模板,代码主体来自yyb的博客
    ///下标从1开始,MAX是两边的点数上限较大值,inf是无穷大
    ///调用km函数,直接把左边和右边点数,邻接表丢进去就行
    ///最大权是ans,匹配是x->pre[x]或者match[x]->x
    const ll inf = (1LL<<60);
    const int MAX = 505;
    ll n,nl,nr,m,a[MAX][MAX];
    ll slack[MAX],sl[MAX],sr[MAX],pre[MAX],match[MAX];
    bool vis[MAX];
    ll ans;
    void bfs(int S)
    {
        for (int i=0;i<=n;++i) slack[i]=inf;
        memset(vis,0,sizeof(vis));
        memset(pre,0,sizeof(pre));
        ll u=0,nt,d,nw;
        match[u]=S;
        while (match[u])
        {
            nw=match[u];d=slack[0];vis[u]=true;
            for(int v=1;v<=n;++v)
                if(!vis[v])
                {
                    if(sl[nw]+sr[v]-a[nw][v]<slack[v])
                        slack[v]=sl[nw]+sr[v]-a[nw][v],pre[v]=u;
                    if(d>slack[v])d=slack[v],nt=v;
                }
            for(int i=0;i<=n;++i)
                if(vis[i])sl[match[i]]-=d,sr[i]+=d;
                else slack[i]-=d;
            u=nt;
        }
        while(u)match[u]=match[pre[u]],u=pre[u];
    }
    void km(int nl_r,int nr_r,const ll a_r[MAX][MAX])
    {
        memset(a,0,sizeof(a));
        memset(sl,0,sizeof(sl));
        memset(sr,0,sizeof(sr));
        memset(match,0,sizeof(match));
        nl=nl_r;nr=nr_r;n=std::max(nl,nr);
        for(int u=1;u<=nl;++u)
        for (int v=1;v<=nr;++v)
        if (a_r[u][v])
        {
            a[u][v]=std::max(a[u][v],a_r[u][v]);
            sl[u]=std::max(sl[u],a[u][v]);
        }
        for(int i=1;i<=n;++i)bfs(i);
        for(int i=1;i<=n;++i)ans+=sl[i]+sr[i];
        memset(pre,0,sizeof(pre));
        for(int i=1;i<=n;++i)pre[match[i]]=i;
    }
    void print()
    {
        printf("KMans=%lld\n",ans);
        for (int i=1;i<=n;++i) printf("%lld ",match[i]);puts("");
        //for (int i=1;i<=n;++i) printf("%lld ",sl[i]);puts("");
        //for (int i=1;i<=n;++i) printf("%lld ",sr[i]);puts("");
    }
};
const int N = 505;
ll a[N][N];
int main()
{
    int nl,nr,m;
    std::cin>>nl>>nr>>m;
    for (int i=1;i<=m;++i)
    {
        int x,y,t;
        scanf("%d%d%d",&x,&y,&t);
        a[x][y]=t;
    }
    KM::km(nl,nr,a);
    //KM::print();
    std::cout<<KM::ans<<std::endl;
    for (int i=1;i<=nl;++i) printf("%d ",(KM::a[i][KM::pre[i]] ? KM::pre[i] : 0));puts("");
    return 0;
}
