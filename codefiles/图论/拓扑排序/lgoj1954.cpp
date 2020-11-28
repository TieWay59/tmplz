/**
ans_position_i=position_ans_i=i
ans_i<=a_i
position_x_i<position_y_i

first line : any legal solution
second line : the minimum position of i (in all legal solution)
**/
#include <bits/stdc++.h>
using namespace std;
#define pb push_back
const int M = 10005;
const int N = 2005;
struct pii
{
    int x,y;
};
struct topocmp
{
    bool operator () (pii x,pii y)
    {
        if (x.x!=y.x) return x.x<y.x;
        return x.y>y.y;
    }
};
priority_queue <pii,vector<pii>,topocmp> heap;
vector <int> radj[N];
pii e[M];
int a[N],d[N],dd[N],ans[N],pos[N],mnpos[N];
int n,m;
int main()
{
    cin>>n>>m;
    while (!heap.empty()) heap.pop();
    for (int i=1;i<=n;++i) d[i]=0;
    for (int i=1;i<=n;++i) scanf("%d",&a[i]);
    for (int i=1;i<=m;++i)
    {
        scanf("%d%d",&e[i].x,&e[i].y);
        radj[e[i].y].pb(e[i].x);
        ++d[e[i].x];
    }
    for (int i=1;i<=n;++i) dd[i]=d[i];
    for (int i=1;i<=n;++i) if (!d[i]) heap.push((pii){a[i],i});
    int id=n;
    while (!heap.empty())
    {
        pii t=heap.top();heap.pop();
        if (t.x<id) break;
        ans[id]=t.y;--id;
        for (auto i:radj[t.y])
        {
            --d[i];
            if (!d[i]) heap.push((pii){a[i],i});
        }
    }
    if (id!=0) {puts("no solution!");return 0;}
    for (int i=1;i<=n;++i) pos[ans[i]]=i;
    for (int i=1;i<=n;++i) printf("%d%c",ans[i],(i==n) ? '\n' : ' ');
    for (int key=1;key<=n;++key)
    {
        for (int i=1;i<=n;++i)
        {
            d[i]=dd[i];
            if (!d[i]) heap.push((pii){a[i],i});
        }
        int id=n,flag=0,mn=n;
        while (!heap.empty())
        {
            pii t=heap.top();heap.pop();
            if (t.y==key) {flag=1;continue;}
            if (t.x<id)
            {
                if (flag)
                {
                    heap.push((pii){t.x,t.y});
                    flag=0;
                    mn=id;
                    ans[id]=key;--id;
                    for (auto i:radj[key])
                    {
                        --d[i];
                        if (!d[i]) heap.push((pii){a[i],i});
                    }
                    continue;
                }
                puts("error");break;
            }
            ans[id]=t.y;--id;
            for (auto i:radj[t.y])
            {
                --d[i];
                if (!d[i]) heap.push((pii){a[i],i});
            }
        }
        if (flag)
        {
            flag=0;
            mn=id;
            ans[id]=key;--id;
        }
        mnpos[key]=mn;
    }
    for (int i=1;i<=n;++i) printf("%d%c",mnpos[i],(i==n) ? '\n' : ' ');
    return 0;
}
