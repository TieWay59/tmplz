// UVA LA 5031
/*
给定n个节点m条边的无向图，每个节点都有一个整数权值。
D X 删除ID为x的边
Q X K 计算与节点X连通的节点中权值第k大的数
C X K 把节点X的权值改为V


*/


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
struct Node{
	Node *ch[2];// 左右子树
	int r;// 随机优先值
	int v; // 值
	int s;// 节点总数

	Node(int v):v(v){ch[0] = ch[1] = NULL; r = rand(); s = 1;}
	int cmp(int x) {
		if(x==v) return -1;
		return x < v?0:1;
	}

	void maintain(){
		s = 1;
		if(ch[0] != NULL) s += ch[0]->s;
		if(ch[1] != NULL) s += ch[1]->s;
	}
};

void rotate(Node * &o,int d){
	Node *k = o->ch[d^1]; o->ch[d^1] = k->ch[d]; k->ch[d] = o;
    o->maintain();k->maintain(); o  = k;

}

void insert(Node * &o,int x){
	if(o ==NULL) o = new Node(x);
	else{
		int d  =  (x < o->v?0:1);
		insert(o->ch[d],x);
		if(o->ch[d]->r > o->r) rotate(o,d^1);
	}
	o->maintain();
}
void remove(Node * &o,int x){
	int d = o->cmp(x);
	// int ret = 0;
	if(d == -1){
		Node *u = o;
		if(o->ch[0] != NULL && o->ch[1] != NULL){
			int d2 = (o->ch[0]->r > o->ch[1]->r?1:0);
			rotate(o,d2); remove(o->ch[d2],x);
		}
		else{
			if(o->ch[0] == NULL) o = o->ch[1]; 
			else o = o->ch[0];
			delete u;
		}
	} else 
	    remove(o->ch[d],x);
	if(o != NULL) o->maintain();
}
const int maxc = 5e5+10;
struct Command{
	char type;
	int x,p;

} commands[maxc];

const int maxn = 2e4+10;
const int maxm = 6e4+10;
int n,m,weight[maxn],from[maxm],to[maxm],removed[maxm];
// 并查集相关
int pa[maxn];
int findset(int x){ return pa[x] != x?pa[x] = findset(pa[x]) : x;}
// 名次数相关
Node *root[maxn];// Treap;
int kth(Node *o,int k){
	if(o == NULL|| k <= 0|| k > o->s) return 0;
	int s = (o->ch[1] == NULL?0:o->ch[1]->s);
	if(k == s+1) return o->v;
	else if(k <= s)  return kth(o->ch[1],k);
	else return kth(o->ch[0],k-s-1);
}
void mergeto(Node* &src,Node * &dest){
	if(src->ch[0] != NULL) mergeto(src->ch[0],dest);
	if(src->ch[1] != NULL) mergeto(src->ch[1],dest);
	insert(dest,src->v);
	delete src;
	src = NULL;
}
void removetree(Node *&x){
	if(x->ch[0] != NULL) removetree(x->ch[0]);
	if(x->ch[1] != NULL) removetree(x->ch[1]);
	delete x;
	x = NULL;
}

void add_edge(int x){
	int u = findset(from[x]), v = findset(to[x]);
	if(u != v){
		if(root[u]-> s < root[v] -> s){ pa[u] = v; mergeto(root[u],root[v]);}
		else {pa[v] = u; mergeto(root[v],root[u]);}
	}
}

int query_cnt;
long long query_tot;
void query(int x,int k){
	query_cnt++;
	query_tot += kth(root[findset(x)],k);

}

void change_weight(int x,int v){
	int u = findset(x);
	remove(root[u],weight[x]);
	insert(root[u],v);
	weight[x] = v;
}

int main(void){
	int kase = 0;
	while(scanf("%d%d",&n,&m) == 2&& n){
		rep(i,1,n+1) scanf("%d",&weight[i]);
		rep(i,1,m+1) scanf("%d%d",&from[i],&to[i]);
		me(removed);
		int c = 0;
		for(;;){
			char type;
			int x,p = 0,v = 0;
			scanf(" %c",&type);
			if(type == 'E') break;
			scanf("%d",&x);
			if(type == 'D') removed[x] = 1;
			if(type == 'Q') scanf("%d",&p);
			if(type == 'C') {
				scanf("%d",&v);
				p = weight[x];
				weight[x] = v;
			}
			commands[c++] = (Command){type,x,p};
		}
		rep(i,1,n+1) {
			pa[i] = i; if(root[i] != NULL) removetree(root[i]);
			root[i] = new Node(weight[i]);
		}
		rep(i,1,m+1) if(!removed[i]) add_edge(i);
		// 反向操作
		query_tot = query_cnt = 0;
		per(i,0,c){
			if(commands[i].type == 'D') add_edge(commands[i].x);
			if(commands[i].type == 'Q') query(commands[i].x,commands[i].p);
			if(commands[i].type == 'C') change_weight(commands[i].x,commands[i].p);
		}
		printf("Case %d: %.6lf\n", ++kase, query_tot / (double)query_cnt);
	}
}
