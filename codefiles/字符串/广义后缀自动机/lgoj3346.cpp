///有一棵树,每个节点有字符,每条链可以组成字符串,问有多少种字符串
///正着走和反着走不一样,叶子只有20个
#include <bits/stdc++.h>
using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::set;
using std::map;
typedef long long ll;
typedef double db;
const int MAXLEN = 3000005;
int t[MAXLEN << 1];
struct Sam
{
    struct Node
    {
        int maxlen,link;
        int nxt[10];
    }node[MAXLEN << 1];
    int rl[MAXLEN << 1];
    int sz,rt;
    void init()
    {
        sz=0;
        ++sz;
        rt=sz;
        memset(node[sz].nxt,0,sizeof(node[sz].nxt));
        node[sz].maxlen=0;
        node[sz].link=0;
    }
    int extend(int last,int c)
    {
        if (node[last].nxt[c] && node[node[last].nxt[c]].maxlen==node[last].maxlen+1) return node[last].nxt[c];
        int cur=++sz,p=last,flag=0,q,clone;
        memset(node[cur].nxt,0,sizeof(node[cur].nxt));
        node[cur].maxlen=node[p].maxlen+1;
        for (;p && !node[p].nxt[c];p=node[p].link) node[p].nxt[c]=cur;
        if (!p) node[cur].link=rt;else
        {
            q=node[p].nxt[c];
            if ((node[p].maxlen+1)==node[q].maxlen) node[cur].link=q;else
            {
                if (p==last) clone=cur;else clone=++sz;
                node[clone].maxlen=node[p].maxlen+1;
                memcpy(node[clone].nxt,node[q].nxt,sizeof(node[clone].nxt));
                node[clone].link=node[q].link;
                for (;p && node[p].nxt[c]==q;p=node[p].link) node[p].nxt[c]=clone;
                node[q].link=clone;
                if (cur!=clone) node[cur].link=clone;
            }
        }
        return cur;
    }
    void build()
    {
        memset(t,0,sizeof(t));
        for (int i=1;i<=sz;++i) ++t[node[i].maxlen];
        for (int i=1;i<=sz;++i) t[i]+=t[i-1];
        for (int i=1;i<=sz;++i) rl[t[node[i].maxlen]--]=i;
    }
    void print()
    {
        for (int i=1;i<=sz;++i) cout<<node[i].maxlen<<' ';cout<<endl;
        for (int i=1;i<=sz;++i) cout<<node[i].link<<' ';cout<<endl;
        //for (int i=1;i<=sz;++i) cout<<cnt[i]<<' ';cout<<endl;
    }
}sam;
string st;
std::vector <int> adj[100005];
int c[MAXLEN],deg[MAXLEN];
void dfs(int x,int pre,int last)
{
    int cur=sam.extend(last,c[x]);
    for (auto y:adj[x])
    if (y!=pre)
    {
        dfs(y,x,cur);
    }
}
int main()
{
    sam.init();
    int n,m;
    cin>>n>>m;
    for (int i=1;i<=n;++i) scanf("%d",&c[i]);
    for (int i=1,x,y;i<n;++i)
    {
        scanf("%d%d",&x,&y);
        adj[x].push_back(y);
        adj[y].push_back(x);
        ++deg[x];++deg[y];
    }
    for (int i=1;i<=n;++i)
    if (deg[i]==1)
    {
        dfs(i,0,sam.rt);
    }
    //sam.build();
    ll tot=0;
    for (int i=1;i<=sam.sz;++i)
    {
        tot+=sam.node[i].maxlen-sam.node[sam.node[i].link].maxlen;
    }
    cout<<tot<<endl;
    return 0;
}



/*#include <bits/stdc++.h>
using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::set;
using std::map;
typedef long long ll;
typedef double db;
const int MAXLEN = 1000005;
int t[MAXLEN << 1];
struct Sam
{
    struct Node
    {
        int maxlen,link;
        std::map <int,int> nxt;
    }node[MAXLEN << 1];
    int cnt[MAXLEN << 1];
    int rl[MAXLEN << 1];
    int sz,rt;
    void init()
    {
        memset(cnt,0,sizeof(cnt));
        sz=0;
        ++sz;
        rt=sz;
        node[sz].nxt.clear();
        node[sz].maxlen=0;
        node[sz].link=0;
    }
    int extend(int last,int c)
    {
        if (node[last].nxt[c] && node[node[last].nxt[c]].maxlen==node[last].maxlen+1) {++cnt[node[last].nxt[c]];return node[last].nxt[c];}
        int cur=++sz,p=last,flag=0,q,clone;
        node[cur].nxt.clear();
        node[cur].maxlen=node[p].maxlen+1;
        for (;p && !node[p].nxt[c];p=node[p].link) node[p].nxt[c]=cur;
        if (!p) node[cur].link=rt;else
        {
            q=node[p].nxt[c];
            if ((node[p].maxlen+1)==node[q].maxlen) node[cur].link=q;else
            {
                if (p==last) clone=cur;else clone=++sz;
                node[clone].maxlen=node[p].maxlen+1;
                node[clone].nxt=node[q].nxt;
                node[clone].link=node[q].link;
                for (;p && node[p].nxt[c]==q;p=node[p].link) node[p].nxt[c]=clone;
                node[q].link=clone;
                if (cur!=clone) node[cur].link=clone;
            }
        }
        ++cnt[cur];
        return cur;
    }
    void build()
    {
        memset(t,0,sizeof(t));
        for (int i=1;i<=sz;++i) ++t[node[i].maxlen];
        for (int i=1;i<=sz;++i) t[i]+=t[i-1];
        for (int i=1;i<=sz;++i) rl[t[node[i].maxlen]--]=i;
        for (int i=sz;i;--i)
        {
            node[node[rl[i]].link].cnt+=node[rl[i]].cnt;
        }
    }
    void print()
    {
        for (int i=1;i<=sz;++i) cout<<node[i].maxlen<<' ';cout<<endl;
        for (int i=1;i<=sz;++i) cout<<node[i].link<<' ';cout<<endl;
        for (int i=1;i<=sz;++i) cout<<node[i].cnt<<' ';cout<<endl;
    }
}sam;
string st;
int main()
{
    sam.init();
    int n;
    cin>>n;
    while (n--)
    {
        int last=sam.rt;
        cin>>st;
        for (auto it = st.begin();it != st.end();++it)
        {
            last=sam.extend(last,(int)(*it));
        }
    }
    sam.build();
    ll tot=0;
    for (int i=1;i<=sam.sz;++i)
    {
        tot+=sam.node[i].maxlen-sam.node[sam.node[i].link].maxlen;
    }
    cout<<tot<<endl;
    return 0;
}
*/
