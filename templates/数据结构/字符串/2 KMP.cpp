#include <bits/stdc++.h>
#define mem(ar,num) memset(ar,num,sizeof(ar))
#define me(ar) memset(ar,0,sizeof(ar))
#define lowbit(x) (x&(-x))
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
const int    prime = 999983;
const int    INF = 0x7FFFFFFF;
const LL     INFF =0x7FFFFFFFFFFFFFFF;
const double pi = acos(-1.0);
const double inf = 1e18;
const double eps = 1e-6;
const LL mod = 20071027 ;
int f[1100];
char ch[100];
void getFail(char *P,int *f)
{
    int m = strlen(P);
    f[0] = 0,f[1] = 0;
    for(int i = 1;i < m; ++i)
    {
        int j = f[i];
        while(j && P[i] != P[j]) j = f[j];
        f[i+1] = P[i] == P[j] ? j + 1: 0;

    }

}
void find(char * T,char * P,int* f)
{
    int n = strlen(T),m = strlen(P);
    getFail(P,f);
    int j = 0;
    for(int i =  0;i < n; ++i)
    {
        while(j&&P[j] != T[i]) j = f[j];
        if(P[j] == T[i]) j++;
        if(j == m) printf("%d\n",i-m+1);
    }
}

int main(void)
{
    cin>>ch;
    getFail(ch,f);
    printf("%d",f[strlen(ch)-1]);

    return 0;
}

