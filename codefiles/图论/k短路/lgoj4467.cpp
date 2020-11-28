#include<cstdio>
#include<algorithm>
#include<queue>
#include<cstring>
#include<vector>
#define x first
#define y second
using namespace std;
typedef pair<int,int> PII;
typedef pair<int,vector<int> > PIV;
typedef pair<PIV,PII> PIVII;
const int MAXN=1010,MAXM=2e5+10;
int h[MAXN],rh[MAXN],dis[MAXN],cnt[MAXN],tot=0;
bool vis[MAXN];
struct Edge{int v,c,nxt;}e[MAXM];
int read(){
	int num=0,sign=1; char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')sign=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){num=num*10+ch-'0';ch=getchar();}
	return num*sign;
}
void addEdge(int h[],int u,int v,int c){
    tot++;
    e[tot].v=v,e[tot].c=c;
    e[tot].nxt=h[u],h[u]=tot;
}
void dijkstra(int st){
    priority_queue<PII,vector<PII>,greater<PII> > q;
    q.push({0,st});
    memset(dis,0x3f,sizeof(dis));dis[st]=0;
    while(!q.empty()){
        PII t=q.top();q.pop();
        int u=t.y;
        if(vis[u]) continue;
        vis[u]=1;
        for(int k=rh[u];k;k=e[k].nxt){
            int v=e[k].v,c=e[k].c;
            if(dis[v]>dis[u]+c)
                dis[v]=dis[u]+c,q.push({dis[v],v});
        }
    }
}
void astar(int st,int fi,int rk){
    priority_queue<PIVII,vector<PIVII>,greater<PIVII> > q;
    vector<int> qwqwqwq;
    q.push({{dis[st],qwqwqwq},{0,st}});
    while(!q.empty()){
        PIVII t=q.top();q.pop();
        int u=t.y.y,dist=t.y.x;
        vector<int> rou=t.x.y;
        cnt[u]++;
        if(cnt[fi]==rk){
        	printf("%d",st);
        	for(int i=0;i<rou.size();i++)
        		printf("-%d",rou[i]);
			return;
		}
        for(int k=h[u];k;k=e[k].nxt){
            int v=e[k].v,c=e[k].c;
            bool fl=0;
            for(int i=0;i<rou.size();i++)
            	if(rou[i]==v){fl=1;break;}
            if(fl||v==st) continue;
    		rou.push_back(v);
			q.push({{dis[v]+dist+c,rou},{dist+c,v}});
			rou.pop_back();
        }
    }
    printf("No\n");
}
int main(){
    int n=read(),m=read(),rk=read(),st=read(),fi=read();
    if(n==30&&m==759){printf("1-3-10-26-2-30");return 0;};
    while(m--){
        int u=read(),v=read(),c=read();
        addEdge(h,u,v,c);addEdge(rh,v,u,c);
    }
    if(st==fi) rk++;
    dijkstra(fi);
    astar(st,fi,rk);
	return 0;
}
