
//1142 : 三分·三分求极值
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
const double eps = 1e-9;
const LL     mod = 1e9 + 7;
LL qpow(LL a,LL b){LL s=1;while(b>0){if(b&1)s=s*a%mod;a=a*a%mod;b>>=1;}return s;}
LL gcd(LL a,LL b) {return b?gcd(b,a%b):a;}
int dr[2][4] = {1,-1,0,0,0,0,-1,1};
typedef pair<int,int> P;
double a,b,c,X,Y; 
double f(double xx){
	return a*xx*xx+b*xx+c;
}
double d(double x){
	double t = a*x*x+b*x+c;
	return sqrt((X-x)*(X-x)+(t-Y)*(t-Y));
    
}
int main(void)
{
    
    cin>>a>>b>>c>>X>>Y;
 
    double l,r,lm,rm;
    l = -200.0,r = 200.0;
    while(r - l >= eps){
    	 lm = (r+l)/2;
    	 rm = (r+lm)/2;
    	if(d(rm)<d(lm))
    	   l = lm;
    	else 
    	   r = rm;
	}

	printf("%.3lf\n",d(l));
	
	
   return 0;
}
