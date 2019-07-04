string div(string a,int b)
{
    string c;
    int len=a.length();
    int ans=0;
    char s;
    for(int i=0;i<len;i++)
    {
        ans=ans*10+a[i]-'0';
        s=ans/b+'0';
        ans%=b;
        c+=s;
    }
    int pos=0;
    while(pos<len && c[pos]=='0') pos++;
    if(pos==len) return "0";
    return c.substr(pos);
}
