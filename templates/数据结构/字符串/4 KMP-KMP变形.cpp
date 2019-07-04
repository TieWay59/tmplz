
//https://www.nowcoder.com/acm/contest/119/E

#include <bits/stdc++.h>
using namespace std;
 
const int N=200010;
int a[N],b[N];
int x[N],y[N],nxt[N];
 
void kmp_pre(int x[],int m,int nxt[])
{
    int i,j;
    j=nxt[0]=-1;
    i=0;
    while(i<m) {
        while(-1!=j && (x[i]!=x[j]&&x[j]!=-1))j=nxt[j];
        nxt[++i]=++j;
    }
}
 
int KMP_Count(int x[],int m,int y[],int n)
{
//    for (int i=0;i<n;i++) {
//        printf("%d ",y[i]);
//    }
//    puts("");
//    for (int i=0;i<m;i++) {
//        printf("%d ",x[i]);
//    }
//    puts("");
    int i,j;
    int ans=0;
    kmp_pre(x,m,nxt);
    i=j=0;
    while(i<n) {
        while(-1!=j && !(y[i]==x[j]||(x[j]==-1&&(y[i]==-1||j-y[i]<0)))) j=nxt[j];
        i++;
        j++;
        if(j>=m) {
            ans++;
            j=nxt[j];
        }
    }
    return ans;
}
 
int main()
{
    int n,m,k;
    scanf("%d%d",&n,&k);
    memset(x,-1,sizeof(x));
    memset(y,-1,sizeof(y));
    map<int,int> pre;
    for (int i=0;i<n;i++) {
        scanf("%d",&a[i]);
        auto pos=pre.find(a[i]);
        if (pos!=pre.end()) {
            y[i]=i-pos->second;
        }
        pre[a[i]]=i;
    }
    scanf("%d",&m);
    pre.clear();
    for (int i=0;i<m;i++) {
        scanf("%d",&b[i]);
        auto pos=pre.find(b[i]);
        if (pos!=pre.end()) {
            x[i]=i-pos->second;
        }
        pre[b[i]]=i;
    }
    printf("%d\n",KMP_Count(x,m,y,n));
    return 0;
}
