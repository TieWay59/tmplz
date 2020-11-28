#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXSIZE = 1500005;
const int N = 300005;
inline int myrand() {return rand()<<15|rand();}
struct FTreap
{
    struct Node
    {
        ll k;
        int l,r,w,sz,rnd;
    }node[MAXSIZE];
    int trash[MAXSIZE],trashcnt;
    int rt[N],nodecnt;
    void init(int n)
    {
        for (int i=0;i<=n;++i) rt[i]=0;
        nodecnt=trashcnt=0;
    }
    inline void update(int now)
    {
        int ls=node[now].l,rs=node[now].r;
        node[now].sz=node[ls].sz+node[rs].sz+node[now].w;
    }
    inline void pushdown(int now)
    {
        ;
    }
    inline int newnode(const Node t)
    {
        int now;
        if (trashcnt) now=trash[trashcnt--];else now=++nodecnt;
        node[now]=t;node[now].rnd=myrand();
        return now;
    }
    void splitnode(int now,int s,int &x,int &y)
    {
        if (s<=0) {y=now;return;}
        if (s>=node[now].w) {x=now;return;}
        int clone=newnode(node[now]);
        x=now;y=clone;
        node[y].k=node[x].k+s;
        node[y].w=node[x].w-s;
        node[x].w=s;
        update(x);update(y);
    }
    int mergeab(const int a,const int b)
    {
        if ((!a) || (!b)) return a+b;
        if (node[a].rnd<node[b].rnd)
        {
            pushdown(a);
            node[a].r=mergeab(node[a].r,b);
            update(a);
            return a;
        }else
        {
            pushdown(b);
            node[b].l=mergeab(a,node[b].l);
            update(b);
            return b;
        }
    }
    void split_s(int now,int s,int &x,int &y)
    {
        if (!now) {x=y=0;return;}
        pushdown(now);
        if (s<=node[node[now].l].sz)
        {
            y=now;
            split_s(node[now].l,s,x,node[now].l);
        }else
        if (s>=node[node[now].l].sz+node[now].w)
        {
            x=now;
            split_s(node[now].r,s-node[node[now].l].sz-node[now].w,node[now].r,y);
        }else
        {
            int sz=node[node[now].l].sz,rt1,rt2,rt3,t1,t2;
            split_s(now,sz+node[now].w,rt1,rt3);
            split_s(now,sz,rt1,rt2);
            splitnode(rt2,s-sz,t1,t2);
            x=mergeab(rt1,t1);y=mergeab(t2,rt3);
            /**
            ///y o u h u a
            int rt1=node[now].l,rt2=now,rt3=node[now].r,t1,t2;
            node[now].l=node[now].r=0;update(now);
            splitnode(rt2,s-node[rt1].sz,t1,t2);
            x=mergeab(rt1,t1);y=mergeab(t2,rt3);
            **/
        }
        update(now);
    }
    inline void delnode(int x)
    {
        trash[++trashcnt]=x;
    }
}tr;
int n,m;
int main()
{
    int Q;
    srand(19260817);
    cin>>n>>m>>Q;
    tr.init(n);
    for (int i=1;i<=n;++i) tr.rt[0]=tr.mergeab(tr.rt[0],tr.newnode({1LL*i*m,0,0,1,1,myrand()}));
    for (int i=1;i<=n;++i) tr.rt[i]=tr.newnode({1LL*(i-1)*m+1,0,0,m-1,m-1,myrand()});
    for (int cas=1,x,y;cas<=Q;++cas)
    {
        int rt1,rt2,rt3,rt4,rt5,rt6;
        //printf("Case %d : \n",cas);
        scanf("%d%d",&x,&y);
        if (y==m)
        {
            tr.split_s(tr.rt[0],x,rt1,rt3);
            tr.split_s(rt1,x-1,rt1,rt2);
            printf("%lld\n",tr.node[rt2].k);
            tr.rt[0]=tr.mergeab(tr.mergeab(rt1,rt3),rt2);
            continue;
        }
        tr.split_s(tr.rt[0],x,rt1,rt3);
        tr.split_s(rt1,x-1,rt1,rt2);
        tr.split_s(tr.rt[x],y,rt4,rt6);
        tr.split_s(rt4,y-1,rt4,rt5);
        //cout<<"rt="<<rt1<<' '<<rt2<<' '<<rt3<<' '<<rt4<<' '<<rt5<<' '<<rt6<<endl;
        printf("%lld\n",tr.node[rt5].k);
        tr.rt[x]=tr.mergeab(tr.mergeab(rt4,rt6),rt2);
        tr.rt[0]=tr.mergeab(tr.mergeab(rt1,rt3),rt5);
    }
    return 0;
}
