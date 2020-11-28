#include <bits/stdc++.h>
using namespace std;
const int N = 100005;
set <int> nxt[N];
int a[N];
int n,m;
int main()
{
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int type,Q;
    cin>>type>>n>>Q>>m;
    for (int i=1;i<=m;++i) nxt[i].clear();
    for (int i=1;i<=n;++i)
    {
        cin>>a[i];
        nxt[a[i]].insert(i);
    }
    while (Q--)
    {
        int len,x,pos=0,flag=1;
        cin>>len;
        while (len--)
        {
            cin>>x;
            if (!flag) continue;
            auto it=nxt[x].upper_bound(pos);
            if (it==nxt[x].end()) flag=0;else pos=*it;
        }
        if (!flag) puts("No");else puts("Yes");
    }
    return 0;
}
