/*
有n个石子，先手第一次最多取n-1个，之后如果前一个人取m个，
则下一个人可以取1到k*m个，取完最后一个为胜，
问先手是否会胜，如果会胜输出第一次取几个。
**/
const int maxn = 2e6+100;
int a[maxn],b[maxn];
int main(void)
{
    int T;
    cin>>T;
    for(int kase  = 1;kase <= T; ++kase){
        int n,k;
        cin>>n>>k;
        a[0] = 1,b[0] = 1;
        int i = 0,j = 0;
        while(a[i] < n){
            i++;
            a[i] = b[i-1]+1;
            if(a[j+1] * k < a[i])  j++;
            if(a[j] * k < a[i])  b[i] = b[j]+a[i];
            else      b[i] = a[i]; 

        }
        printf("Case %d: ",kase);
        if(a[i] == n) {
            puts("lose");
            continue;
        } 
        // i--;
        while(i >= 0){
            if(n-a[i] > 0)
                n -= a[i];
            if(n == a[i]) break;
            i--;
        }
        printf("%d\n",n);
    }

   return 0;
}
