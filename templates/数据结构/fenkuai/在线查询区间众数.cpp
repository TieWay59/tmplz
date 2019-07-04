const int N  = 40006,T = 37;
int a[N],b[N],L[N],R[N],pos[N];
int c[T][T][N],f[T][T][2],now[2];
inline void work(int x,int y,int num){
    ++c[x][y][num];
    if(c[x][y][num] > now[0] ||(c[x][y][num] == now[0] && num < now[1])){
        now[0] = c[x][y][num];
        now[1] = num;
    }
}   
int ask(int l,int r){
    int p = pos[l],q = pos[r];
    int x = 0,y = 0;
    if(p+1 <= q-1){
        x = p+1;
        y = q-1;
    }
    memcpy(now,f[x][y],sizeof(now));
    if(p == q){
        rep(i,l,r+1) work(x,y,a[i]);
        rep(i,l,r+1) --c[x][y][a[i]];
    }
    else{
        rep(i,l,R[p]+1) work(x,y,a[i]);
        rep(i,L[q],r+1) work(x,y,a[i]);
        rep(i,l,R[p]+1) --c[x][y][a[i]];
        rep(i,L[q],r+1) --c[x][y][a[i]];
    }
    return b[now[1]];
}
int main(void){
        // freopen("input.txt","r",stdin);

        // freopen("output1.txt","w+",stdout);
    int n,m;cin>>n>>m;
    rep(i,1,n+1) scanf("%d",&a[i]);
    memcpy(b,a,sizeof(a));
    sort(b+1,b+n+1);
    int tot = unique(b+1,b+n+1)-(b+1);
    rep(i,1,n+1) a[i] = lower_bound(b+1,b+tot+1,a[i])-b;
    int t = pow((double)n,(double)1/3);
    int len = t?n/t:n;
    for(int i = 1;i <= t; ++i){
        L[i] = (i-1)*len+1;
        R[i] = i*len;
    }
    if(R[t] < n){
        L[t+1] = R[t]+1;
        R[++t] = n;
    }
    rep(i,1,t+1)
        rep(j,L[i],R[i]+1)
            pos[j] = i;

    me(c),me(f);
    rep(i,1,t+1){
        rep(j,i,t+1){
            rep(k,L[i],R[j]+1)
                ++c[i][j][a[k]];
            rep(k,1,tot+1)
                if(c[i][j][k] > f[i][j][0]){
                    f[i][j][0] = c[i][j][k];
                    f[i][j][1] = k;
                }
        }
    }
    int x = 0;
    while(m--){
        int l,r;scanf("%d%d",&l,&r);
        l = (l+x-1)%n+1;
        r = (r+x-1)%n+1;
        if(l > r) swap(l,r);
        printf("%d\n",x = ask(l,r));
    }


    return 0;
}

