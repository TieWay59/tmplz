#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXLEN = 5000005;
const int MOD = 1e9+7;
struct Lyndon
{
    int st[MAXLEN],len;
    int mnsuf[MAXLEN];
    vector <int> pos;
    void duval()
    {
        pos.clear();
        st[0]=st[len+1]=0;
        for (int i=1,j,k;i<=len;)
        {
            mnsuf[i]=i;
            j=i;k=i+1;
            for (;k<=len && st[j]<=st[k];++k)
            {
                if (st[j]==st[k])
                {
                    mnsuf[k]=mnsuf[j]+k-j;
                    ++j;
                }else
                {
                    j=i;
                    mnsuf[k]=i;
                }
            }
            for (;i<=j;i+=k-j) pos.push_back(i+k-j-1);
        }
    }
}lyn;
string st;
int n;
int main()
{
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int T;
    cin>>T;
    while (T--)
    {
        cin>>st;
        n=st.size();
        lyn.len=n;
        for (int i=1;i<=n;++i) lyn.st[i]=st[i-1];
        lyn.duval();
        //for (auto it:lyn.pos) cout<<it<<' ';cout<<endl;
        //for (int i=1;i<=n;++i) cout<<lyn.mnsuf[i]<<' ';cout<<endl;
        ll ans=0;
        for (ll i=1,mi=1;i<=lyn.len;++i,mi=mi*1112%MOD) (ans+=mi*lyn.mnsuf[i])%=MOD;
        ans=(ans%MOD+MOD)%MOD;
        cout<<ans<<endl;
    }
    return 0;
}
