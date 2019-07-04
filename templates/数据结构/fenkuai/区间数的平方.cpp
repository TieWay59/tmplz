const int maxn = 50000+10;
int n,m,k;
int pos[maxn];
int a[maxn];
int num[maxn];
LL  Ans[maxn];
int L[maxn],R[maxn];
struct Query{
	int l,r,id;
};
Query q[maxn];
bool cmp1 (const Query &a,const Query &b){
	return a.l < b.l ||(a.l == b.l && a.r < b.r);
}
bool cmp2(const Query &a,const  Query &b){
	return a.r < b.r;
}

void work(int x,LL &ans,int d){
	ans -= 1ll*num[x]*num[x];
	num[x] += d;
	ans += 1ll*num[x]*num[x];
}
int main(){
	cin>>n>>m>>k;
	rep(i,1,n+1) scanf("%d",&a[i]);
	rep(i,1,m+1){
		scanf("%d%d",&q[i].l,&q[i].r);
		q[i].id = i;
	}
	int t = sqrt(m);
	for(int i = 1;i <= t; ++i){
		L[i] = (i-1)*t;
		R[i] = i*t;
	}
	if(R[t] < m){
		L[t+1] = R[t]+1;
		R[++t] = m; 
	}
	sort(q+1,q+m+1,cmp1);
	for(int i = 1;i <= t; ++i){
		sort(q+L[i],q+R[i]+1,cmp2);
		LL ans = 0;
		me(num);
		int l = q[L[i]].l,r = q[L[i]].r;
		rep(i,l,r+1) work(a[i],ans,1);
		Ans[q[L[i]].id] = ans;
		for(int j = L[i]+1;j <= R[i]; ++j){
			// l = L[j].l,r = L[j].r;
			while(l < q[j].l) work(a[l++],ans,-1);
			while(l > q[j].l) work(a[--l],ans,1);
			while(r < q[j].r) work(a[++r],ans,1);
			while(r > q[j].r) work(a[r--],ans,-1);
			Ans[q[j].id] = ans;
		}
	}
	rep(i,1,m+1)
		printf("%lld\n",Ans[i]);
	return 0;
}
