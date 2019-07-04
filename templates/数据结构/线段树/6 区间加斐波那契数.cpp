//CodeForces 446C DZY Loves Fibonacci Numbers


#include <cstdio>

const int maxn=300000;
const long long mod=1e9+9;

struct fenv {
    long long tree[maxn+10];
    void add(int i, long long d) {
        for (;i<maxn+10;i|=(i+1)) tree[i]=tree[i]+d;
    }
    long long get(int i) {
        long long ans=0;
        for (;i>=0; i=(i&(i+1))-1) ans+=tree[i];
        return ans%mod;
    }
};

fenv t1, t2, t3;
long long fb[maxn+10], s[maxn+10];
int n, m, a, t, l, r;
char ss[20];

inline long long getfb(int i) {
    if (i>0) return fb[i];
    else if (i%2) return fb[-i];
    else return mod-fb[-i];
}

inline int geti() {
    char ch=getchar();
    while (ch<'0'||ch>'9') ch=getchar();
    int ans=0;
    while (ch>='0'&&ch<='9') ans=(ans*10+ch-'0'), ch=getchar();
    return ans;
}

inline void puti(int i) {
    int j=0;
    while (i) ss[j]=(i%10)+'0', j++, i/=10;
    for (j--; j>=0; j--) putchar(ss[j]);
    putchar('\n');
}

int main() {
    fb[1]=fb[2]=1;
    for (int i=3; i<maxn+10; i++) fb[i]=(fb[i-1]+fb[i-2])%mod;
    n=geti(), m=geti();
    for (int i=1, sum=0; i<=n; i++) a=geti(), sum=(sum+a)%mod, s[i]=sum;
    for (int i=0; i<m; i++) {
        t=geti(), l=geti(), r=geti();
        if (t==1) {
            long long c=getfb(2-l), d=getfb(3-l);
            t1.add(l, c);
            t2.add(l, d);
            t3.add(l, -1);
            t1.add(r, -c);
            t2.add(r, -d);
            t3.add(r, fb[r-l+3]);
        } else {
            puti((int) (((t3.get(r)+t1.get(r)*fb[r]+t2.get(r)*fb[r+1]-t3.get(l-1)-t1.get(l-1)*fb[l-1]-t2.get(l-1)*fb[l]+s[r]-s[l-1])%mod+mod)%mod));
        }
    }
    return 0;
}
// #include <bits/stdc++.h>
#define eps 1e-6
#define LL long long
#define pii pair<int, int>
#define pb push_back
#define mp make_pair
//#pragma comment(linker, "/STACK:1024000000,1024000000")
using namespace std;
 
const int MAXN = 1500000;
const int MOD = 1e9+9;
LL bas = 276601605;
LL q1 = 691504013;
LL q2 = 308495997;
LL mul1[MAXN], mul2[MAXN];
int c[MAXN];
LL s[MAXN];
 
struct Node {
	LL a, b, sum;
} node[MAXN];
int n, k;
 
void init(int m) {
	mul1[0] = mul2[0] = 1;
	for (int i = 1; i <= m; i++) {
		mul1[i] = mul1[i-1] * q1 % MOD;
		mul2[i] = mul2[i-1] * q2 % MOD;
	}
}
void build(int o, int l, int r) {
	node[o].a = node[o].b = node[o].sum = 0;
	if (l == r) return;
	int m = (l+r) >> 1;
	build(o<<1, l, m);
	build((o<<1)+1, m+1, r);
}
void push_down(int o, int l, int r) {
	LL aa = node[o].a, bb = node[o].b;
	if (!aa && !bb) return;
	int lc = o << 1, rc = (o<<1)|1, mid = (l+r) >> 1;
	int len1 = mid-l+1, len2 = r - mid;
	
	node[lc].a = (node[lc].a+aa) % MOD;
	node[lc].b = (node[lc].b+bb) % MOD;
 	node[lc].sum = (node[lc].sum+aa*(mul1[len1+2]-mul1[2])) % MOD;
 	node[lc].sum = (node[lc].sum-bb*(mul2[len1+2]-mul2[2])) % MOD;
 
 	node[rc].a = (node[rc].a+aa*mul1[len1]) % MOD;
 	node[rc].b = (node[rc].b+bb*mul2[len1]) % MOD;
 	node[rc].sum = (node[rc].sum + aa*mul1[len1]%MOD*(mul1[len2+2]-mul1[2])%MOD) % MOD;
 	node[rc].sum = (node[rc].sum - bb*mul2[len1]%MOD*(mul2[len2+2]-mul2[2])%MOD) % MOD;
 
 	node[o].a = node[o].b = 0;
}
void push_up(int o) {
	node[o].sum = (node[o<<1].sum+node[(o<<1)|1].sum) % MOD;
}
LL query(int o, int l, int r, int ql, int qr) {
	if (l == ql && r == qr)
		return node[o].sum;
	push_down(o, l, r);
	int mid = (l+r) >> 1;
	if (qr <= mid)
		return query(o<<1, l, mid, ql, qr);
	else if (ql > mid)
		return query((o<<1)|1, mid+1, r, ql, qr);
	else 
		return (query(o<<1, l, mid, ql, mid)+query((o<<1)|1, mid+1, r, mid+1, qr)) % MOD;
}
void update(int o, int l, int r, int ql, int qr, LL x, LL y) {
	if (l == ql && r == qr) {
		node[o].a = (node[o].a+x) % MOD;
		node[o].b = (node[o].b+y) % MOD;
		node[o].sum = (node[o].sum+x*(mul1[r-l+3]-mul1[2])) % MOD;
 		node[o].sum = (node[o].sum-y*(mul2[r-l+3]-mul2[2])) % MOD;
 		return;
	}
	push_down(o, l, r);
	int mid = (l+r) >> 1;
	if (qr <= mid)
		update(o<<1, l, mid, ql, qr, x, y);
	else if (ql > mid) 
		update((o<<1)|1, mid+1, r, ql, qr, x, y);
	else {
		int len = mid - ql + 1;
		update(o<<1, l, mid, ql, mid, x, y);
		update((o<<1)|1, mid+1, r, mid+1, qr, x*mul1[len]%MOD, y*mul2[len]%MOD);
	}
	push_up(o);
}
 
int main()
{
	//freopen("input.txt", "r", stdin);
	scanf("%d%d", &n, &k);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &c[i]);
		s[i] = s[i-1] + c[i];
	}
	init(301000);
	build(1, 1, n);
	for (int i = 1; i <= k; i++) {
		int op, l, r;
		scanf("%d%d%d", &op, &l, &r);
		if (op == 1) 
			update(1, 1, n, l, r, 1, 1);
		else {
			LL ans = (bas*query(1, 1, n, l, r)%MOD+s[r]-s[l-1]) % MOD;
			if (ans < 0) ans += MOD;
			printf("%I64d\n", ans);
		}
	}
	return 0;
}
 
