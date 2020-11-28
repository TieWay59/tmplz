///给定两个字符串，求出在两个字符串中各取出一个子串使得这两个子串相同的方案数。两个方案不同当且仅当这两个子串中有一个位置不同。
#include <bits/stdc++.h>
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
        int nxt[27];
    }node[MAXLEN << 1];
    int cnt[MAXLEN << 1][3];
    int rl[MAXLEN << 1];
    int sz,rt;
    void init()
    {
        memset(cnt,0,sizeof(cnt));
        sz=0;
        ++sz;
        rt=sz;
        memset(node[sz].nxt,0,sizeof(node[sz].nxt));
        node[sz].maxlen=0;
        node[sz].link=0;
    }
    int extend(int last,int c,int id)
    {
        if (node[last].nxt[c] && node[node[last].nxt[c]].maxlen==node[last].maxlen+1) {++cnt[node[last].nxt[c]][id];return node[last].nxt[c];}
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
        ++cnt[cur][id];
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
            for (int j=1;j<=2;++j) cnt[node[rl[i]].link][j]+=cnt[rl[i]][j];
        }
    }
    void print()
    {
        for (int i=1;i<=sz;++i) cout<<node[i].maxlen<<' ';cout<<endl;
        for (int i=1;i<=sz;++i) cout<<node[i].link<<' ';cout<<endl;
        for (int i=1;i<=sz;++i) cout<<cnt[i][1]<<' ';cout<<endl;
    }
}sam;
string st;
int main()
{
    sam.init();
    int n;
    n=2;
    for (int id=1;id<=2;++id)
    {
        int last=sam.rt;
        cin>>st;
        for (auto it = st.begin();it != st.end();++it)
        {
            last=sam.extend(last,(int)(*it)-'a'+1,id);
        }
    }
    sam.build();
    ll tot=0;
    for (int i=1;i<=sam.sz;++i)
    {
        tot+=1LL*(sam.node[i].maxlen-sam.node[sam.node[i].link].maxlen)*sam.cnt[i][1]*sam.cnt[i][2];
    }
    cout<<tot<<endl;
    return 0;
}
