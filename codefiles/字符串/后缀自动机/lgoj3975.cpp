///�����ĳ���Ϊ n ���ַ���,������ĵ� k С�Ӵ���ʲô

///���� t  k,t Ϊ 0 ���ʾ��ͬλ�õ���ͬ�Ӵ�����һ����t Ϊ 1 ���ʾ��ͬλ�õ���ͬ�Ӵ��������

///������ݽ���һ��,������һ���ַ���,Ϊ�� k С���Ӵ� ���Ӵ���Ŀ����k��,����� -1

#include <bits/stdc++.h>
using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::set;
using std::map;
typedef long long ll;
typedef double db;
const int MAXLEN = 500005;
ll dp[MAXLEN << 1];
int t[MAXLEN << 1];
int TYPE,K;
struct Sam
{
    struct Node
    {
        int maxlen,link,cnt;
        int nxt[27];
    }node[MAXLEN << 1];
    int rl[MAXLEN << 1];
    int sz,last,rt;
    void init()
    {
        sz=0;
        ++sz;
        rt=last=sz;
        memset(node[sz].nxt,0,sizeof(node[sz].nxt));
        node[sz].maxlen=0;
        node[sz].link=0;
        node[sz].cnt=0;
    }
    void extend(int c)
    {
        int cur=++sz,p=last;last=cur;
        memset(node[cur].nxt,0,sizeof(node[cur].nxt));
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
                memcpy(node[clone].nxt,node[q].nxt,sizeof(node[clone].nxt));
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
            int u=rl[i];
            node[node[rl[i]].link].cnt+=node[rl[i]].cnt;
            if (u==rt) dp[u]=0;else dp[u]=(TYPE) ? node[u].cnt : 1;
            for (int c=1;c<=26;++c)
            if (node[u].nxt[c])
            {
                dp[u]+=dp[node[u].nxt[c]];
            }
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
    memset(dp,0,sizeof(dp));
    cin>>st>>TYPE>>K;
    sam.init();
    for (auto it = st.begin();it != st.end();++it)
    {
        sam.extend((int)(*it)-'a'+1);
    }
    sam.build();
    //cout<<dp[sam.rt]<<endl;
    st="";
    for (int p=sam.rt;K>0;)
    {
        ll tot=0,c;
        for (c=1;c<=26;++c)
        {
            if (!sam.node[p].nxt[c]) continue;
            if (K<=dp[sam.node[p].nxt[c]]) break;
            K-=dp[sam.node[p].nxt[c]];
        }
        if (c>26) {puts("-1");return 0;}
        st+=(char)c+'a'-1;
        p=sam.node[p].nxt[c];
        K-=(TYPE) ? sam.node[p].cnt : 1;
        //cout<<st<<' '<<K<<endl;
    }
    cout<<st<<endl;
    return 0;
}
