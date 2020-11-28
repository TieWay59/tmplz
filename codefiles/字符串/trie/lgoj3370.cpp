#include <bits/stdc++.h>
using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::set;
using std::map;
typedef long long ll;
typedef double db;
const int TOTLEN = 15000000;
struct Trie
{
    struct Node
    {
        int v,fa;
        map <int,int> nxt;
    };
    vector <Node> node;
    int rt,sz;
    void init()
    {
        node.clear();
        node.push_back((Node){0});
        node.push_back((Node){0});
        rt=sz=1;
        node[rt].v=node[rt].fa=0;
        node[rt].nxt.clear();
    }
    int extend(int p,int c)
    {
        if (node[p].nxt[c]) return node[p].nxt[c];
        node.push_back((Node){0});
        int cur=++sz;
        node[cur].v=0;
        node[cur].fa=p;
        node[cur].nxt.clear();
        node[p].nxt[c]=cur;
        return cur;
    }
}trie1;
char st[1505];
int main()
{
    trie1.init();
    int n,tot=0;
    cin>>n;
    while (n--)
    {
        scanf("%s",st);
        int len=strlen(st),p=trie1.rt;
        for (int i=0;i<len;++i)
        {
            p=trie1.extend(p,st[i]);
        }
        if (!trie1.node[p].v) ++tot;
        ++trie1.node[p].v;
    }
    cout<<tot<<endl;
    return 0;
}

