#include <bits/stdc++.h>
using namespace std;
const int MAXLEN = 5000005;
struct Lyndon
{
    int st[MAXLEN],len;
    vector <int> pos;
    void duval()
    {
        pos.clear();
        st[0]=st[len+1]=0;
        for (int i=1,j,k;i<=len;)
        {
            j=i;k=i+1;
            for (;k<=len && st[j]<=st[k];++k) j=(st[j]==st[k]) ? j+1 : i;
            for (;i<=j;i+=k-j) pos.push_back(i+k-j-1);
        }
    }
}lyn;
string st;
int n;
int main()
{
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    cin>>st;
    n=st.size();
    lyn.len=n;
    for (int i=1;i<=n;++i) lyn.st[i]=st[i-1];
    lyn.duval();
    int ans=0;
    for (auto it:lyn.pos) ans^=it;
    cout<<ans<<endl;
    return 0;
}
