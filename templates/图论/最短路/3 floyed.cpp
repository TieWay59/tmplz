// https://hihocoder.com/problemset/problem/1089?sid=1348128
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
struct Floyd{
	// 复杂度O(n^3) 
	#define maxn 300
	int d[maxn][maxn];
	int n,m;
	void init(void){
		scanf("%d %d",&n,&m);
		for(int i = 1;i <= n ;++i)
		 for(int j = 1;j <= n; ++j)
		    if(i != j)
		       d[i][j] = INF;
		int u,v,c;
		for(int i = 0;i < m; ++i){
			scanf("%d %d %d",&u,&v,&c);
			d[u][v] = d[v][u] = min(d[v][u],c);
		} 
	}
	void floyd(void){
		for(int k = 1; k <= n; ++k)
		 for(int i = 1;i <= n ;++i)
		   for(int j = 1;j <= n; ++j)
		     if(d[i][k] < INF&&d[j][k] < INF)
		        d[i][j] = min(d[i][j],d[i][k]+d[j][k]);
	} 
	void print(void){
		for(int i = 1;i <= n; ++i){
			for(int j = 1;j <= n; ++j)
			  printf("%d%c",d[i][j]," \n"[j==n]);
		}
	}
	
};
Floyd floyd;
int main(void)
{
	 floyd.init();
	 floyd.floyd();
	 floyd.print();
   

   return 0;
}

