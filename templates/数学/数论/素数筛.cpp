```
Eratosthenes筛法（埃拉托斯特尼筛法）
onst int maxn = 1e6+10;
bool check[maxn];
int Prime[maxn];
int tot = 1;
void Eratosthenes(void){
	const int n = maxn -1;
	memset(check,0,sizeof(check));
	for(int i = 2;i < n; ++i){
		if(!check[i]){
			Prime[tot++] = i;
			for(int j = i+i;j < n;j += i) check[j] = 1;
		}
	}
} 
```
欧拉筛
```
const int maxn = 1e6+10;
bool check[maxn];
int Prime[maxn];
int tot = 1;
void Euler_shai(void){
	int n = maxn-1;
	memset(check,0,sizeof(check));
	for(int i = 2;i <= n; ++i){
		if(!check[i]){
			Prime[tot++] = i;
		}
			for(int j = 1;j < tot; ++j){
				if(i*Prime[j] > n) break;
			    	check[i*Prime[j]]  =1 ;
			    if(i % Prime[j]==0) break;
			}
	}
} 

```
