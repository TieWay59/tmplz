/*
UVA 11922 
序列反转 (a,b) 


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
	Node *ch[2];
	int s;
	int flip;
	int v;
	int cmp(int k) const {
		int d = k-ch[0]->s;
		if(d == 1) return -1;
		return d <= 0?0:1;
	}
	void maintain(){
		s = ch[0]->s+ch[1]->s+1;
	}
	void pushdown(){
		if(flip){
			flip = 0;
			swap(ch[0],ch[1]);
			ch[0]->flip = !ch[0]->flip;
			ch[1]->flip = !ch[1]->flip;
		}
	}
};
Node *null = new Node();
void rotate(Node *&o,int d){
	Node *k = o->ch[d^1]; 
	o->ch[d^1] = k->ch[d];
	k->ch[d] = o;
	o->maintain(); k->maintain(); o = k;

}

void splay(Node * &o,int k){
	// cout<<1<<endl;
	o->pushdown();
	int d = o->cmp(k);
	if(d == 1) k -= o->ch[0]->s + 1;
	// DEBUG;
	if(d != -1){
		Node *p = o->ch[d];
		p->pushdown();
		int d2 = p->cmp(k);
		int k2 = (d2==0?k:k-p->ch[0]->s-1);
		// cout<<k2<<endl;
		if(d2 != -1){
			splay(p->ch[d2],k2);
			if(d == d2) rotate(o,d^1);
			else rotate(o->ch[d],d);
		}
		rotate(o,d^1);
	}
}
Node * Merge(Node *left,Node*right){
	splay(left,left->s);
	left->ch[1] = right;
	left->maintain();
	return left;
}

void split(Node *o,int k,Node * &left,Node *&right){
	splay(o,k);
	left = o;
	right = o->ch[1];
	o->ch[1] = null;
	left->maintain();
}
const int maxn = 1e5+10;
struct SplaySequence{
	int n;
	Node seq[maxn];
	Node *root;
	Node *build(int sz){
		if(!sz) return null;
		Node *L = build(sz/2);
		Node *o = &seq[++n];
		o->v = n;
		o->ch[0] = L;
		o->ch[1] = build(sz-sz/2-1);
		o->flip = o->s = 0;
		o->maintain();
		return o;
	}
	void init(int sz){
		n = 0;
		null->s = 0;
		root = build(sz);
	}
};
vector<int> ans;
void print(Node *o){
	if(o!=null){
		o->pushdown();
		print(o->ch[0]);
		ans.push_back(o->v);
		print(o->ch[1]);
	}
}
void debug(Node *o){
	if(o!=null){
		o->pushdown();
		debug(o->ch[0]);
		printf("%d ",o->v-1);
		debug(o->ch[1]);
	}
}
SplaySequence ss;
int main(void)
{
   int n,m;
   scanf("%d%d",&n,&m);
   // cout<<n<<" "<<m<<endl;
   ss.init(n+1);


   while(m--){
   	int a,b;
   	scanf("%d %d",&a,&b);
   	// cout<<a<<" "<<b<<endl;
   	Node *left,*mid,*right,*o;
   	split(ss.root,a,left,o);
   	// DEBUG;
   	split(o,b-a+1,mid,right);
   	mid->flip ^= 1;
   	ss.root = Merge(Merge(left,right),mid);
   }
   print(ss.root);
   for(int i = 1; i <ans.size(); i++) 
   	  printf("%d\n",ans[i]-1);
   return 0;
}
