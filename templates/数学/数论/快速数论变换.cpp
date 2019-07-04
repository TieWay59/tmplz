const int mod = 998244353;
LL qpow(LL a,LL b){LL s=1;while(b>0){if(b&1)s=s*a%mod;a=a*a%mod;b>>=1;}return s;}
const int g = 3;  //原根
LL quick_mod(LL a,LL b)
{
    LL ans=1;
    for(;b;b/=2)
    {
        if(b&1)
            ans=ans*a%mod;
        a=a*a%mod;
    }
    return ans;
}
int rev(int x,int r)  //蝴蝶操作
{
    int ans=0;
    for(int i=0; i<r; i++)
    {
        if(x&(1<<i))
        {
            ans+=1<<(r-i-1);
        }
    }
    return ans;
}
void NTT(int n, LL  A[],int on) // 长度为N (2的次数) 
{
    int r=0;
    for(;; r++)
    {
        if((1<<r)==n)
            break;
    }
    for(int i=0; i<n; i++)
    {
        int tmp=rev(i,r);
        if(i<tmp)
            swap(A[i],A[tmp]);
    }
    for(int s=1; s<=r; s++)
    {
        int m=1<<s;
        LL wn=quick_mod(g,(mod-1)/m);
        for(int k=0; k<n; k+=m)
        {
            LL  w=1;
            for(int j=0; j<m/2; j++)
            {
                LL t,u;
                t=w*(A[k+j+m/2]%mod)%mod;
                u=A[k+j]%mod;
                A[k+j]=(u+t)%mod;
                A[k+j+m/2]=((u-t)%mod+mod)%mod;
                w=w*wn%mod;
            }
        }
    }
    if(on==-1)
    {
        for(int i=1;i<n/2;i++)
            swap(A[i],A[n-i]);
        LL inv=quick_mod(n,mod-2);
        for(int i=0;i<n;i++)
            A[i]=A[i]%mod*inv%mod;
    }
    
}
