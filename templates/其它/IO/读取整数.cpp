


//读取正负整数
inline int input(void)
{
    int num = 0;
    char c;
    int flag = 0;
    while((c = getchar()) < '0' || c > '9') flag = c=='-' ? 1:flag;
    while(c  >= '0' && c <= '9')
        num = num * 10 + c - '0',c = getchar();
    if(flag) num = -num;
    return num;
}
