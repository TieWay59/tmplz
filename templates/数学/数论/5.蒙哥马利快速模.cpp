#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,n) for (int i=a;i<n;i++)
#define per(i,a,n) for (int i=n-1;i>=a;i--)
#define pb push_back
#define mp make_pair
#define all(x) (x).begin(),(x).end()
#define fi first
#define se second
#define SZ(x) ((int)(x).size())
typedef vector<int> VI;
typedef long long ll;
typedef pair<int,int> PII;
const ll mod=1000000007;
ll powmod(ll a,ll b) {ll res=1;a%=mod; assert(b>=0); for(;b;b>>=1){if(b&1)res=res*a%mod;a=a*a%mod;}return res;}
ll gcd(ll a,ll b) { return b?gcd(b,a%b):a;}
// head
 
typedef unsigned long long u64;
typedef __int128_t i128;
typedef __uint128_t u128;
int _,k;
u64 A0,A1,M0,M1,C,M;
 
struct Mod64 {
   Mod64():n_(0) {}
   Mod64(u64 n):n_(init(n)) {}
   static u64 init(u64 w) { return reduce(u128(w) * r2); }
   static void set_mod(u64 m) {
      mod=m; assert(mod&1);
      inv=m; rep(i,0,5) inv*=2-inv*m;
      r2=-u128(m)%m;
   }
   static u64 reduce(u128 x) {
      u64 y=u64(x>>64)-u64((u128(u64(x)*inv)*mod)>>64);
      return ll(y)<0?y+mod:y;
   }
   Mod64& operator += (Mod64 rhs) { n_+=rhs.n_-mod; if (ll(n_)<0) n_+=mod; return *this; }
   Mod64 operator + (Mod64 rhs) const { return Mod64(*this)+=rhs; }
   Mod64& operator -= (Mod64 rhs) { n_-=rhs.n_; if (ll(n_)<0) n_+=mod; return *this; }
   Mod64 operator - (Mod64 rhs) const { return Mod64(*this)-=rhs; }
   Mod64& operator *= (Mod64 rhs) { n_= reduce(u128(n_)*rhs.n_); return *this; }
   Mod64 operator * (Mod64 rhs) const { return Mod64(*this)*=rhs; }
   u64 get() const { return reduce(n_); }
   static u64 mod,inv,r2;
   u64 n_;
};
u64 Mod64::mod,Mod64::inv,Mod64::r2;
 
u64 pmod(u64 a,u64 b,u64 p) {
   u64 d=(u64)floor(a*(long double)b/p+0.5);
   ll ret=a*b-d*p;
   if (ret<0) ret+=p;
   return ret;
}
 
 
void bruteforce() {
   u64 ans=1;
   for (int i=0;i<=k;i++) {
      ans=pmod(ans,A0,M);
      u64 A2=pmod(M0,A1,M)+pmod(M1,A0,M)+C;
      while (A2>=M) A2-=M;
      A0=A1; A1=A2;
   }
   printf("%llu\n",ans);
}
 
int main() {
   for (scanf("%d",&_);_;_--) {
      scanf("%llu%llu%llu%llu%llu%llu%d",&A0,&A1,&M0,&M1,&C,&M,&k);
      Mod64::set_mod(M);
      Mod64 a0(A0),a1(A1),m0(M0),m1(M1),c(C),ans(1),a2(0);
      for (int i=0;i<=k;i++) {
         ans=ans*a0;
         a2=m0*a1+m1*a0+c;
         a0=a1; a1=a2;
      }
      printf("%llu\n",ans.get());
   }
}
