#include <bits/stdc++.h>
using namespace std;
queue <int> q;
const int MAXLEN = 200005;
struct ACAM
{
    struct Node
    {
        int fail;
        int nxt[26];
    }node[MAXLEN];
    int rt,node_cnt;
    vector <int> adj[MAXLEN];
    void init()
    {
        for (int i=1;i<=node_cnt;++i)
        {
            memset(node[i].nxt,0,sizeof(node[i].nxt));
            adj[i].clear();
        }
        rt=node_cnt=1;
    }
    int extend(int p,int c)
    {
        if (node[p].nxt[c]) return node[p].nxt[c];
        int cur=++node_cnt;
        node[p].nxt[c]=cur;
        return cur;
    }
    int findc(int p,int c)
    {
        if (node[p].nxt[c]) return node[p].nxt[c];
        if (!p) return rt;
        return findc(node[p].fail,c);
    }
    void getfail()
    {
        while (!q.empty()) q.pop();
        q.push(rt);
        while (!q.empty())
        {
            int x=q.front();q.pop();
            for (int c=0;c<26;++c)
            {
                if (node[x].nxt[c])
                {
                    node[node[x].nxt[c]].fail=findc(node[x].fail,c);
                    q.push(node[x].nxt[c]);
                }else node[x].nxt[c]=findc(node[x].fail,c);
            }
        }
        for (int i=1;i<=node_cnt;++i) adj[node[i].fail].push_back(i);
    }
    void print()
    {
        cout<<"node_cnt="<<node_cnt<<' '<<"rt="<<rt<<endl;
        for (int i=1;i<=node_cnt;++i)
        {
            cout<<"nod["<<i<<"]="<<node[i].fail<<' '<<node[i].fail<<' '<<node[i].fail<<endl;
        }
    }
}ac1;
int dp[MAXLEN],a[MAXLEN],f[MAXLEN];
void dfs(int x)
{
    dp[x]=f[x];
    for (auto y:ac1.adj[x])
    {
        dfs(y);
        dp[x]+=dp[y];
    }
}
string st;
int main()
{
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    ac1.init();
    int m,n=0;
    cin>>m;
    while (m--)
    {
        cin>>st;
        int p=ac1.rt;
        for (int i=0;i<st.size();++i)
        {
            p=ac1.extend(p,st[i]-'a');
        }
        a[++n]=p;
    }
    ac1.getfail();
    cin>>st;
    int p=ac1.rt;
    for (int i=0;i<st.size();++i)
    {
        p=ac1.findc(p,st[i]-'a');
        ++f[p];
    }
    dfs(ac1.rt);
    for (int i=1;i<=n;++i) cout<<dp[a[i]]<<endl;
    return 0;
}
