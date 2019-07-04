// 堆的插入和删除操作

void Insert(int vv)
{
    int t = sz++;
    h[t] = vv;
    while(t > 1)
    {
        if(h[t] < h[t/2])
        {
            swap(h[t],h[t/2]);
            t /= 2;
        }
        else break;
    }
}
int Down(int i)
{
    int t;
    while(i * 2 <= n)
    {
        if(h[i] > h[2*i])
            t = 2*i;
        else
            t = i;
        if(i*2+1 <= n&&h[i*2+1] < h[t])
          t = i*2+1;
        if(i == t)
            break;
        swap(h[t],h[i]);
        i = t;
    }
}
