

int main(void)
{
    std::ios::sync_with_stdio(false);
    int T;
    cin>>T;
    int Kase = 0;
    while(T--)
    {
        LL n;
        cin>>n;
        int m = (int)sqrt(n);
        LL ans = 0;
        for(LL i = 1;i < m; ++i)
        {
            ans += n/i;
            ans += (LL)i*(n/i - n/(i+1));
        }
        ans += n/m;
        ans += m*(n/m-m);
        printf("Case %d: %lld\n",++Kase,ans);
    }
