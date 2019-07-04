

// 对于y = a*x+b; 这n个不同的直线，查询在某个点的最大的y值

// 每一个节点存的是当前节点取最大值的线段的ID// 查询的时候从根到子节点都查询值，取其中的最大值
// 插入点的时候
// 更新节点的规则就是如果插入直线比当前直线更优，那么说明原本直线对某区间的最优答案没有贡献，这个时候它就可以舍弃
// 共有四种情况
// 插入直线的斜率大于节点存的斜率，
//如果插入直线的值比原来的节点直线在这个地方的值大，当前值更新为插入直线，用原来节点值更新l,mid
//如果插入直线的值小，那么用插入直线更新mid+1，r;
// 如果插入直线的斜率小于节点存的斜率
// 如果插入直线的值比原来的节点直线在这个地方的值大，当前值更新为插入直线，用原来节点值更新mid+1,r
// 如果插入直线的值小，那么用插入直线更新l，mid+1;


#include <bits/stdc++.h>
using namespace std;
const int N = 5e5+10;
int n,m,tree[N*4];
double a[N*2],b[N*2];
int cmp(int x,int y,int pos){
	return a[x] + (pos-1)*b[x] > a[y] +(pos-1)*b[y];
}
void update(int o,int l,int r,int x){
	if(l == r){
		if(cmp(x,tree[o],l))
			 tree[o] = x;
	    return ;
	}
	int mid = (l+r)/2;
	if(b[x] > b[tree[o]]){
	    if(cmp(x,tree[o],mid)){
	        update(o<<1,l,mid,tree[o]),tree[o] = x;
	    }
	    else
	    	update(o<<1|1,mid+1,r,x);
	}
	if(b[x] < b[tree[o]]){
		if(cmp(x,tree[o],mid)){
               update(o<<1|1,mid+1,r,tree[o]),tree[o] = x;
		}
		else
			  update(o<<1,l,mid,x);
	}

}
double cal(int k,int x){
	return a[k] + (x-1)*b[k];
}
double query(int o,int l,int r,int x){
	if(l==r) return cal(tree[o],x);
	int mid = (l+r)/2;
	double ans = cal(tree[o],x);
	if(x <= mid) ans = max(ans,query(o<<1,l,mid,x));
	else
		ans = max(ans,query(o<<1|1,mid+1,r,x));
	return ans;
}
int main(void)
{
	scanf("%d",&n);
	for(int i = 1;i <=n; ++i){
		char s[20];
		scanf("%s",s);
		if(s[0] == 'P'){
			m++;
			scanf("%lf%lf",&a[m],&b[m]);
			update(1,1,N,m);
		}
		else{
			int x;
			scanf("%d",&x);
			double t = query(1,1,N,x);
			int k = t;
			printf("%d\n",k/100);
		}
	}
    

   return 0;
}
