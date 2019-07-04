
/*
A Puzzle for Pirates HDU - 1538
*/

int  solve(int n,int m,int q){
        if(n <= 2*m+2){
            if(q == n){
                  return  m-(n-1)/2;
            }
            else{
                  if(q % 2== n%2) return 1;
                  else            return 0;
            }
        }
        else{
           if(q <= 2*m+2) return 0;
            if(n == q)
           {
            LL  t = 2*m+2;
            while(t < n)
                t = 2*(t-m);
            if(t == n) return 0;
            else       return -1;
           }
           else{
            LL t  = 2*m+2;
            while(t < q)
                t = 2*(t-m);
            if(t  <= n)  return 0;
            else              return -1;
           }
        }
}
int main(void)
{
    int T;
    cin>>T;
    while(T--){
        LL n,m,q;
        cin>>n>>m>>q;
      LL ans = solve(n,m,q);
       
      if(ans == -1) puts("Thrown");
      else printf("%lld\n",ans);
    }
    

   return 0;
}

