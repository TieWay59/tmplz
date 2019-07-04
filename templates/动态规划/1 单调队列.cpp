//https://ac.nowcoder.com/acm/contest/223/C
//C	区区区间间间
//$$ v_{l,r} = max(a_i-a_j) (l <= i,j <= r)$$
//$$ \sum_{i}^{n} \sum_{j+1}^{n} v_{i,j}$$
const int maxn = 1e5+100;
int a[maxn];
int s[maxn];// 单调栈
// 第一遍求在这个区间里面最大
int pre[maxn];
int nxt[maxn];
int main(void)
{
    int T,n;
    cin>>T;
    while(T--){
        scanf("%d",&n);
        for(int i = 1;i <= n; ++i){
            scanf("%d",&a[i]);
        }
        int t = 0;
        for(int i = 1;i <= n; ++i){
            pre[i] = nxt[i] = 0;
            while(t > 0&&a[i] > a[s[t]]) nxt[s[t]] = i,t--;
            pre[i] = s[t];
            s[++t] = i;
            // cout<<pre[i]<<" ";
        }
        while(t > 0)
            nxt[s[t]] = n+1,t--;
        LL ans = 0;
        for(int i = 1;i <= n; ++i){
            ans += 1ll*a[i]*(nxt[i]-i)*(i-pre[i]);
        }
        t = 0;
        for(int i = 1;i <= n; ++i){
            pre[i] = nxt[i] = 0;
            while(t > 0&&a[i] < a[s[t]]) nxt[s[t]] = i,t--;
            pre[i] = s[t];
            s[++t] = i;
        }
         while(t > 0)
            nxt[s[t]] = n+1,t--;
        for(int i = 1;i <= n; ++i){
            ans -= 1ll*a[i]*(nxt[i]-i)*(i-pre[i]);
        }
        printf("%lld\n",ans);
    }

    return 0;
}
