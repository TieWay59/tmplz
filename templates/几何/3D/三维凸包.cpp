struct Face{
    int v[3];
    Vector3 normal(Vector *P)
    {
        return Cross(P[v[1]]-P[v[0]],P[v[2]]-P[v[0]]);
    }
    int cansee(Point *P,int i)const
    {
        return Dot(P[i]-P[v[0]],normal(P)) > 0?1 : 0;
    }
};
vector <Face> CH3D(Point3* P,int n)
{
    vector <Face> cur;
    cur.push_back((Face){{0,1,2}});
    cur.push_back((Face){{2,1,0}});
    for(int i = 3;i < n; ++i)
    {
        vector<Face> next;
        //计算每条边“左面”的可见性
        for(int j= 0;j < cur.size(); ++j)
        {
            Face &f = cur[j];
            int res = f.cansee(P,i);
            if(!res) next.push_back(f);
            for(int k = 0;k < 3; ++k)
                vis[f.v[k]][f.v[(k+1)%3]] = res;
        }
        for(int j = 0;j < cur.size(); ++j)
        {
            for(int k = 0;k < 3; ++k)
            {
                int a  = cur[j].v[k],b = cur[j].v[(k+1)%3];
                if(vis[a][b] != vis[b][a]&&vis[a][b])//(a,b) 是分界线，左边对P[i] 可见
                 next.push_back((Face){{a,b,i}});
            }
        }
        cnr = next;
    }
    return cur;
}
double rand01() {return rand() / (double) RAND_MAX;}//0-1 的随机数
double randeps() {return (rand01()-0.5) * eps;}
Point3 add_noise(Point3 p)
{
    return Point3(p.x + randeps(),p.y+randeps(),p.z+randeps());
}

//....................................................................
struct Face{
    int v[3];
    Vector3 normal(Vector *P)
    {
        return Cross(P[v[1]]-P[v[0]],P[v[2]]-P[v[0]]);
    }
    int cansee(Point *P,int i)const
    {
        return Dot(P[i]-P[v[0]],normal(P)) > 0?1 : 0;
    }
};
vector <Face> CH3D(Point3* P,int n)
{
    vector <Face> cur;
    cur.push_back((Face){{0,1,2}});
    cur.push_back((Face){{2,1,0}});
    for(int i = 3;i < n; ++i)
    {
        vector<Face> next;
        //计算每条边“左面”的可见性
        for(int j= 0;j < cur.size(); ++j)
        {
            Face &f = cur[j];
            int res = f.cansee(P,i);
            if(!res) next.push_back(f);
            for(int k = 0;k < 3; ++k)
                vis[f.v[k]][f.v[(k+1)%3]] = res;
        }
        for(int j = 0;j < cur.size(); ++j)
        {
            for(int k = 0;k < 3; ++k)
            {
                int a  = cur[j].v[k],b = cur[j].v[(k+1)%3];
                if(vis[a][b] != vis[b][a]&&vis[a][b])//(a,b) 是分界线，左边对P[i] 可见
                 next.push_back((Face){{a,b,i}});
            }
        }
        cnr = next;
    }
    return cur;
}
double rand01() {return rand() / (double) RAND_MAX;}//0-1 的随机数
double randeps() {return (rand01()-0.5) * eps;}
Point3 add_noise(Point3 p)
{
    return Point3(p.x + randeps(),p.y+randeps(),p.z+randeps());
}
