
#include <bits/stdc++.h>
using namespace std;
const double pi = acos(-1.0);
int main(void)
{
    for(int i = 0;i < 5; ++i)
    printf("%.*f\n",i,pi);
    for(int i = 0;i < 5; ++i)
        cout<<setiosflags(ios::fixed)<<setprecision(i)<<pi<<endl;
    return 0;
}
