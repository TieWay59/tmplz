const int LEN = 234567;
int F[LEN];
int val[LEN];
int Find(int x){
    int k = F[x];
    if(x!=k){
       F[x] = Find(k);
       val[x] += val[k];
    }
    return F[x];
}
int main(void)
{
    int N,M;
    while(cin>>N>>M) {
       for(int i = 0;i <= N; ++i){
           F[i] = i;
           val[i] = 0;
       }
       int a,b,c;
       int Count = 0;
       while(M--){
           scanf("%d %d %d",&a,&b,&c);
           a--;
           int x1 = Find(a);
           int y1 = Find(b);
           if(x1==y1&&c+val[a]!=val[b])
            ++Count;
           else if(x1<y1) {
               F[y1] = x1;
               val[y1] = c+val[a]-val[b];
           }
           else if(x1>y1){
               F[x1] = y1;
               val[x1] = val[b]-val[a]-c;
           }
       }
       cout<<Count<<endl;
    }
    return 0;
}
