
#include <bits/stdc++.h>
#define mem(ar,num) memset(ar,num,sizeof(ar))
#define me(ar) memset(ar,0,sizeof(ar))
#define lowbit(x) (x&(-x))
#define Pb push_back
#define  FI first
#define  SE second
#define For(i,a,b) for(int i = a; i < b; ++i)
#define IOS ios::sync_with_stdio(false)
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
const int maxn = 1000+10;
vector<int> G[maxn];
int match[maxn];
bool used[maxn];
int N,M;
bool dfs(int v){
	used[v] = true;
	for(int i = 0;i < G[v].size(); ++i){
		if(used[u]) continue; used[u] = true;
		int u = G[v][i],w = match[u];
		if(w < 0||!used[w]&&dfs(w)){
			match[v] = u;
			match[u] = v;
			return true;
		}
	}
	return false;
}
int main(void)
{
    scanf("%d %d",&N,&M);
    
    while(M--){
    	int u,v;
    	scanf("%d %d",&u,&v);
    	G[u].Pb(v);
    	G[v].Pb(u);
	}
	int ans = 0;
	memset(match,-1,sizeof(match));
	for(int i = 1;i <= N; ++i){
		if(match[i] < 0){
			memset(used,0,sizeof(used));
			if(dfs(i)){
				ans++;
			}
		}
	}
   cout<<ans<<endl;
   return 0;
}

