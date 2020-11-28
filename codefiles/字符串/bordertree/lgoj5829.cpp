///qiu chuan de liang ge qian zhui de zui chang gong gong border
#include <bits/stdc++.h>
using namespace std;
#define pb push_back
const int MAXLEN = 1000005;
struct Border_Tree
{
    int st[MAXLEN],border[MAXLEN];
    int dep[MAXLEN],fa[MAXLEN][21];
    int len;
    vector <int> adj[MAXLEN];
    void init(const string & st1)
    {
        len=st1.size();
        for (int i=1;i<=len;++i) st[i]=st1[i-1]-'a'+1;
        st[0]=st[len+1]=0;
    }
    void print()
    {
        cout<<"len="<<len<<endl;
        for (int i=1;i<=len;++i) cout<<border[i]<<' ';cout<<endl;
    }
    void Bdt_Prepare(int u,int pre)
    {
        dep[u]=dep[pre]+1;fa[u][0]=pre;
        for (auto v:adj[u])
            Bdt_Prepare(v,u);
    }
    void getbdt()
    {
        st[0]=st[len+1]=0;
        border[0]=border[1]=0;
        for (int i=2;i<=len;++i)
        {
            int u=border[i-1];
            while (st[u+1]!=st[i] && u) u=border[u];
            if (st[u+1]==st[i]) border[i]=u+1;else border[i]=0;
        }
        for (int i=0;i<=len;++i) adj[i].clear();
        for (int i=1;i<=len;++i) adj[border[i]].pb(i);
        dep[0]=0;
        Bdt_Prepare(0,0);
        for (int i=1;i<=20;++i) for (int j=1;j<=len;++j) fa[j][i]=fa[fa[j][i-1]][i-1];
    }
    int getlca(int x,int y)
    {
        if (dep[x]<dep[y]) swap(x,y);
        for (int i=20;i>=0;--i) if (dep[fa[x][i]]>=dep[y]) x=fa[x][i];
        if (x==y) return x;
        for (int i=20;i>=0;--i) if (fa[x][i]!=fa[y][i]) x=fa[x][i],y=fa[y][i];
        return fa[x][0];
    }
}bdt;
string st;
int main()
{
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int T,x,y;
    cin>>st;
    bdt.init(st);
    //bdt.len=st.size();for (int i=1;i<=bdt.len;++i) bdt.st[i]=st[i-1]-'a'+1;
    bdt.getbdt();
    //bdt.print();
    cin>>T;
    while (T--)
    {
        cin>>x>>y;
        cout<<bdt.getlca(bdt.border[x],bdt.border[y])<<endl;
    }
    return 0;
}
