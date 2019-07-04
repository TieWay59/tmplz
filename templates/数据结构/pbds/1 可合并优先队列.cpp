// pbds zoj2334 合并logn

#include<bits/stdc++.h>
#include<ext/pb_ds/priority_queue.hpp>

using namespace std;
using namespace __gnu_pbds;
typedef pair<int,int> P;
typedef __gnu_pbds::priority_queue<int> Heap;

const int maxn = 1e5+10;
Heap heap[maxn]; 

int F[maxn];

int Find(int x){
    return x == F[x]?x:F[x] = Find(F[x]);
}
int main(void){
    int N,M;
    while(cin>>N){
        for(int i = 1;i <= N; ++i){
            int a;
            scanf("%d",&a);
            heap[i].clear();
            heap[i].push(a);
            F[i] = i;

        }
        cin>>M;
        int a,b;
        for(int i = 1;i <= M; ++i){
            scanf("%d%d",&a,&b);
            int fa = Find(a);
            int fb = Find(b);
            if(fa == fb){
                puts("-1");
                continue;
            }
            // cout<<fa<<" "<<fb<<endl;
            F[fb] = fa;
            int t;
            t  = heap[fa].top(),heap[fa].pop(),t/=2,heap[fa].push(t);
            t  = heap[fb].top(),heap[fb].pop(),t/=2,heap[fb].push(t);
            heap[fa].join(heap[fb]);
            printf("%d\n",heap[fa].top());
        }
    }
    return 0;
}
