#include <bits/stdc++.h>
using namespace std;
inline int getc() {
	static char buf[100000];
	static int l = 0, r = 0;
	if (l == r) {
		l = 0;
		r = fread(buf, 1, 100000, stdin);
	}
	return (l == r) ? EOF : buf[l++];
}

inline int read() {
	int f = 1, x = 0;
	char c = getc();
	while (c < '0' || c > '9') f = (c == '-' ? -1 : 1), c = getc();
	while (c >= '0' && c <= '9') x = x * 10 + (c ^ '0'), c = getc();
	return f * x;
}
const int N = 10000005;
struct Dke_t
{
    struct Node
    {
        int k,l,r;
    }node[N];
    int stk[N],top;
    int rt,nodecnt;
    void build(int *a,int n)
    {
        nodecnt=n;
        top=0;
        for (int i=1,lst;i<=n;++i)
        {
            lst=0;
            while (top && a[i]<node[stk[top]].k)
            {
                lst=stk[top];
                --top;
                if (top) node[stk[top]].r=stk[top+1];
            }
            node[i].l=lst;node[i].r=0;node[i].k=a[i];
            stk[++top]=i;
        }
        while (top)
        {
            --top;
            node[stk[top]].r=stk[top+1];
            rt=stk[top];
        }
    }
    void print()
    {
        for (int i=1;i<=nodecnt;++i) cout<<"i="<<i<<' '<<node[i].k<<' '<<node[i].l<<' '<<node[i].r<<endl;
    }
}dket;
int a[N];
int n;
int main()
{
    cin>>n;
    for (int i=1;i<=n;++i) a[i]=read();
    //for (int i=1;i<=n;++i) cin>>a[i];
    dket.build(a,n);
    //dket.print();
    long long ans1=0,ans2=0;
    for (int i=1;i<=n;++i) ans1^=1LL*i*(dket.node[i].l+1),ans2^=1LL*i*(dket.node[i].r+1);
    cout<<ans1<<' '<<ans2<<endl;
    return 0;
}
