void Era_s(void){
    check[1] = 1;
    tot = 1;
    for(int i = 2;i < maxn; ++i){
        if(!check[i]){
        Prime[tot++] = i;    
        for(int j = i+i;j < maxn; ++j)  check[j] = 1;
        }
    } 
}
void Euler_s(void){
    check[1] = 1;
    tot = 1;
    int n = 1e6;
    for(int i = 2;i <= n; ++i){
         if(!check[i]) Prime[tot++] = i; 
         for(int j = 1;j < tot; ++j){
            if(i*Prime[j] > n) break;
            check[i*Prime[j]] = 1;
            if(i % Prime[j] == 0) break;
         }
    }
}
