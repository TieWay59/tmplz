/* 状态压缩dp+矩阵快速幂，用1*2 的小方块填满N*M的矩形*/
//1033 骨牌覆盖 V2 

#include<bits/stdc++.h>

using namespace std;
typedef long long LL;
const int maxn = 13;
const int mod = 1e9+7;
int n,m;
LL f[12][1<<11];
bool in_s[1<<11];

struct Matrix{
  #define  maxn  100
  int n,m;
  Matrix(int nn = 1,int mm = 1):n(nn),m(mm){ memset(a,0,sizeof(a));};
  long long a[maxn][maxn];
};
void print(const Matrix &a)
{
 for(int i = 1;i <= a.n; ++i,cout<<endl)
  for(int j= 1;j <= a.m; ++j)
     cout<<a.a[i][j]<<" ";
}
Matrix operator*(Matrix a,Matrix b)
{
  assert(a.m == b.n);
  Matrix c(a.n,b.m);
  for(int i = 1;i <= a.n; ++i)
  {
    for(int j = 1;j <= b.m; ++j)
    {
      for(int k = 1;k <= a.m; ++k)
      {
        c.a[i][j] += a.a[i][k] * b.a[k][j];
        c.a[i][j] %= mod;
      }
    }
  }
//  print(c);
  return c;
}
Matrix B;
void solve(int m){
  for(int i = 0;i < (1<<m); ++i){
    bool cnt = 0,has_odd = 0;
    for(int j = 0;j < m; ++j){
      if(i >>j &1) has_odd |= cnt,cnt = 0;
      else cnt^= 1;
      in_s[i] = has_odd |cnt?0:1;
    }

  }

  // f[0][0] = 1;
  // for(int i = 1;i <= n; ++i){
    for(int j = 0;j < (1<<m); ++j){
      // f[i][j] = 0;
      for(int k = 0;k < (1<<m); ++k){
        if((j&k) == 0&& in_s[j|k])
             B.a[j+1][k+1] = 1;
           // f[i][j]  += f[i-1][k];
      // }
    }
  }
  // print(B);
  // cout<<f[n][0]<<endl;
}


LL M,N;
int main(void){
  scanf("%lld%lld",&M,&N);
  B.n = B.m = 1<<N;
  solve(N);
  Matrix ans(1,1<<N);

  ans.a[1][1] = 1;
  // print(ans);
  // cout<<endl;
  // print(B);
  while(M > 0){
    if(M & 1) 
      ans = ans*B;
    B = B*B;
    // cout<<endl;
    // print(B);
    M >>= 1;
  }
  cout<<ans.a[1][1]<<endl;

  return 0;
}

/* 加强版
1*1 和2*1 的小方块
SWERC2017 C - Macarons 
搜索求状态*/


// 矩阵快速幂
// 注意修改maxn 的值，要不然容易T

const int maxn = 260;
int n;
struct Matrix{
    int n,m;
    Matrix(int nn = 1,int mm = 1):n(nn),m(mm){ memset(a,0,sizeof(a));};
    int  a[maxn][maxn];
};
void print(const Matrix &a)
{
 for(int i = 1;i <= a.n; ++i,cout<<endl)
  for(int j= 1;j <= a.m; ++j)
     cout<<a.a[i][j]<<" ";
}
Matrix operator*(Matrix a,Matrix b)
{
    Matrix c(a.n,b.m);
    for(int i = 1;i <= a.n; ++i)
    {
        for(int j = 1;j <= b.m; ++j)
        {
            for(int k = 1;k <= a.m; ++k)
            {
                c.a[i][j] = (1ll*c.a[i][j]+1ll*a.a[i][k] * b.a[k][j])%mod;
            }
        }
    }
//  print(c);
    return c;
}
// 状态压缩

LL MM[maxn][maxn];
LL N,M;
// a 代表是a的递推，now代表当前行的状态，nxt代表下一行的状态
void dfs(int  a,int  now,int  nxt){
  // cout<<a<<endl;
  int tmpnow = now,tmpnxt = nxt;
  int one[10],two[10];
  memset(one,0,sizeof(one));
  memset(two,0,sizeof(two));
  int cnt = 0;
  while(tmpnow > 0){
    one[cnt++] = tmpnow&1;
    tmpnow >>= 1;

  }
  bool flag = true;
  for(int i = 0;i < N; ++i){
     if(!one[i]){
        flag = false;
        break;
     }
  }
  if((now & NN) == NN){
    MM[a][nxt]++;
    return ;
  }
  cnt = 0;
  while(tmpnxt  > 0){
    two[cnt++] = tmpnxt&1;
    tmpnxt >>= 1;
  }
  for(int i = 0;i < N; ++i){
    if(!one[i]){
        dfs(a,now|(1<<i),nxt);
        dfs(a,now|(1<<i),nxt|(1<<i));
        if(i + 1 < N&& !one[i+1]){
            dfs(a,now|(1<<i)|(1<<(i+1)),nxt);
        }
       break;
    }
  }

}
int NN;
Matrix ans(NN,NN);
Matrix B(NN,NN);
void solve(){
    B.n = B.m = ans.n = ans.m = NN;
    for(int i = 1;i <= NN; ++i){
        for(int j = 1;j <= NN; ++j)
        {
            B.a[i][j] = MM[i-1][j-1];
        }
    }

    for(int i = 1;i <= NN; ++i) ans.a[i][i] = 1;
    while(M > 0){
        if(M & 1)
            ans = ans*B;
        B = B*B;
        M >>= 1;
    }
   cout<<ans.a[1][1]<<endl;
}
int main(void)
{
    scanf("%lld%lld",&N,&M);
    // cout<<N<<" "<<M<<endl;
    NN = 1<<N;
    // cout<<N<<" "<<NN<<endl;
    for(int i = 0;i < NN; ++i){
        dfs(i,i,0);
    }
    solve();
   return 0;
}



