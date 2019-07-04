//[POJ-2931] 
// 超自然数求解不平等博弈问题
char ar[100];
bool b[100];
LL sureal(int n){
  LL k  = 1;
  k <<= 52;
  for(int i = 0;i < n; ++i){
    scanf("%s",ar);
    if(ar[0] == 'W')
      b[i] = 1;
    else
      b[i] = 0;
  }
  LL x = 0,i = 0;
  while(i < n&&b[i] == b[0]){
    if(b[i]) x += k;
    else x -= k;
    i++;
  }
  k >>= 1;
  while(i < n){
    if(b[i]) 
      x += k;
    else
      x -= k;
    i++;
    k >>= 1;
  }
  return x;
}
int main(void)
{
   int T;
   cin>>T;
   while(T--){
     int n;
     char br[100];
     scanf("%s %d: ",br,&n);
     
     LL ans1 = 0,ans2 = 0;
     int a[3];
     rep(i,0,3)   scanf("%d",&a[i]);
     rep(i,0,3)   ans1 += sureal(a[i]);
     rep(i,0,3)   scanf("%d",&a[i]);
     rep(i,0,3)   ans2 += sureal(a[i]);
     // cout<<ans1<<" "<<ans2<<endl;
     printf("%s %d: ",br,n);
     if(ans1 >= ans2)
      puts("Yes");
     else
      puts("No");
   }

   return 0;
}
