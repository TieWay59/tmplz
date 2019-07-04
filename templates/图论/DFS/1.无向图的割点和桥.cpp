
SPF POJ - 1523
// 如果有割点，那么割点与子节点边就是割边
int dfs(int u,int fa){
    int lowu = pre[u] = ++dfs_clock;
    int child = 0;
    for(int i = 0;i < G[u].size(); ++i){
        int v = G[u][i];
        if(!pre[v]){
            child++;
            int lowv = dfs(v,u);
            lowu = min(lowu,lowv);
            if(lowv >= pre[u]){
                iscut[u]++;
            }
        }
        else if(pre[v] < pre[u] && v != fa){
            lowu = min(lowu,pre[v]);
        }
    }
    if(fa < 0&&child == 1) iscut[u] = 0;
    else if(fa < 0&&child >= 2) iscut[u] = child-1;
    return low[u] = lowu;
}
如果要输出去掉割点之后的联通分量的个数，需要谈判根的情况
#include<iostream>
#include<cstdio>
#include<cctype>
#include<cstring>
#include<algorithm>
#include<vector>
#include<stack>
#include<map>
#include<queue>
#include<cmath>
#define mem(ar,num) memset(ar,num,sizeof(ar))
#define me(ar) memset(ar,0,sizeof(ar))
#define lowbit(x) (x&(-x))
#define Pb push_back
#define  FI first
#define  SE second
#define rep(i,a,n) for (int i=a;i<n;i++)
#define per(i,a,n) for (int i=n-1;i>=a;i--)
#define IOS ios::sync_with_stdio(false)
#define DEBUG cout<<endl<<"DEBUG"<<endl; 
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
const int    prime = 999983;
const int    INF = 0x7FFFFFFF;
const LL     INFF =0x7FFFFFFFFFFFFFFF;
const double pi = acos(-1.0);
const double inf = 1e18;
const double eps = 1e-6;
const LL     mod = 1e9 + 7;
LL qpow(LL a,LL b){LL s=1;while(b>0){if(b&1)s=s*a%mod;a=a*a%mod;b>>=1;}return s;}
LL gcd(LL a,LL b) {return b?gcd(b,a%b):a;}
int dr[2][4] = {1,-1,0,0,0,0,-1,1};
typedef pair<int,int> P;
const int maxn = 1000+100;
// cosnt int maxm = 1e6+100
int pre[maxn];
int dfs_clock = 0;
vector<int> G[maxn];
int iscut[maxn];
int low[maxn];

void init(){
    dfs_clock = 1;
    rep(i,1,maxn) G[i].clear();
    me(iscut);
    me(low);
    me(pre);
}
int dfs(int u,int fa){
    int lowu = pre[u] = ++dfs_clock;
    int child = 0;
    for(int i = 0;i < G[u].size(); ++i){
        int v = G[u][i];
        if(!pre[v]){
            child++;
            int lowv = dfs(v,u);
            lowu = min(lowu,lowv);
            if(lowv >= pre[u]){
                iscut[u]++;
            }
        }
        else if(pre[v] < pre[u] && v != fa){
            lowu = min(lowu,pre[v]);
        }
    }
    if(fa < 0&&child == 1) iscut[u] = 0;
    else if(fa < 0&&child >= 2) iscut[u] = child-1;
    return low[u] = lowu;
}
// #define Debug
int main(void)
{
    #ifdef Debug
    freopen("input.txt","r",stdin);
    freopen("output.txt","w+",stdout);
    #endif
    int kase = 0;
    while(1){
        init();
        int u,v;
        int t = 0;
        while(scanf("%d",&u)==1&&u != 0){
          t++;
          scanf("%d",&v);
          G[u].Pb(v);
          G[v].Pb(u);
        }   
        if(t==0)break;
        // rep(i,1,maxn) if(!G[i].empty()){

        //  dfs(i,-1);
        //  break;
        // }
        dfs(1,-1);
        int num = 0;
        rep(i,1,1001) if(iscut[i]) num++;
        
        printf("Network #%d\n",++kase);
        if(num > 0)
        {
            rep(i,1,1001) if(iscut[i]){
            printf("  SPF node %d leaves %d subnets\n",i,iscut[i]+1);
        }
        }
        else 
            printf("  No SPF nodes\n");
        if(kase) puts("");
    }

   return 0;
}
