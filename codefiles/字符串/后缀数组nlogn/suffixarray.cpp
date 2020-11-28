#include <bits/stdc++.h>
using namespace std;
const int MAXLEN = 1000006;
struct Suffix_Array
{
    int n;
    int st[MAXLEN];
    int rk[MAXLEN<<1],trk[MAXLEN<<1],rl[MAXLEN],trl[MAXLEN],cnt[MAXLEN],tcnt[MAXLEN],lcp[MAXLEN];
    void print()
    {
        //for (int i=1;i<=n;++i) printf("%d ",rk[i]);puts("");
        for (int i=1;i<=n;++i) printf("%d ",rl[i]);puts("");
        for (int i=2;i<=n;++i) printf("%d ",lcp[i]);puts("");
    }
    void suffix_sort()
    {
        st[n+1]=-1;
        memset(rk,0,sizeof(rk));
        memset(trk,0,sizeof(trk));
        memset(cnt,0,sizeof(cnt));
        int mx=0;
        for (int i=1;i<=n;++i) ++cnt[st[i]],mx=max(mx,st[i]);
        for (int i=1;i<=mx;++i) cnt[i]+=cnt[i-1];
        for (int i=n;i;--i) rl[cnt[st[i]]--]=i;
        rk[rl[1]]=1;
        for (int i=2;i<=n;++i) rk[rl[i]]=rk[rl[i-1]]+(st[rl[i]]!=st[rl[i-1]]);
        for (int len=1;len<n && rk[rl[n]]!=n;len<<=1)
        {
            for (int i=1;i<=n;++i) trk[i]=rk[i];
            for (int i=1;i<=n;++i) cnt[i]=tcnt[i]=0;
            for (int i=1;i<=n;++i) ++cnt[rk[i]],++tcnt[rk[i+len]];
            for (int i=1;i<=n;++i) cnt[i]+=cnt[i-1],tcnt[i]+=tcnt[i-1];
            for (int i=n;i;--i) trl[tcnt[rk[i+len]]--]=i;
            for (int i=n;i;--i) rl[cnt[rk[trl[i]]]--]=trl[i];
            rk[rl[1]]=1;
            for (int i=2;i<=n;++i) rk[rl[i]]=rk[rl[i-1]]+(trk[rl[i]]!=trk[rl[i-1]] || trk[rl[i]+len]!=trk[rl[i-1]+len]);
        }
        for (int i=1,len=0;i<=n;++i)
        {
            if (len) --len;
            while (st[i+len]==st[rl[rk[i]-1]+len] && i+len<=n && rl[rk[i]-1]+len<=n) ++len;
            lcp[rk[i]]=len;
        }
    }
}s1;
char st[MAXLEN];
int main()
{
    scanf("%s",st);
    s1.n=strlen(st);
    for (int i=1;i<=s1.n;++i) s1.st[i]=(int)st[i-1];
    s1.suffix_sort();
    s1.print();
    return 0;
}
