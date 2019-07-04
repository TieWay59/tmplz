// 注意修改maxn 的值，要不然容易T
// 注意maxn值过大，栈可能会不够
const int maxn = 100;
int n;
struct Matrix{
	int n,m;
	Matrix(int nn = 1,int mm = 1):n(nn),m(mm){ memset(a,0,sizeof(a));};
	long long a[maxn][maxn];
};
// void print(const Matrix &a)
// {
// 	for(int i = 1;i <= a.n; ++i,cout<<endl)
// 	 for(int j= 1;j <= a.m; ++j)
// 	    cout<<a.a[i][j]<<" ";
// }
Matrix operator*(Matrix a,Matrix b)
{
	Matrix c(a.n,b.m);
	for(int i = 1;i <= a.n; ++i)
	{
		for(int j = 1;j <= b.m; ++j)
		{
			for(int k = 1;k <= a.m; ++k)
			{
				c.a[i][j] += a.a[i][k] * b.a[k][j];
				c.a[i][j] %= mod;
			}
		}
	}
//	print(c);
	return c;
}
