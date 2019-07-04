const int maxn = 100010;
LL a[maxn],add[maxn],sum[maxn];
int pos[maxn],R[maxn],L[maxn];
int n,m,t;
void change(int l,int r,LL d){
  int p = pos[l],q = pos[r];
  if(p == q){
    for(int i = l;i <= r; ++i) a[i] += d;
    sum[p] += (r-l+1)*d;
  }
  else{
    for(int i = p+1;i <= q-1; ++i) add[i] += d;
    for(int i = l;i <= R[p];++i)
      a[i] += d;
    sum[p] += (R[p]-l+1)*d;
    for(int i = L[q];i <= r; ++i)
      a[i] += d;
    sum[q] += (r-L[q]+1)*d;
  }
}
LL ask(int l,int r){
  LL ans = 0;
  int p = pos[l],q = pos[r];
  if(p == q){
    for(int i = l;i <= r; ++i)
      ans += a[i];
    ans += (r-l+1)*add[p];
  }
  else{
    for(int i = p+1;i <= q-1; ++i)
      ans += sum[i]+add[i]*(R[i]-L[i]+1);
    for(int i = l;i <= R[p]; ++i)
      ans += a[i];
    ans += add[p]*(R[p]-l+1);
    for(int i = L[q];i <= r; ++i)
      ans += a[i];
    ans += add[q]*(r-L[q]+1);
  }
  return ans;
}
int main(void){

  cin>>n>>m;
  for(int i = 1;i <= n; ++i) scanf("%lld",&a[i]);
  LL t = sqrt(n);
  for(int i = 1;i <= t; ++i){
    L[i] = (i-1)*sqrt(n)+1;
    R[i] = i*sqrt(n);
  }
  if(R[t]  < n) t++,L[t] = R[t-1]+1,R[t] = n;
  // cout<<t<<endl;
  for(int i = 1;i <= t; ++i){
    for(int j = L[i];j <= R[i]; ++j){
      pos[j] = i;
      sum[i] += a[j];
    }
  }
  while(m--){
    char op[3];
    int l,r,x;
    scanf("%s%d%d",op,&l,&r);
    if(op[0] == 'C'){
      scanf("%d",&x);
      change(l,r,x);
    }
    else
      printf("%lld\n",ask(l,r));
  }
  return 0;
}
