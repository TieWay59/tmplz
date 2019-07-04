
#include <bits/stdc++.h>
#define mem(ar,num) memset(ar,num,sizeof(ar))
#define me(ar) memset(ar,0,sizeof(ar))
#define lowbit(x) (x&(-x))
#define Pb push_back
#define  FI first
#define  SE second
#define rep(i,a,n) for (int i=a;i<n;i++)
#define per(i,a,n) for (int i=n-1;i>=a;i--)
#define IOS ios::sync_with_stdio(false)
#define DEBUG cout<<endl<<"DEBUG"<<endl; 
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
const int    prime = 999983;
const int    INF = 0x7FFFFFFF;
const LL     INFF =0x7FFFFFFFFFFFFFFF;
const double pi = acos(-1.0);
const double inf = 1e18;
const double eps = 1e-6;
const LL     mod = 1e9 + 7;
LL qpow(LL a,LL b){LL s=1;while(b>0){if(b&1)s=s*a%mod;a=a*a%mod;b>>=1;}return s;}
LL gcd(LL a,LL b) {return b?gcd(b,a%b):a;}
int dr[2][4] = {1,-1,0,0,0,0,-1,1};
typedef pair<int,int> P;

const int maxn = 2e5+100;
int n,m;
int a[maxn];
int del[maxn];
int id[maxn];
bool del2[maxn];
struct nd{
    int id,val;
};
bool operator <(const nd &a,const nd &b){
    return a.id < b.id;
}
bool operator >(const nd &a,const nd &b){
    return !(a < b);
}
nd A[maxn],B[maxn];
LL ans[maxn];
LL tree[maxn];
void Add(int x,int y){
    while(x <= n)
    {
        tree[x] += y;
        x += lowbit(x);
    }
}
LL Sum(int x){
    LL sum  = 0;
    while(x > 0){
        sum += tree[x];
        x -= lowbit(x);
    }
    return sum;
}
void CDQ(int L,int R){
    // DEBUG;
    if(L == R) return ;
    int M = (L+R)>>1;
    CDQ(L,M),CDQ(M+1,R);
    int t1 = L,t2 = M+1;
    for(int i = L;i <= R; ++i){
        if((t1 <= M&&A[t1] < A[t2])||t2 > R){
            Add(A[t1].val,1);
            B[i] = A[t1++];
        }
        else{
            ans[id[A[t2].val]] += Sum(n)-Sum(A[t2].val);
            B[i] = A[t2++];
        }
    }
     for(int i = L;i <= M; ++i)
        Add(A[i].val,-1);
     t1 = M,t2 = R;
    for(int i = R;i >= L; --i){
        if((t1 >= L&&A[t1] > A[t2])||t2 <= M){
            Add(A[t1].val,1);
            t1--;
            // B[i] = A[t2++];?
        }
        else{
            ans[id[A[t2].val]] += Sum(A[t2].val);
            t2--;
        }
    }
    for(int i = L;i <= M; ++i)
        Add(A[i].val,-1);
    for(int i = L;i <= R; ++i)
        A[i] = B[i];
}
LL ans2[maxn];
int sign[maxn];
int main(void)
{

    // cout<<maxn*maxn/2<<endl;
    // freopen("input.txt","r",stdin);
    // freopen("output.txt","w",stdout);
    scanf("%d%d",&n,&m);
    // int s;
    for(int i = 1;i <= n; ++i){
        scanf("%d",&a[i]);
        id[a[i]] = i;
    }
    for(int i = 1;i <= m;++i){
        scanf("%d",&del[i]);
        del2[id[del[i]]] =  1;
    }
    // DEBUG;
    int cnt = 0;
    for(int i = 1;i <= n; ++i){
       if(!del2[i])
          {
             A[++cnt].id = i,A[cnt].val = a[i];
             sign[cnt] = a[i];
          }
    }
    for(int i = m; i >= 1; --i){
       // A[++cnt].op = 1,A[cnt].id = id[del[i]],A[cnt].val = a[i];
        A[++cnt].id = id[del[i]],A[cnt].val = del[i];
        sign[cnt] = del[i];
    }
    CDQ(1,n);
    LL sum = 0;
    for(int i = 1;i <= n; ++i){
        sum += ans[id[sign[i]]];
        ans2[i] = sum;
    }
    for(int i = n;i >= n-m+1; --i){
        printf("%lld\n",ans2[i]);
    }

   return 0;
}
