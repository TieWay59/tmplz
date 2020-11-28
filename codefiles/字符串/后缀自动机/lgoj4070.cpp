#include <bits/stdc++.h>
using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::set;
using std::map;
typedef long long ll;
typedef double db;
const int MAXLEN = 100005;
int t[MAXLEN << 1];
ll tot;
int n;
struct Sam
{
    struct Node
    {
        int maxlen,link,cnt;
        std::map <int,int> nxt;
    }node[MAXLEN << 1];
    int rl[MAXLEN << 1];
    int sz,last,rt;
    void init()
    {
        sz=0;
        ++sz;
        rt=last=sz;
        node[sz].nxt.clear();
        node[sz].maxlen=0;
        node[sz].link=0;
        node[sz].cnt=0;
    }
    void extend(int c)
    {
        int cur=++sz,p=last;last=cur;
        node[cur].nxt.clear();
        node[cur].cnt=1;
        node[cur].maxlen=node[p].maxlen+1;
        for (;p && !node[p].nxt[c];p=node[p].link) node[p].nxt[c]=cur;
        if (!p) node[cur].link=rt;else
        {
            int q=node[p].nxt[c];
            if ((node[p].maxlen+1)==node[q].maxlen) node[cur].link=q;else
            {
                int clone=++sz;
                node[clone].maxlen=node[p].maxlen+1;
                node[clone].nxt=node[q].nxt;
                node[clone].link=node[q].link;
                node[clone].cnt=0;
                for (;p && node[p].nxt[c]==q;p=node[p].link) node[p].nxt[c]=clone;
                node[q].link=node[cur].link=clone;
            }
        }
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
    cin>>n;
    sam.init();
    tot=0LL;
    for (int i=1;i<=n;++i)
    {
        int x;
        scanf("%d",&x);
        sam.extend(x);
        tot+=sam.node[sam.last].maxlen-sam.node[sam.node[sam.last].link].maxlen;
        printf("%lld\n",tot);
    }
    sam.build();
    return 0;
}
