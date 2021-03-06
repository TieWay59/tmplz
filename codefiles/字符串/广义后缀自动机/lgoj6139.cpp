///给定 n 个由小写字母组成的字符串，求本质不同的子串个数。（不包含空串）
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
            last=sam.extend(last,(int)(*it)-'a'+1);
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
