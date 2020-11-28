///如果一个 01 串长度不少于 L 且在 标准作文库 中的某个串里出现过（即，它是 标准作文库 的 某个串 的一个 连续子串 ），那么它是“ 熟悉 ”的。
///对于一篇作文（一个 01 串）A，如果能够把 A 分割成若干段子串，其中“ 熟悉 ” 的子串的 长度 总 和 不少于 A 总 长度的 90%，那么称 A 是 “ 熟悉的文章 ”。
///L 0 是 能够让 A 成为 “ 熟悉的文章 ” 的 所有 L 的最大值 （如果不存在这样的 L，那么规定 L 0 =0）。
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
        int nxt[2];
    }node[MAXLEN << 1];
    //int rl[MAXLEN << 1];
    int sz,rt;
    void init()
    {
        memset(node,0,sizeof(node));
        sz=0;
        ++sz;
        rt=sz;
        node[sz].maxlen=0;
        node[sz].link=0;
    }
    int extend(int last,int c)
    {
        if (node[last].nxt[c] && node[node[last].nxt[c]].maxlen==node[last].maxlen+1) return node[last].nxt[c];
        int cur=++sz,p=last,flag=0,q,clone;
        node[cur].maxlen=node[p].maxlen+1;
        for (;p && !node[p].nxt[c];p=node[p].link) node[p].nxt[c]=cur;
        if (!p) node[cur].link=rt;else
        {
            q=node[p].nxt[c];
            if ((node[p].maxlen+1)==node[q].maxlen) node[cur].link=q;else
            {
                if (p==last) clone=cur;else clone=++sz;
                node[clone].maxlen=node[p].maxlen+1;
                node[clone].nxt[0]=node[q].nxt[0];node[clone].nxt[1]=node[q].nxt[1];//memcpy(node[clone].nxt,node[q].nxt,sizeof(node[clone].nxt));
                node[clone].link=node[q].link;
                for (;p && node[p].nxt[c]==q;p=node[p].link) node[p].nxt[c]=clone;
                node[q].link=clone;
                if (cur!=clone) node[cur].link=clone;
            }
        }
        return cur;
    }
    /*void build()
    {
        memset(t,0,sizeof(t));
        for (int i=1;i<=sz;++i) ++t[node[i].maxlen];
        for (int i=1;i<=sz;++i) t[i]+=t[i-1];
        for (int i=1;i<=sz;++i) rl[t[node[i].maxlen]--]=i;
    }*/
    void print()
    {
        for (int i=1;i<=sz;++i) cout<<node[i].maxlen<<' ';cout<<endl;
        for (int i=1;i<=sz;++i) cout<<node[i].link<<' ';cout<<endl;
        //for (int i=1;i<=sz;++i) cout<<cnt[i]<<' ';cout<<endl;
    }
}sam;
std::deque <int> deq;
char st[1500005];
int dp[MAXLEN];
int len;
int check(int L)
{
    dp[0]=0;
    int n=len;
    deq.clear();
    int last=sam.rt,mxl=0,c;
    for (int i=1;i<=n;++i)
    {
        dp[i]=dp[i-1]-1;
        c=st[i-1]-'0';
        if (sam.node[last].nxt[c]) {last=sam.node[last].nxt[c];++mxl;}
        else{
            while (last && !sam.node[last].nxt[c]) last=sam.node[last].link;
            if (!last) last=sam.rt,mxl=0;else mxl=sam.node[last].maxlen+1,last=sam.node[last].nxt[c];
        }
        if (i-L>=0) {while (!deq.empty() && dp[i-L]>=dp[deq.back()]) deq.pop_back();deq.push_back(i-L);}
        while (!deq.empty() && deq.front()<i-mxl) deq.pop_front();
        if (!deq.empty()) dp[i]=std::max(dp[i],dp[deq.front()]);
        //for (int j=i-mxl;j<=i-L;++j) dp[i]=std::max(dp[i],dp[j]);
        //cout<<"i="<<i<<' '<<last<<' '<<mxl<<endl;
    }
    //cout<<"L="<<L<<endl;for (int i=1;i<=n;++i) cout<<dp[i]+i<<' ';cout<<endl;
    return dp[n]*10+n>=0;
}
int main()
{
    sam.init();
    int n,m;
    cin>>n>>m;
    while (m--)
    {
        int last=sam.rt;
        scanf("%s",st);
        len=strlen(st);
        for (int i = 0;i < len;++i)
        {
            last=sam.extend(last,st[i]-'0');
        }
    }
    //sam.build();
    while (n--)
    {
        scanf("%s",st);
        len=strlen(st);
        int l=0,r=len;
        while (l<r)
        {
            int mid=(l+r+1)>>1;
            if (check(mid)) l=mid;else r=mid-1;
        }
        printf("%d\n",l);
    }
    return 0;
}

