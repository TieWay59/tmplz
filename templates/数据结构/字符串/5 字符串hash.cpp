// 字符串hash,查找在字符串中至少出现k次的最长字符串
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn  = 40000+10;
const int x = 123;
int n,m,pos;

unsigned long long H[maxn],xp[maxn];

unsigned long long Hash[maxn];
int Rank[maxn];

int cmp(const int &a,const int &b){
	return Hash[a] < Hash[b] ||(Hash[a] == Hash[b] &&a <b );
}

int possible(int L){
	int c = 0;
	pos = -1;
	for(int i = 0;i < n-L+1; ++i){
		Rank[i] = i;
		Hash[i] = H[i]-H[i+L]*xp[L];

	}
	sort(Rank,Rank+n-L+1,cmp);
	for(int i = 0;i < n-L+1; ++i){
		if(i == 0||Hash[Rank[i]] != Hash[Rank[i-1]]) c = 0;
		if(++c >= m) pos = max(pos,Rank[i]);
	}
	return pos >= 0;
}

char s[maxn];
int main(void)
{
    while((scanf("%d",&m)) == 1&&m){
        scanf("%s",s);
        n = strlen(s);
        H[n] = 0;
        for(int i = n-1;i >= 0; i--) H[i] = H[i+1]*x+(s[i]-'a');
        xp[0] = 1;
        for(int i = 1;i <= n; ++i) xp[i] = xp[i-1]*x;
        if(!possible(1)) printf("none\n");
    else{
    	int L = 1,R = n;
        while(R >= L){
        	int M = (R+L)/2;
        	if(possible(M)) L = M+1;
        	else R = M-1;
        }
        possible(R);
        printf("%d %d\n",R,pos);
       }
    }

   return 0;
}
