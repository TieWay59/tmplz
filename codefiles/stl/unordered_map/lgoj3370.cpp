#include <bits/stdc++.h>
using std::cin;
using std::cout;
using std::endl;
using std::set;
using std::string;
using std::unordered_map;
using std::map;
typedef long long ll;
typedef double db;
struct my_hash
{
    size_t operator () (const string &x) const
    {
        return 0;
    }
};
unordered_map <string,int,my_hash> mp;
string st;
int main()
{
    int n,tot=0;
    cin>>n;
    while (n--)
    {
        cin>>st;
        if (mp[st]==0) ++tot;
        ++mp[st];
    }
    for (auto it = mp.begin();it!=mp.end();++it) cout<<(*it).first<<endl;
    cout<<tot<<endl;
    return 0;
}

