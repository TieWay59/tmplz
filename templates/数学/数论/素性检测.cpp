#include<bits/stdc++.h>

using namespace std;
//typedef long long LL;
const int LEN  = 1e6+1;
bool vis[LEN];
//int prime[LEN];
int Prime[LEN];
int cnt = 1;
typedef unsigned long long LL;

LL modular_multi(LL x,LL y,LL mo) {
	LL t;
	x%=mo;
	for(t=0;y;x=(x<<1)%mo,y>>=1)
		if (y&1)
			t=(t+x)%mo;
	return t;
}

LL modular_exp(LL num,LL t,LL mo) {
	LL ret=1,temp=num%mo;
	for(;t;t>>=1,temp=modular_multi(temp,temp,mo))
		if (t&1)
			ret=modular_multi(ret,temp,mo);
	return ret;
}

bool miller_rabin(LL n) {
	if (n==2||n==7||n==61)
        return true;
	if (n==1||(n&1)==0)
        return false;
	int t=0,num[3]={2,7,61};//2,7,61对unsigned int内的所有数够用了，最小不能判断的数为4 759 123 141；用2,3,7,61在 10^16 内唯一不能判断的数是 46 856 248 225 981
	LL a,x,y,u=n-1;
	while((u&1)==0)
        t++,u>>=1;
	for(int i=0;i<3;i++) {
		a=num[i];
		x=modular_exp(a,u,n);
		for(int j=0;j<t;j++) {
			y=modular_multi(x,x,n);
			if (y==1&&x!=1&&x!=n-1)
				return false;
            //其中用到定理，如果对模n存在1的非平凡平方根，则n是合数。
            //如果一个数x满足方程x^2≡1 (mod n),但x不等于对模n来说1的两个‘平凡’平方根：1或-1，则x是对模n来说1的非平凡平方根
			x=y;
		}
		if (x!=1)//根据费马小定理,若n是素数，有a^(n-1)≡1(mod n).因此n不可能是素数
			return false;
	}
	return true;
}
void init(void)
{
    int n = LEN -1;
    for(int i = 2; i <= n; ++i)
    {
        if(!vis[i])
        {
            Prime[cnt++] = i;
            for(LL j = (LL)i *  i; j <= n; j += i)
                vis[j] = 1;
        }
    }
}
bool isPrime(LL n)
{
	if(n < 1e6)
	{
		for(LL i = 1;i < cnt&&Prime[i] < n; ++i)
	{
		if(n % Prime[i] == 0)
		 return false;
	}
	return true;
	}
	else
	 return miller_rabin(n);
 } 

int main(void)
{
	init();

	int T;
	cin>>T;
	while(T--)
	{
	   LL n;
	   cin>>n;
	   if(isPrime(n))
	      cout<<"Yes"<<endl;
	   else
	      cout<<"No"<<endl;
	}
	
	return 0;
} 
