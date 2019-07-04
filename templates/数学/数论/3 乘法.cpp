string mul(string a,int b)
{
    string c;
    char s;
    int len=a.length();
    int ok=0;
    for(int i=len-1;i>=0;i--)
    {
        int temp=(a[i]-'0')*b+ok;
        ok=temp/10;
        s=temp%10+'0';
        c=s+c;
    }
    while(ok)
    {
        s=ok%10+'0';
        c=s+c;
        ok/=10;
    }
    return c;
}
