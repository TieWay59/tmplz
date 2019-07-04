
/*
ZOJ
Dynamic Rankings ZOJ - 2112
动态第k大数
*/
//lowbit 自己写
#define lson l,m
#define rson m+1,r
const int N = 60006;
int a[N],Hash[N];
int T[N],L[N<<5],R[N<<5],sum[N<<5];
int S[N];
int n,m,tot;
struct node{
  int l,r,k;
  bool Q;
}op[10005];

int build(int l,int r){
  int rt = (++tot);
  sum[rt] = 0;
  if(l != r){
    int m  = (l+r)>>1;
    L[rt] = build(lson);
    R[rt] = build(rson);

  }
  return rt;
}
int update(int pre,int l,int r,int x,int val){
  int rt = (++tot);
  L[rt] = L[pre],R[rt] = R[pre],sum[rt] = sum[pre]+val;
  if(l < r){
    int m = (l+r)>>1;
    if(x <= m)
      L[rt] = update(L[pre],lson,x,val);
    else
      R[rt] = update(R[pre],rson,x,val);
  }
  return rt;
}
int use[N];
void add(int x,int pos,int val){
  while(x <= n){
    S[x] = update(S[x],1,m,pos,val);
    x += lowbit(x);
  }
}
int Sum(int x){
  int ret = 0;
  while(x > 0){
    ret += sum[L[use[x]]];
    x -= lowbit(x);
  }
  return ret;
}

int query(int u,int v,int lr,int rr,int l,int r,int k){
  if(l >= r)
    return l;
  int m = (l+r)>>1;
  int tmp = Sum(v)-Sum(u)+sum[L[rr]]-sum[L[lr]];
  if(tmp >= k){
    for(int i = u;i;i -= lowbit(i))
      use[i] = L[use[i]];
    for(int i = v;i;i -= lowbit(i))
      use[i] = L[use[i]];
    return query(u,v,L[lr],L[rr],lson,k);
  }
  else{
      for(int i = u;i ;i -= lowbit(i))
        use[i] = R[use[i]];
      for(int i = v;i ;i -= lowbit(i))
        use[i] = R[use[i]];
      return query(u,v,R[lr],R[rr],rson,k-tmp);
  }

}

void modify(int x,int p,int d){
  while(x <= n){
    S[x] = update(S[x],1,m,p,d);
    x += lowbit(x);
  }
}
int main(){
  int t;
  scanf("%d",&t);
  while(t--){
    int q;
    scanf("%d%d",&n,&q);
    tot = 0;
    m = 0;
    for(int i = 1;i <= n; ++i)
    {
      scanf("%d",&a[i]);
      Hash[++m] = a[i];
    }
    for(int i = 0;i < q; ++i){
      char s[10];
      scanf("%s",s);
      if(s[0] == 'Q'){
        scanf("%d%d%d",&op[i].l,&op[i].r,&op[i].k);
        op[i].Q = 1;
      }
      else{
        scanf("%d%d",&op[i].l,&op[i].r);
        op[i].Q = 0;
        Hash[++m] = op[i].r;
      }
    }
    sort(Hash+1,Hash+1+m);
    int mm = unique(Hash+1,Hash+1+m)-Hash-1;
    m = mm;
    T[0] = build(1,m);
    for(int i = 1;i <= n; ++i) 
      T[i] = update(T[i-1],1,m,lower_bound(Hash+1,Hash+1+m,a[i])-Hash,1);
    // DEBUG;

    for(int i = 1;i <= n; ++i)
      S[i] = T[0];
    for(int i = 0;i < q; ++i){
      // DEBUG;
      if(op[i].Q){

        // cout<<op[i].l<<" "<<op[i].r<<" "<<endl;
        for(int j = op[i].l-1;j;j -= lowbit(j))
          use[j] = S[j];
        for(int j = op[i].r  ;j;j -= lowbit(j))
          use[j] = S[j];
        // DEBUG;
        printf("%d\n",Hash[query(op[i].l-1,op[i].r,T[op[i].l-1],T[op[i].r],1,m,op[i].k)]);

      }
      else{
        modify(op[i].l,lower_bound(Hash+1,Hash+1+m,a[op[i].l])-Hash,-1);
        modify(op[i].l,lower_bound(Hash+1,Hash+1+m,op[i].r)-Hash,1);
        a[op[i].l] = op[i].r;
      }

    }
  }
  return 0;
}

/*
2
5 3
3 2 1 4 7
Q 1 4 3
C 2 6
Q 2 5 3
5 3
3 2 1 4 7
Q 1 4 3
C 2 6
Q 2 5 3
*/
