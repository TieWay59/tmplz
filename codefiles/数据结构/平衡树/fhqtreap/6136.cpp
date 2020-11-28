#include <bits/stdc++.h>
using namespace std;
const int MAXSIZE = 1111111;
struct FTreap
{
    struct Node
    {
        int k,l,r,w,sz,rnd;
    }node[MAXSIZE];
    int trash[MAXSIZE],trashcnt;
    int rt,nodecnt;
    void init()
    {
        rt=nodecnt=trashcnt=0;
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
    void split_k(int now,int k,int &x,int &y)
    {
        if (!now) {x=y=0;return;}
        pushdown(now);
        if (node[now].k<=k)
        {
            x=now;
            split_k(node[now].r,k,node[now].r,y);
        }else
        {
            y=now;
            split_k(node[now].l,k,x,node[now].l);
        }
        update(now);
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
        {
            x=now;
            split_s(node[now].r,s-node[node[now].l].sz-node[now].w,node[now].r,y);
        }
        update(now);
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
    inline int newnode(const Node t)
    {
        int now;
        if (trashcnt) now=trash[trashcnt--];else now=++nodecnt;
        node[now]=t;
        return now;
    }
    inline void delnode(int x)
    {
        trash[++trashcnt]=x;
    }
    void ins(const Node t)
    {
        int x,y,z;
        split_k(rt,t.k,x,z);
        split_k(x,t.k-1,x,y);
        if (y)
        {
            pushdown(y);
            ++node[y].w;
            ++node[y].sz;
        }else
        {
            y=newnode(t);
        }
        rt=mergeab(mergeab(x,y),z);
    }
    int del(const int k)
    {
        int x,y,z,res=1;
        split_k(rt,k,x,z);
        split_k(x,k-1,x,y);
        if (!y) res=0;
        else
        {
            if (node[y].w>1)
            {
                pushdown(y);
                --node[y].w;
                --node[y].sz;
            }
            else
            {
                delnode(y);
                y=0;
            }
        }
        rt=mergeab(mergeab(x,y),z);
        return res;
    }
    int getrk(int x)
    {
        int now=rt,res=0;
        while (now)
        {
            pushdown(now);
            if (node[now].k>=x) now=node[now].l;
            else res+=node[node[now].l].sz+node[now].w,now=node[now].r;
        }
        return res+1;
    }
    int findrk(int x)
    {
        if (node[rt].sz<x) return -1;
        int now=rt;
        while (now)
        {
            pushdown(now);
            if (x<=node[node[now].l].sz) now=node[now].l;
            else if (x<=node[node[now].l].sz+node[now].w) return now;
            else x-=node[now].w+node[node[now].l].sz,now=node[now].r;
        }
        return -1;
    }
    int findpre(int x)
    {
        int now=rt,mx=-2147483648;
        while (now)
        {
            pushdown(now);
            if (node[now].k<x) mx=max(mx,node[now].k),now=node[now].r;
            else now=node[now].l;
        }
        return mx;
    }
    int findnxt(int x)
    {
        int now=rt,mn=2147483647;
        while (now)
        {
            pushdown(now);
            if (node[now].k>x) mn=min(mn,node[now].k),now=node[now].l;
            else now=node[now].r;
        }
        return mn;
    }
}tr;
inline int myrand()
{
    return rand()<<15|rand();
}
int main()
{
    srand(19260817);
    int n1,Q;
    cin>>n1>>Q;
    while (n1--)
    {
        int x;
        scanf("%d",&x);
        tr.ins((FTreap::Node){x,0,0,1,1,myrand()});
    }
    long long ans=0;
    for (int cas=1,lst=0;cas<=Q;++cas)
    {
        int op,x;
        scanf("%d%d",&op,&x);
        ///!!!
        x^=lst;///attention!
        ///!!!
        if (op==1)
        {
            tr.ins((FTreap::Node){x,0,0,1,1,myrand()});
            continue;
        }
        if (op==2)
        {
            tr.del(x);
            continue;
        }
        if (op==3)
        {
            //printf("%d\n",lst=tr.getrk(x));
            ans^=(lst=tr.getrk(x));
            continue;
        }
        if (op==4)
        {
            int now=tr.findrk(x);
            if (now==-1) puts("-1");
            else
            {
                //printf("%d\n",lst=tr.node[now].k);
                ans^=(lst=tr.node[now].k);
            }
            continue;
        }
        if (op==5)
        {
            //printf("%d\n",lst=tr.findpre(x));
            ans^=(lst=tr.findpre(x));
            continue;
        }
        if (op==6)
        {
            //printf("%d\n",lst=tr.findnxt(x));
            ans^=(lst=tr.findnxt(x));
            continue;
        }
    }
    cout<<ans<<endl;
    return 0;
}
