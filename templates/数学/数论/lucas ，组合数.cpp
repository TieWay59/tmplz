LL qpow(LL a,LL b,LL m){
	LL ans = 1;
	a %= m;
	while(b > 0){
		if(b&1)
		   ans = ans*a%m;
		   a = a*a%m;
		   b >>= 1;
	}
	return ans;
}
LL C(LL n,LL m,LL p){
	if(m > n) return 0;
	LL tmp1 = 1,tmp2 = 1;
	m = min(n-m,m);
	for(LL i = 1;i <= m; ++i){
		tmp1 = tmp1*(n-m+i)%p;
		tmp2 = tmp2*i%p;
	}
	return tmp1*qpow(tmp2,p-2,p)%p;
}
LL lucas(LL n, LL m, LL p){
	if(m == 0)
	  return 1;
	return lucas(n/p,m/p,p)*C(n%p,m%p,p)%p;
}
