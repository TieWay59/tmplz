#include <bits/stdc++.h>
using namespace std;
const int MAXLEN = 5000005;
struct Lyndon
{
    int st[MAXLEN],len,mnid;
    vector <int> pos;
    void duval()
    {
        pos.clear();
        st[0]=st[len+1]=-1;
        for (int i=1,j,k;i<=len;)
        {
            j=i;k=i+1;
            for (;k<=len && st[j]<=st[k];++k)
            {
                if (st[j]<st[k]) j=i;
                else ++j;
            }
            if (i<=len/2) mnid=i;
            for (;i<=j;i+=k-j) pos.push_back(i+k-j-1);
        }
    }
}lyn;
string st;
int n;
int main()
{
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    cin>>n;
    lyn.len=n;
    for (int i=1;i<=n;++i) cin>>lyn.st[i],lyn.st[i+n]=lyn.st[i];
    lyn.len*=2;
    lyn.duval();
    //cout<<lyn.mnid<<endl;
    for (int i=lyn.mnid;i<lyn.mnid+lyn.len/2;++i) cout<<lyn.st[i]<<' ';cout<<endl;
    return 0;
}
