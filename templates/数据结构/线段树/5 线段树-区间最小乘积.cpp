// 单点更新，区间查询


#include <bits/stdc++.h>
#define me(ar) memset(ar,0,sizeof(ar))
using namespace std;
const int    INF = 100000;
const int maxn = 1e6+10;
const int maxnode = 4*maxn;
int ql,qr;
int _p,_v;
struct T{
   int a,b,c,d;
   T(int aa = -INF,int bb = -INF,int cc = INF,int dd = INF):a(aa),b(bb),c(cc),d(dd){
   }
};
T up(T x,T y)
{
    int a[4] = {x.a,x.b,y.a,y.b};
    sort(a,a+4);
    x.a = a[3];
    x.b = a[2];
    int b[4] = {x.c,x.d,y.c,y.d};
    sort(b,b+4);
    x.c = b[0];
    x.d = b[1];
    return x;
}
T vv[maxnode];
T a[maxn];
void build(int o,int l,int r)
{
	int m = (r+l)>>1;
	if(l == r) vv[o] = a[l];
	else
	{
		build(o*2,l,m);
		build(o*2+1,m+1,r);
		vv[o] = up(vv[o*2],vv[o*2+1]);
	}
}
void update(int o,int l,int r)
{
	if(l == r) vv[o] = T(_v,-INF,_v,INF);
	else
	{
		int m = (r+l)>>1;
		if(_p <= m)
		 update(o*2,l,m);
		else
		 update(o*2+1,m+1,r);
		vv[o] = up(vv[o*2],vv[o*2+1]);
	}
}
T query(int o,int l,int r)
{
   
   if(l >= ql&&r <= qr)
     return vv[o];
   int m = l+(r-l)/2;
   T ans;
   if(ql <= m&&m < qr)
      ans = up(query(o*2,l,m),query(o*2+1,m+1,r));
   else if(ql <= m)
       ans = query(o*2,l,m);
   else if( m < qr)
       ans = query(o*2+1,m+1,r);
   return ans;  
}

int main(void)
{
   int N,Q;
   while(scanf("%d",&N) != EOF&&N)
   {
   	  for(int i  = 1;i <= N; ++i)
   	  {
   	  	 int aa;
   	  	 scanf("%d",&aa);
   	  	 a[i] = T(aa,-INF,aa,INF);
	  }
	  build(1,1,N);
   	  cin>>Q;
   	  while(Q--)
   	  {
   	  	int op;
   	  	scanf("%d",&op);
   	  	if(op == 1)
   	  	{
   	  		 scanf("%d %d",&_p,&_v);
   	  		 update(1,1,N);
			 }
		else 
		{
			scanf("%d %d",&ql,&qr);
   	  	    T ans = query(1,1,N);
   	  	    long long an = min(ans.a*ans.b,min(ans.a*ans.c,ans.c*ans.d));
   	  	    printf("%lld\n",an);
		}
   	  	
		 }
	} 

   return 0;
}
