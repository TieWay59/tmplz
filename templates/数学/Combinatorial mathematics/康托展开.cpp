int cantor(int a[],int n){//cantor展开,n表示是n位的全排列，a[]表示全排列的数
    int ans=0,sum=0;
    for(int i=1;i<n;i++){
        for(int j=i+1;j<=n;j++)
            if(a[j]<a[i])
                sum++;
        ans+=sum*factorial[n-i];//累积
        sum=0;//计数器归零
    }
    return ans+1;
}


static const int FAC[] = {1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880};   // 阶乘
  
//康托展开逆运算
void decantor(int x, int n)
{
    vector<int> v;  // 存放当前可选数
    vector<int> a;  // 所求排列组合
    for(int i=1;i<=n;i++)
        v.push_back(i);
    for(int i=n;i>=1;i--)
    {
        int r = x % FAC[i-1];
        int t = x / FAC[i-1];
        x = r;
        sort(v.begin(),v.end());// 从小到大排序
        a.push_back(v[t]);      // 剩余数里第t+1个数为当前位
        v.erase(v.begin()+t);   // 移除选做当前位的数
    }
}

