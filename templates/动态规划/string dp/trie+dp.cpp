/*

Margot 有一个 长度为字符串aa，给定nn个子串，
每一个子串一个价值wi，从原串中取出一个子串后，
原串的左右结合组合成一个新的串，
并且得到改子串的价值wi。 问能取到的最大价值
*/
// SWERC 2017 D candy
#include<bits/stdc++.h>

using namespace std;
const int maxn = 55;
const int maxm = 11000;// 200个串 200*50 tire树节点

inline void up(int &a,int b){
  a<b?(a=b):0;
}

// tire 树
const int maxnode = 4e5+100;
const int sigma_size = 26;
struct Trie
{
    int ch[maxnode][sigma_size];
    int val[maxnode];
    int sz;
    Trie()
    {
        sz = 1;
        memset(ch[0],0,sizeof(ch[0]));
        memset(val,-1,sizeof(val));
    }
    int idx(char c)
    {
        return c-'a';
    }
    void insert(char *s,int v)
    {
        int u = 0, n = strlen(s);
        for(int i = 0; i < n; ++i)
        {
            int c = idx(s[i]);
            if(!ch[u][c])
            {
                memset(ch[sz],0,sizeof(ch[sz]));
                //val[sz] = 0;
                ch[u][c] = sz++;
            }
            u = ch[u][c];
        }
        up(val[u], v);
    }
};

Trie tr;

int dp[maxn],f[maxn][maxn],g[maxn][maxm];
char ar[maxn];
char br[maxn];
int main(void){

   scanf("%s",ar+1);
   int n = strlen(ar+1);
   for(int i = 1;i <= n; ++i)
     ar[i] -= 'a';
   int C;
   scanf("%d",&C);
   while(C--){
      int u;
      scanf("%s %d",br,&u);
      int nn = strlen(br);
      tr.insert(br,u);
      reverse(br,br+nn);
      tr.insert(br,u);
   }
   
   // 初始化
  //  for(int i = 1;i < tr.sz; ++i)
  //   cout<<tr.val[i]<<" ";
  // cout<<endl;
   for(int i = 0;i <= n+1; ++i)
      for(int j = 0;j <= n+1; ++j)
        f[i][j] = -1;
   for(int i = n; i; --i){
    for(int j = i - 1;j <= n; ++j)
      for(int k = 0;k < tr.sz; ++k)
        g[j][k] = -1;
      // cout<<tr.sz<<endl;
    g[i-1][0] = 0;
    for(int j = i-1;j <= n; ++j){
      for(int k = 0;k < tr.sz; ++k){
        if(~g[j][k]){// 我为人人递推
          for(int x = j+1;x <= n; ++x)
            if(~f[j+1][x])
            up(g[x][k],g[j][k]+f[j+1][x]);
          int y = tr.ch[k][(int)ar[j+1]];
          // cout<<y<<endl;
          if(y != 0){
            up(g[j+1][y],g[j][k]);
            if(~tr.val[y]){
              // cout<<tr.val[y]<<endl;
              up(g[j+1][0],g[j][k]+tr.val[y]);
            }
          }
          if(k == 0)
            up(f[i][j],g[j][k]);
        }
      }
    }
   }


   // cout<<f[1][n]<<endl;
   for(int i = 1;i <= n; ++i){
     dp[i] = dp[i-1];
     for(int j = 1;j <= i; ++j)
      if(~f[j][i])
        up(dp[i],dp[j-1]+f[j][i]);
   }
   cout<<dp[n]<<endl;

  


  return 0;
}
