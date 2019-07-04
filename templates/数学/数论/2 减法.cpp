string sub(string a,string b)
{
    string c;
    bool ok=0;
    int len1=a.length();
    int len2=b.length();
    int len=max(len1,len2);
    for(int i=len1;i<len;i++)
        a="0"+a;
    for(int i=len2;i<len;i++)
        b="0"+b;
    if(a<b)
    {
        string temp=a;
        a=b;
        b=temp;
        ok=1;
    }
    for(int i=len-1;i>=0;i--)
    {
        if(a[i]<b[i]) 
        {
            a[i-1]-=1;
            a[i]+=10;
        }
        char temp=a[i]-b[i]+'0';
        c=temp+c;
    }
    int pos=0;
    while(c[pos]=='0' && pos<len) pos++;
    if(pos==len) return "0"; 
    if(ok) return "-"+c.substr(pos);
    return c.substr(pos);
}
