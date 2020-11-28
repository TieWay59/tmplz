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
using std::min;
using std::max;
using std::swap;
using std::string;
typedef long long ll;
typedef double db;
const int MOD = 998244353;
const int N = 500005;
const ll inf = (1LL<<60);
#define pb push_back
ll power(const ll & x,const ll & mi)
{
    ll s1=1LL,s2=x,m=mi;
    while (m)
    {
        if (m&1) s1=s1*s2%MOD;
        s2=s2*s2%MOD;
        m>>=1;
    }
    return s1;
}
struct Pam
{
    struct Node
    {
        int c[26],fail,len,dep,cnt;
    }node[N];
    int node_cnt,last,rt;
    int st[N],n;
    int newnode()
    {
        int p=++node_cnt;
        memset(node[p].c,0,sizeof(node[p].c));
        node[p].fail=node[p].len=node[p].dep=node[p].cnt=0;
        return p;
    }
    void init()
    {
        memset(st,-1,sizeof(st));n=0;
        node_cnt=last=rt=0;
        rt=last=newnode();node[1].len=-1;node[1].fail=1;
        node[newnode()].fail=1;node[2].len=0;
        last=2;
    }
    void extend(int ch)
    {
        //cout<<"ch="<<ch<<endl;
        st[++n]=ch;
        int p=last;
        //cout<<"ok="<<st[n-1-node[1].len]<<' '<<node[1].len<<endl;
        while (st[n-1-node[p].len]!=ch) p=node[p].fail;
        //cout<<"p="<<p<<endl;
        if (!node[p].c[ch])
        {
            int np=newnode();
            //cout<<"np="<<np<<endl;
            if (p==1)
            {
                node[np].len=1;
                node[np].fail=2;
            }else
            {
                node[np].len=node[p].len+2;
                int k=node[p].fail;
                while (st[n-1-node[k].len]!=ch) k=node[k].fail;
                node[np].fail=node[k].c[ch];
            }
            node[p].c[ch]=np;
            node[np].dep=node[node[np].fail].dep+1;
        }
        last=node[p].c[ch];
        ++node[last].cnt;
    }
    ll calc_cnt()
    {
        ll res=0;
        for (int i=node_cnt;i>2;--i) node[node[i].fail].cnt+=node[i].cnt;
        for (int i=1;i<=node_cnt;++i)
        {
            res=max(1LL*node[i].len*node[i].cnt,res);
        }
        return res;
    }
}pam;
char st[N];
int n;
int main()
{
    pam.init();
    scanf("%s",st);n=strlen(st);
    for (int i=0,ans=0;i<n;)
    {
        //cout<<"i="<<i<<endl;
        pam.extend(st[i]-'a');
        ans=pam.node[pam.last].dep;
        //printf("%d ",ans);
        ++i;
        //st[i]=(st[i]-97+ans)%26+97;
    }
    //puts("");
    printf("%lld\n",pam.calc_cnt());
    return 0;
}
