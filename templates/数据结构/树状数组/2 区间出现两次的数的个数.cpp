//......................................................离线树状数组
int n,m;
const int LEN = 2e5+100;
int tree[LEN];//树状数组
int ans[LEN];//答案数组
int ar[LEN];
int last[LEN];//last[i]上一个与ar[i]相等的元素的位置
map<int,int> ma;//存储每一个数对应的最后的位置
struct Q
{
    int l,r,ID;
};
Q q[LEN];
bool operator <(const Q &a,const Q &b)
{
    return a.r < b.r;
}
void modify(int x,int d)
{
    while(x <= n)
    {
        tree[x] += d;
        x += lowbit(x);
    }
}
int Query(int x)
{
    int sum = 0;
    while(x>0)
    {
        sum += tree[x];
        x -= lowbit(x);
    }
    return sum;
}

int main()
{

    cin>>n>>m;

    for(int i = 1; i <= n; ++i)
    {
        scanf("%d",&ar[i]);
        last[i] = ma[ar[i]];
        ma[ar[i]] = i;
    }
    for(int i = 1; i <= m; ++i)
    {
        scanf("%d %d",&q[i].l,&q[i].r);
        q[i].ID = i;
    }
    sort(q+1,q+m+1);
    int index = 1;
    /*树状数组的目的是进行快速求和, 我们可以假设求和的数组是C*/
    for(int i = 1; i <= n; ++i)
    {
        if(last[i]!=0)
        modify(last[i],1);//将上一个与这个元素相同的元素的位置+1,代表有一组
        int p = last[last[i]];
        if(p != 0)
        {
            modify(p,-2);/*如果有三个或者多个该元素,则需要-2,把+1抵消,并且把之前 p 和 last[i] 这个组合抵消*/
            int pp = last[p];
            if(pp != 0)//消除-2的影响
                modify(pp,1);
        }
        // 分析后得知C[i]只有三种可能的值,0,-1,1,


        while(index <= m&&q[index].r == i)
        {

            ans[q[index].ID] =   Query(i) - Query(q[index].l-1);/*这个时候Query(i)就代表从1到i有多少个恰好两次的不同数,Query(q[index].l-1)则不是*/
            index ++;
        }
    }
    for(int i = 1; i <= m; ++i)
        printf("%d\n",ans[i]);
    return 0;
}
