
// 欧几里得扩展
long long ex_gcd(long long a,long long b,long long &x,long long &y)
{
    if(b == 0)
    {
        x = 1;
        y = 0;
        return a;
    }
    long long m = ex_gcd(b,a%b,y,x);
     y  -= a/b * x;
    return m;
}
int main()
{
    long long a,b,x,y;
    cin>>a>>b; //求a 关于b的逆元
    if(ex_gcd(a,b,x,y)==1)
        cout<<(x%b+b)%b<<endl;
    else
        cout<<"None"<<endl;
    return 0;
}
// 费马小定理求逆元
qpow(a,p-2,p);
// 逆元打表

   int inv[10000];
    int p;
    cin>>p;
    inv[1] = 1;
    for(int i = 2;i < p; ++i)
    {
        inv[i] = (p - p/i*inv[p%i]%p)%p;
    }
    for(int i = 1;i < p; ++i)
        cout<<inv[i]<<" ";
    cout<<endl;
    for(int i = 1;i < p; ++i)
        cout<<i * inv[i] % p<<" ";
        
 // 快速阶乘逆元
 
 const int maxn = 1e5+10;
long long fac[maxn],invfac[maxn];
void init(int n){
    fac[0] = 1;
    for(int i = 1;i <= n; ++i) fac[i] = fac[i-1]*i%mod;
    invfac[n] = qpow(fac[n],mod-2);
    for(int i = n-1;i >= 0; --i) invfac[i] = invfac[i+1]*(i+1)%mod;
} 
