#include<bits/stdc++.h>

#define pb push_back
#define mp make_pair
#define fi first
#define se second

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;

template <typename T> bool chkmax(T &x,T y){return x<y?x=y,true:false;}
template <typename T> bool chkmin(T &x,T y){return x>y?x=y,true:false;}

int readint(){
    int x=0,f=1; char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}

const int cys=998244353;
int n,cnt,lst,tot;
ll ans=0;
int len[2000005],ch[2000005][26],tag[2000005],fa[2000005],v[2000005],nxt[2000005],h[2000005];
ll val[2000005],sum[2000005];
vector<pll> knd[2000005];
string s[100005];

ll mod(ll x){return x>=cys?x-cys:x;}
void addedge(int x,int y){v[++tot]=y; nxt[tot]=h[x]; h[x]=tot;}

void insert(int c){
    if(ch[lst][c]){
        int p=lst,q=ch[p][c];
        if(len[q]==len[p]+1){
            lst=q;
            return;
        }
        int nq=++cnt;
        len[nq]=len[p]+1;
        memcpy(ch[nq],ch[q],sizeof(ch[nq]));
        fa[nq]=fa[q],fa[q]=nq;
        for(;ch[p][c]==q;p=fa[p]) ch[p][c]=nq;
        lst=nq;
        return;
    }
    int p=lst,np=++cnt; lst=np,len[np]=len[p]+1;
    for(;p&&!ch[p][c];p=fa[p]) ch[p][c]=np;
    if(!p) return (void)(fa[np]=1);
    int q=ch[p][c];
    if(len[q]==len[p]+1) return (void)(fa[np]=q);
    int nq=++cnt;
    len[nq]=len[p]+1;
    memcpy(ch[nq],ch[q],sizeof(ch[nq]));
    fa[nq]=fa[q],fa[q]=fa[np]=nq;
    for(;ch[p][c]==q;p=fa[p]) ch[p][c]=nq;
}

void dfs1(int u){
    for(auto &r:knd[u]) r.se=mod(r.se+cys-val[r.fi]);
    for(auto r:knd[u]) val[r.fi]=mod(val[r.fi]+r.se);
    for(int p=h[u];p;p=nxt[p]) dfs1(v[p]);
    for(auto r:knd[u]) val[r.fi]=mod(val[r.fi]+cys-r.se);
}

void dfs2(int u){
    for(auto r:knd[u]) sum[u]=mod(sum[u]+r.se);
//  if(tag[u]) cout<<"test "<<sum[u]<<' '<<endl;
    ans=(ans+tag[u]*sum[u])%cys;
    for(int p=h[u];p;p=nxt[p]){
        sum[v[p]]=mod(sum[v[p]]+sum[u]);
        dfs2(v[p]);
    }
}

int main(){
    n=readint();
    for(int i=1;i<=n;i++) cin>>s[i];
    cnt=1;
    for(int i=1;i<=n;i++){
        int l=s[i].length();
        lst=1;
        for(int j=0;j<l;j++) insert(s[i][j]-'a');
    }
    for(int i=1;i<=n;i++){
        int l=s[i].length(),p=1;
        for(int j=0;j<l;j++){
            p=ch[p][s[i][j]-'a'];
            knd[p].pb(mp(i,1ll*(j+1)*(j+1)%cys));
        }
        tag[p]++;
    }
    for(int i=2;i<=cnt;i++) addedge(fa[i],i);
    dfs1(1);
    dfs2(1);
    printf("%lld\n",ans);
    return 0;
}
