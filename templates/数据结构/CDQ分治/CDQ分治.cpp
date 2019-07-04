// CDQ 解决 单点修改，区间查询
/*

*/
const int maxn = 5e6+100;

struct node{
    int type,id;
    LL val;
    bool operator <(const node &a) const
    {
        if(a.id != id) return id < a.id;
        return type < a.type;
    }
};

node A[maxn],B[maxn];
LL ans[maxn];



void CDQ(int L,int R){
  // cout<<L<<" "<<R<<endl;
  if(L == R) return ;
  int M = (L+R)>>1;
  CDQ(L,M),CDQ(M+1,R);
  int t1 = L,t2 = M+1;
  LL sum = 0;
  for(int i = L;i <= R; ++i){
    if((t1 <= M && A[t1] < A[t2])||t2 > R){
        if(A[t1].type == 1) sum += A[t1].val;
        B[i] = A[t1++];
    }
    else{
        if(A[t2].type == 2) ans[A[t2].val] -= sum;
        else if(A[t2].type == 3) ans[A[t2].val] += sum;
        B[i] = A[t2++];
    }

  }

  for(int i = L;i <= R; ++i) A[i] = B[i];
}
int main(void)
{
    int n,q;
    cin>>n>>q;
    int tot = 0;
    for(int i = 1;i <= n; ++i){
            scanf("%lld",&A[i].val);
            A[i].type = 1;
            A[i].id = i;
    }
    tot = n;
    int sz = 0;
    rep(i,0,q){
        int type;
        scanf("%d",&type);
        if(type ==1){
            A[++tot].type = 1;
            scanf("%d%lld",&A[tot].id,&A[tot].val);
        }
        else{
           int l,r;
           scanf("%d%d",&l,&r);
           A[++tot].type = 2,A[tot].id = l-1,A[tot].val = ++sz;
           A[++tot].type = 3,A[tot].id = r,  A[tot].val = sz;
        }
    }
    CDQ(1,tot);
    rep(i,1,sz+1){
        printf("%lld\n",ans[i]);
    }

   return 0;
}
