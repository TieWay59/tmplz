///bit / segment tree
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define pb push_back
const int N = 100005;
inline int lowbit(int x) {return x&-x;}
struct Segt
{
    struct Node
    {
        int l,r,sz;
    }node[N*30*20*2];
    int rt[N];
    int nodecnt,trash[N*30*20*2],trashcnt;
    void init(int n)
    {
        nodecnt=trashcnt=0;
        for (int i=1;i<=n;++i) rt[i]=0;
    }
    inline int newnode()
    {
        int cur;
        if (trashcnt) cur=trash[trashcnt--];else cur=++nodecnt;
        node[cur].l=node[cur].r=node[cur].sz=0;
        return cur;
    }
    void ins(int & now,int l,int r,int x,int t)
    {
        if (!now) now=newnode();
        node[now].sz+=t;
        if (l==r) return;
        int mid=(l+r)>>1;
        if (x<=mid) ins(node[now].l,l,mid,x,t);
        else ins(node[now].r,mid+1,r,x,t);
    }
}segt;
void bit_extract(int x,vector <int> & vc)
{
    vc.clear();
    for (int i=x;i;i^=lowbit(i)) vc.pb(segt.rt[i]);
}
vector <int> vcadd,vcdel;
int a[N];
int n,m;
int main()
{
    cin>>n>>m;
    segt.init(n);
    for (int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
        for (int j=i;j<=n;j+=lowbit(j)) segt.ins(segt.rt[j],0,1000000000,a[i],1);
    }
    for (int cas=1;cas<=m;++cas)
    {
        char op[5];
        int x,y,k;
        scanf("%s%d%d",op,&x,&y);
        if (op[0]=='Q')
        {
            scanf("%d",&k);
            bit_extract(x-1,vcdel);
            bit_extract(y,vcadd);
            int l=0,r=1000000000;
            while (l<r)
            {
                int mid=(l+r)>>1,sum=0;
                for (auto i:vcadd) sum+=segt.node[segt.node[i].l].sz;
                for (auto i:vcdel) sum-=segt.node[segt.node[i].l].sz;
                if (k<=sum)
                {
                    r=mid;
                    for (int i=0;i<vcadd.size();++i) vcadd[i]=segt.node[vcadd[i]].l;
                    for (int i=0;i<vcdel.size();++i) vcdel[i]=segt.node[vcdel[i]].l;
                }
                else
                {
                    l=mid+1;k-=sum;
                    for (int i=0;i<vcadd.size();++i) vcadd[i]=segt.node[vcadd[i]].r;
                    for (int i=0;i<vcdel.size();++i) vcdel[i]=segt.node[vcdel[i]].r;
                }
            }
            printf("%d\n",l);
            continue;
        }
        if (op[0]=='C')
        {
            for (int j=x;j<=n;j+=lowbit(j)) segt.ins(segt.rt[j],0,1000000000,a[x],-1);
            a[x]=y;
            for (int j=x;j<=n;j+=lowbit(j)) segt.ins(segt.rt[j],0,1000000000,a[x],+1);
            continue;
        }
        assert(0);
    }
    return 0;
}
