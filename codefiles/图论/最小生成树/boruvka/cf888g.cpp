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
using std::queue;
using std::min;
using std::max;
using std::swap;
using std::string;
using std::sort;
using std::unique;
typedef long long ll;
const int inf = (1<<30)-5+(1<<30);
const int N = 200005;
#define pb push_back
#define RE register
struct Pir
{
    int x,y;
};
struct Trie
{
    struct Node
    {
        int v;
        int nxt[2];
    }node[3000005];
    int rt,sz;
    inline void init()
    {
        rt=sz=1;
        node[rt].v=0;
    }
    inline int extend(const int & p,const int & c)
    {
        if (node[p].nxt[c]) return node[p].nxt[c];
        int cur=++sz;
        node[cur].v=0;
        node[p].nxt[c]=cur;
        return cur;
    }
    int calc(int p1,int p2,int dep)
    {
        if (!p1 || !p2) return inf;
        if (dep<0) return 0;
        int res;
        if (node[p1].nxt[0] && node[p2].nxt[0] || node[p1].nxt[1] && node[p2].nxt[1]) res=min(calc(node[p1].nxt[0],node[p2].nxt[0],dep-1),calc(node[p1].nxt[1],node[p2].nxt[1],dep-1));
        else res=min(calc(node[p1].nxt[0],node[p2].nxt[1],dep-1),calc(node[p1].nxt[1],node[p2].nxt[0],dep-1))+(1<<dep);
        //cout<<"calc="<<p1<<' '<<p2<<' '<<dep<<' '<<res<<endl;
        return res;
    }
    ll dfs(int p,int dep)
    {
        if (!node[p].nxt[0] && !node[p].nxt[1]) return 0;
        int res=0;
        if (node[p].nxt[0] && node[p].nxt[1]) res=calc(node[p].nxt[0],node[p].nxt[1],dep-1)+(1<<dep);
        //cout<<"p="<<p<<' '<<dep<<' '<<res<<"        lrs="<<node[p].nxt[0]<<' '<<node[p].nxt[1]<<endl;
        return dfs(node[p].nxt[0],dep-1)+dfs(node[p].nxt[1],dep-1)+res;
    }
}tr;
int a[N];
int n;
int main()
{
    cin>>n;
    for (int i=1;i<=n;++i) scanf("%d",&a[i]);
    tr.init();
    for (int i=1;i<=n;++i)
    {
        for (int j=29,p=tr.rt;~j;--j)
        {
            p=tr.extend(p,(a[i]>>j)&1);
        }
    }
    ll ans=tr.dfs(tr.rt,29);
    cout<<ans<<endl;
    return 0;
}
