// 主席树求第k大
// 先离散，后可持续化建树
// poj 2104

#include <bits/stdc++.h>
#define me(ar) memset(ar,0,sizeof(ar))
#define rep(i,a,n) for (int i=a;i<n;i++)
using namespace std;
const int maxn = 1e5+10;
int sum[maxn<<5],L[maxn<<5],R[maxn<<5];
int rt[maxn];
int a[maxn],Hash[maxn];
int tot = 0;
int build(int l,int r){
	int rt = (++tot);
    sum[rt] = 0;
    if(l < r){
    	int m = (l+r) >> 1;
    	L[rt] = build(l,m);
    	R[rt] = build(m+1,r);
    }
    return rt;
}

int update(int pre,int l,int r,int x){
     int rt = (++tot);
     L[rt] = L[pre],R[rt] = R[pre],sum[rt] = sum[pre]+1;
     if(l < r){
     	int m = (l+r)>>1;
     	if(x <= m)
     		L[rt] = update(L[pre],l,m,x);
        else 
        	R[rt] = update(R[pre],m+1,r,x);
     }
     return rt;
}
int query(int u,int v,int l,int r,int k){
    if(l >= r) return r;
	int num = sum[L[v]]-sum[L[u]];
	int m = (l+r)>>1;
    if(num >= k)
    	return query(L[u],L[v],l,m,k);
    	return query(R[u],R[v],m+1,r,k-num);
}
int main(void)
{
  
  	int T;
  	scanf("%d",&T);
  	while(T--){
  		tot = 0;
  		int n,m;
  		scanf("%d%d",&n,&m);
  		// map<int,int> ma;
  		rep(i,1,n+1){scanf("%d",&a[i]);Hash[i] =  a[i];}
  		sort(Hash+1,Hash+1+n);
  		int id = unique(Hash+1,Hash+n+1) - Hash-1;
  		rt[0] = build(1,id);
        rep(i,1,n+1){
           int x = lower_bound(Hash+1,Hash+id+1,a[i]) - Hash;
           rt[i] = update(rt[i-1],1,id,x);
        }
        rep(i,0,m){
        	int l,r,k;
        	scanf("%d%d%d",&l,&r,&k);
        	int ans = query(rt[l-1],rt[r],1,id,k);
        	printf("%d\n",Hash[ans]);
        }
  	}    

   return 0;
}
