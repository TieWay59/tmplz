#include<bits/stdc++.h>
#define reg register
using namespace std;
typedef long long LL;
const int MN=60;
LL a[61],tmp[61];
bool flag;
void ins(LL x){
    for(reg int i=MN;~i;i--)
        if(x&(1LL<<i))
            if(!a[i]){a[i]=x;return;}
            else x^=a[i];
    flag=true;
}
bool check(LL x){
    for(reg int i=MN;~i;i--)
        if(x&(1LL<<i))
            if(!a[i])return false;
            else x^=a[i];
    return true;
}
LL qmax(LL res=0){
    for(reg int i=MN;~i;i--)
        res=max(res,res^a[i]);
    return res;
}
LL qmin(){
    if(flag)return 0;
    for(reg int i=0;i<=MN;i++)
        if(a[i])return a[i];
}
LL query(LL k){
    reg LL res=0;reg int cnt=0;
    k-=flag;if(!k)return 0;
    for(reg int i=0;i<=MN;i++){
        for(int j=i-1;~j;j--)
            if(a[i]&(1LL<<j))a[i]^=a[j];
        if(a[i])tmp[cnt++]=a[i];
    }
    if(k>=(1LL<<cnt))return -1;
    for(reg int i=0;i<cnt;i++)
        if(k&(1LL<<i))res^=tmp[i];
    return res;
}
int main(){
    int n;LL x;scanf("%d",&n);
    for(int i=1;i<=n;i++)scanf("%lld",&x),ins(x);
    printf("%lld\n",qmax());
    return 0;
}
