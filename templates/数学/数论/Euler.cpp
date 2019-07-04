#### 欧拉函数打表
O(nlog(n)) 
```

const int maxn = 1e6+100;
int phi[maxn],Prime[maxn];

void init2(int n){
	for(int i = 1;i <= n; ++i) phi[i] = i;
    for(int i = 2;i <= n; ++i){
    	if(i == phi[i]){
    	   for(int j = i; j <= n; j += i) phi[j] = phi[j]/i*(i-1);
    	}
    }
}
```
 线性筛 O(n)
```
const int maxn = 1e6+100;
bool check[maxn];
int phi[maxn],Prime[maxn];
void init(int MAXN){
	int N = maxn-1;
    memset(check,false,sizeof(check));
    phi[1] = 1;
    int tot = 0;
    for(int i = 2;i <= N; ++i){
    	if(!check[i]){
    		Prime[tot++] = i;
    		phi[i] = i-1;
    	}
    	for(int j = 0;j < tot; ++j){
    		if(i*Prime[j] > N) break;
    		check[i*Prime[j]] = true;
    		if(i%Prime[j] == 0){
    			phi[i*Prime[j]] = phi[i]*Prime[j];
    			break;
    		}
    		else{
    			phi[i*Prime[j]] = phi[i]*(Prime[j]-1);
    		}
    	}
    }

}
```
