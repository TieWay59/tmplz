const int maxnode = 4e5+100;
const int sigma_size = 26;
struct Trie
{
    int ch[maxnode][sigma_size];
    int val[maxnode];
    int sz;
    Trie()
    {
        sz = 1;
        memset(ch[0],0,sizeof(ch[0]));
    }
    int idx(char c)
    {
        return c-'a';
    }
    void init(void)
    {
        memset(ch,0,sizeof(ch));
        memset(val,0,sizeof(val));
    }
    void insert(char *s,int v)
    {
        int u = 0, n = strlen(s);
        for(int i = 0; i < n; ++i)
        {
            int c = idx(s[i]);
            if(!ch[u][c])
            {
                memset(ch[sz],0,sizeof(ch[sz]));
                val[sz] = 0;
                ch[u][c] = sz++;
            }
            u = ch[u][c];
        }
        val[u] = v;
    }
    int query(char *s,int  t)
    {
        int sum = 0;
        int u = 0,n = strlen(s);
        for(int i =  0; i < n; ++i)
        {
            int c = idx(s[i]);
            if(ch[u][c])
            {
                if(val[ch[u][c]])
                    sum = (sum+ans[i+t+1]) % mod;
            }
            else
                return sum;
            u = ch[u][c];
        }
        return sum;
    }

};
