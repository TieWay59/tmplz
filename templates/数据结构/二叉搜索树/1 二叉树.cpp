// 通过中序遍历和后序遍历建立二叉树
//https://vjudge.net/problem/UVA-548


#include<bits/stdc++.h>

using namespace std;
const int maxn = 1e5+10;
const int INF = 1e8;
int in_order[maxn],post_order[maxn],l[maxn],r[maxn];
int n;
int read_order(int *a)
{
    string s;
    if(!getline(cin,s)) return false;
    stringstream ss(s);
    n = 0;
    int v;
    while(ss >> v)
        a[n++] = v;
    return n > 0;
}
int build_tree(int L1,int R1,int L2,int R2)
{
    if(L1 > R1)
        return 0;
    int root = post_order[R2];
    int p = L1;
    while(in_order[p] != root)
        p++;
    int cnt = p-L1;
    l[root] = build_tree(L1,p-1,L2,L2+cnt-1);
    r[root] = build_tree(p+1,R1,L2+cnt,R2-1);
    return root;
}
int best,bestsum;
void dfs(int a,int b)
{
    if(!l[a] && !r[a])
    {
        b += a;
        if(bestsum > b||(bestsum == b&&best > a))
        {
            best = a;
            bestsum = b;
        }
    }
    if(l[a]) dfs(l[a],b+a);
    if(r[a]) dfs(r[a],b+a);
}


int main(void)
{
    while(read_order(in_order))
    {
        read_order(post_order);
        build_tree(0,n-1,0,n-1);
//        cout<<0<<endl;
        bestsum = INF;
        dfs(post_order[n-1],0);
        cout<<best<<endl;
    }

    return 0;
}
