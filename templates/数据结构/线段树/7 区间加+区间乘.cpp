//洛谷P3373
const int maxn = 100000+10;
LL n,m,mod;
LL sumv[maxn<<2],addv[maxn<<2],mulv[maxn<<2];
LL a[maxn];
#define lc  (o<<1)
#define rc  (o<<1|1)
void maintain(int o,int l,int r){
	sumv[o] = sumv[lc]+sumv[rc];
	sumv[o] %= mod;
}
void pushdown(int o,int l,int r){
	int m = (l+r)>>1;
	if(mulv[o]!= 1){
		sumv[lc] = sumv[lc]*mulv[o]%mod,sumv[rc] = sumv[rc]* mulv[o]%mod;
		addv[lc] = addv[lc] *mulv[o]%mod,addv[rc]  = addv[rc] * mulv[o]%mod;
		mulv[lc] = (mulv[lc]*mulv[o])%mod,mulv[rc] = (mulv[rc]* mulv[o]%mod);
		mulv[o] = 1;
	}
	if(addv[o]){
		sumv[lc] = (sumv[lc]+addv[o]*(m-l+1))%mod;
		addv[lc] = (addv[lc]+addv[o])%mod;
		sumv[rc] = (sumv[rc]+addv[o]*(r-m))%mod;
		addv[rc] = (addv[rc]+addv[o])%mod;
		addv[o] =  0;
	}
}


void build(int o,int l,int r){

	if(l == r){
		sumv[o] = a[l];
		addv[o] = 0;
		mulv[o] = 1; 
		return ;
	}
	int m = (l+r)>>1;
	build(lc,l,m);
	build(rc,m+1,r);
	// sumv[o] = 
	addv[o] = 0,mulv[o] = 1;
	maintain(o,l,r);
}
int op;
void update(int o,int l,int r,int L,int R,LL v){
	if(L <= l &&R >= r){
		if(op == 2){
			sumv[o] = (sumv[o]+v*(r-l+1))%mod;
			addv[o] += v;
		}
		else{
			sumv[o] = (sumv[o]*v)%mod;
			addv[o] = (addv[o]*v)%mod;
			mulv[o] = (mulv[o]*v)%mod;
		}
	}
	else{
		int m = (l+r)>>1;
		pushdown(o,l,r);
		if(L <= m)
			update(lc,l,m,L,R,v);
		if(R > m)
			update(rc,m+1,r,L,R,v);
		maintain(o,l,r);
	}
    
}
LL _sum;
void query(int o,int l,int r,int L,int R){
	if(L <= l && R >= r){
		_sum += sumv[o];
		_sum %= mod;
		return ;
	}
	pushdown(o,l,r);
	int m = (l+r)>>1;
	if(L <= m)
		query(lc,l,m,L,R);
	if(R > m)
		query(rc,m+1,r,L,R);
	// pushup()
}



int main(void){
	cin>>n>>m>>mod;
	for(int i = 1;i <= n; ++i)
		scanf("%lld",&a[i]);
	build(1,1,n);
	// _sum = 0;
	// query(1,1,n,1,n);
	// cout<<_sum<<endl;
	for(int i = 1;i <= m; ++i){
		int x,y,v;
		scanf("%d%d%d",&op,&x,&y);
		if(op == 1||op == 2){
			scanf("%d",&v);
			update(1,1,n,x,y,v);
		}
		else{
			_sum = 0;
			query(1,1,n,x,y);
			_sum %= mod;
			printf("%lld\n",_sum);
		}
	}


	return 0;
}
