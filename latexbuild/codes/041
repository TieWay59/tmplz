#include <bits/stdc++.h>
using namespace std;
const int MAXSIZE = 100005;
struct FTreap
{
    struct Tag
    {
        int rev;
    };
    struct Node
    {
        int k,l,r,w,sz,rnd;
        Tag tag;
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
        int ls=node[now].l,rs=node[now].r;
        if (node[now].tag.rev)
        {
            if (ls)
            {
                swap(node[ls].l,node[ls].r);
                node[ls].tag.rev^=1;
            }
            if (rs)
            {
                swap(node[rs].l,node[rs].r);
                node[rs].tag.rev^=1;
            }
            node[now].tag.rev^=1;
        }
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
    void print(int now)
    {
        if (!now) return;
        pushdown(now);
        print(node[now].l);
        printf("%d ",node[now].k);
        print(node[now].r);
    }
}tr;
inline int myrand()
{
    return rand()<<15|rand();
}
FTreap::Node a[MAXSIZE];
int n;
int main()
{
    srand(19260817);
    int Q;
    cin>>n>>Q;
    for (int i=1;i<=n;++i)
    {
        a[i].k=i;
        a[i].l=a[i].r=0;
        a[i].w=a[i].sz=1;
        a[i].rnd=myrand();
        a[i].tag.rev=0;
        tr.ins(a[i]);
    }
    for (int cas=1;cas<=Q;++cas)
    {
        int l,r,x,y,z;
        scanf("%d%d",&l,&r);
        tr.split_s(tr.rt,r,x,z);
        tr.split_s(x,l-1,x,y);
        swap(tr.node[y].l,tr.node[y].r);
        tr.node[y].tag.rev^=1;
        tr.rt=tr.mergeab(tr.mergeab(x,y),z);
    }
    tr.print(tr.rt);
    return 0;
}
