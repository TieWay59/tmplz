// 威佐夫博弈
// 两对石子，只能选择在一堆或者两堆石子里面取相同石子
// 打表发现规律,第k个必败点,a_k = b_k+k
// a_k = (1+sqrt(5))/2 *k ，判断就是直接下面的式子了
int main(void)
{
	int a,b;
	while(cin>>a>>b){
		if(a > b)
		  swap(a,b);
		int   c = floor((b-a)*((1.0+sqrt(5.0))/2.0));
		if(a == c)
			 cout<<0<<endl;
		else
			 cout<<1<<endl;
	}
   return 0;
}
