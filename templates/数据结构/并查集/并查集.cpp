//http://acm.hdu.edu.cn/showproblem.php?pid=1232

#include <iostream>
#include <cstdio>
#include <set>
#include <cstring>
using namespace std;
const int LEN = 1000+5;
int N,M;
int ar[LEN];
int Find(int x)//并查集之find 函数
{
    return x==ar[x]?x:ar[x]=Find(ar[x]);
}
int main()
{

    while(cin>>N&&N)
    {
        cin>>M;
        for(int i = 1;i <= N; ++i)
            ar[i] = i;
        while(M--)
        {
            int a,b;
           scanf("%d %d",&a,&b);
            if(Find(a)!=Find(b))//如果不在一个集合,合并
            {
                ar[Find(a)] = Find(b);
            }
        }
        int Count=0;
        for(int i = 1;i <= N; ++i)
            if(Find(ar[i]) == i)
             Count++;
        cout<<Count-1<<endl;

    }
    return 0;
}
