void Add(int x,int p)//
{
    while(x<=N)
        {
            tree[x] += p;
            x += lowbit(x);
        }
}
int Query(int x)
{
    int sum = 0;
    while(x)
    {
        sum += tree[x];
        x -= lowbit(x);
    }
    return sum;
}
