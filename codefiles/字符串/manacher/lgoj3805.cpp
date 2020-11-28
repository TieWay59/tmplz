#include <bits/stdc++.h>
using namespace std;
void manacher(int * a,int n,int * len)
{
    for (int i=1,mid=0,r=0;i<=n;++i)
    {
        if (i<=r) len[i]=min(r-i+1,len[2*mid-i]);else len[i]=1;
        while (i-len[i]>0 && i+len[i]<=n && a[i+len[i]]==a[i-len[i]]) ++len[i];
        if (i+len[i]-1>r) r=i+len[i]-1,mid=i;
    }
}
int a[22200000],len[22200000],n,mxid,ans;
string st;
int main()
{
    std::ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    cin>>st;n=st.size();
    for (int i=1;i<=n;++i) a[i*2]=st[i-1],a[i*2-1]=-1;
    a[n*2+1]=-1;n=n*2+1;
    manacher(a,n,len);
    mxid=1;
    for (int i=2;i<=n;++i) if (len[i]>len[mxid]) mxid=i;
    if (a[mxid]==-1) ans=(len[mxid]-1)/2*2;else ans=(len[mxid]-1-1)/2*2+1;
    cout<<ans<<endl;
    return 0;
}
