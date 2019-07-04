
// 异或
void FWT(int *a,int N,int opt){
	const int inv2 = qpow(2,mod-2);
	// j是区间开始点，i是区间距离，k是具体位置，j+k,i+j+k就是在a数组中的坐标
	for(int i = 1;i < N; i <<= 1){
		for(int p = i<<1,j = 0;j < N; j += p){
			for(int k = 0;k < i; ++k){
                int X = a[j+k],Y = a[i+j+k];
                a[j+k] = (X+Y)%mod;
                a[i+j+k] = (X+mod-Y)%mod;
                if(opt == -1) a[j+k] = 1ll*a[j+k]*inv2%mod,a[i+j+k] = 1ll*a[i+j+k]*inv2%mod;


			}
		}
	}
}

 或   
if(opt == 1) F[i+j+k] = (F[i+j+k]+F[j+k]) %mod;
else         F[i+j+k] = (F[i+j+k+mod-F[j+k]) %mod;
和
if(opt == 1) F[j+k] = (F[j+k]+F[i+j+k]) %mod;
else         F[j+k] = (F[j+k] +mod-F[i+j+k])%mod;
