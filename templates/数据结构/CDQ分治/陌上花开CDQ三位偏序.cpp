#include <cstdio>
#include <algorithm>
#include <iostream>
using namespace std;
 
const int N = 200005;
int w,q,c[500005];
struct nd {int op,x1,y1,x2,y2,z,id,ans;}a[N],b[N];
bool cmp(const nd &a, const nd &b) {return a.x1<b.x1 || (a.x1==b.x1&&a.op<b.op);}
 
int lowbit(int x) {return x & -x;}
void Add(int x, int y) {while(x <= w) c[x] += y, x += lowbit(x);}
int Sum(int x) {
    int r = 0;
    while(x) r += c[x], x -= lowbit(x);
    return r;
}
struct node{
  int x,y,z,id,num;
}Node[N],Node2[N];
bool operator<(const node &a,const node &b){
   return a.z < b.z||(a.z == b.z &&a.y < b.y)||(a.z == b.z && a.y == b.y&&a.x < b.x);
}
bool operator ==(const node &a,const node&b){
   return a.x == b.x && a.y == b.y&&a.z == b.z;
}
void CDQ(int l, int r) {
    if(l == r) return;

    // printf("%d %d\n",l,r);
    int m = (l+r) >> 1, cnt = 0;
    CDQ(l,m),CDQ(m+1,r);
    for(int i = l; i <= m; i++) if(a[i].op == 1) b[cnt++] = a[i];
    for(int i = m+1; i <= r; i++) if(a[i].op == 2) {
        b[cnt++] = a[i];
        b[cnt++] = a[i];
        b[cnt-2].x1--, b[cnt-1].x1=a[i].x2,
        b[cnt-1].op = 3;
    }
    sort(b, b+cnt, cmp);
    for(int i = 0; i < cnt; i++)
    if(b[i].op == 1) Add(b[i].y1, b[i].z);
    else if(b[i].op == 2) a[b[i].id].ans -= Sum(b[i].y2)-Sum(b[i].y1-1);
    else a[b[i].id].ans += Sum(b[i].y2)-Sum(b[i].y1-1);
    for(int i = 0; i < cnt; i++)
    if(b[i].op == 1) Add(b[i].y1, -b[i].z);
}
int ans[N];
int main() {
//     freopen("locust.in","r",stdin);
//     freopen("locust.out","w",stdout);
    scanf("%d%d",&q,&w);
    for(int i = 1;i <= q; ++i)
      scanf("%d%d%d",&Node2[i].x,&Node2[i].y,&Node2[i].z),Node2[i].id = i;
    // DEBUG;
    // cout<<"1"<<endl;
    int qq = q;
    sort(Node2+1,Node2+q+1);
    int cnt = 1;
    Node[cnt] = Node2[1];
    Node[cnt].num = 1;
    for(int i = 2;i <= q; ++i){
      if(Node2[i] == Node2[i-1]) 
          Node[cnt].num++;
      else
        Node[++cnt] = Node2[i],Node[cnt].num = 1;

    }
    q = cnt;

    for(int i = 1; i <= q; i++) {
        Node[i].id = i;
        a[2*i-1].op = 2; a[2*i-1].x1 = 1,a[2*i-1].y1 = 1,a[2*i-1].x2 = Node[i].x,a[2*i-1].y2 = Node[i].y;
        a[2*i].op = 1;a[2*i].x1 = Node[i].x,a[2*i].y1 = Node[i].y,a[2*i].z = Node[i].num;
        
        a[2*i-1].id = a[2*i].id =Node[i].id;
    }
    // puts("DEBUG");
    CDQ(1, 2*q);

    for(int i = 1; i <= q; i++) ans[a[i].ans+Node[i].num-1] += Node[i].num;
      // cout<<endl;
    // for(int i = 1;i <= q; ++i) cout<<a[i].ans<<endl;
    // cout<<endl;
    for(int i = 0; i < qq; ++i) printf("%d\n",ans[i]);
    return 0;
}
