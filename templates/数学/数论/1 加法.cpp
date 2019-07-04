string add(string a,string b)
{
    string c;
    int len1=a.length();
    int len2=b.length();
    int len=max(len1,len2);
    for(int i=len1;i<len;i++)
        a="0"+a;
    for(int i=len2;i<len;i++)
        b="0"+b;
    int ok=0;
    for(int i=len-1;i>=0;i--)
    {
        char temp=a[i]+b[i]-'0'+ok;
        if(temp>'9')
        {
            ok=1;
            temp-=10;
        }
        else ok=0;
        c=temp+c;
    }
    if(ok) c="1"+c;
    return c;
}
