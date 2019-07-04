typedef vector<Point> Polygon;
double PolygonArea(Polygon poly)
{
    double area = 0;
    int n = poly.size();
    for(int i = 1; i < n-1; i++)
        area += Cross(poly[i]-poly[0], poly[(i+1)%n]-poly[0]);
    return area/2;
}

struct Edge
{
    int from, to; // 起点，终点，左边的面编号
    double ang;
    Edge(int f,int t,double a):from(f),to(t),ang(a) {}
};

const int maxn = 10000 + 10; // 最大边数

// 平面直线图（PSGL）实现
struct PSLG
{
    int n, m, face_cnt;//face_cnt 面数
    double x[maxn], y[maxn];
    vector<Edge> edges;//储存边
    vector<int> G[maxn];//指向边
    int vis[maxn*2];  // 每条边是否已经访问过
    int left[maxn*2]; // 左面的编号
    int prev[maxn*2]; // 相同起点的上一条边（即顺时针旋转碰到的下一条边）的编号

    vector<Polygon> faces;//faces 储存面
    double area[maxn]; // 每个polygon的面积

    void init(int n)
    {
        this->n = n;
        for(int i = 0; i < n; i++)
            G[i].clear();
        edges.clear();
        faces.clear();
    }

    // 有向线段from->to的极角
    double getAngle(int from, int to)
    {
        return atan2(y[to]-y[from], x[to]-x[from]);
    }

    void AddEdge(int from, int to)
    {
        edges.push_back((Edge){ from, to, getAngle(from, to)});
        edges.push_back((Edge){ to, from, getAngle(to, from)});
        m = edges.size();
        G[from].push_back(m-2);
        G[to].push_back(m-1);
    }

    // 找出faces并计算面积
    void Build()
    {
        for(int u = 0; u < n; u++)
        {
            // 给从u出发的各条边按极角排序
            int d = G[u].size();
            for(int i = 0; i < d; i++)
                for(int j = i+1; j < d; j++) // 这里偷个懒，假设从每个点出发的线段不会太多
                    if(edges[G[u][i]].ang > edges[G[u][j]].ang)
                        swap(G[u][i], G[u][j]);
            for(int i = 0; i < d; i++)
                prev[G[u][(i+1)%d]] = G[u][i];
        }

        memset(vis, 0, sizeof(vis));
        face_cnt = 0;
        for(int u = 0; u < n; u++)
            for(int i = 0; i < G[u].size(); i++)
            {
                int e = G[u][i];
                if(!vis[e])   // 逆时针找圈
                {
                    face_cnt++;
                    Polygon poly;
                    for(;;)
                    {
                        vis[e] = 1;
                        left[e] = face_cnt;
                        int from = edges[e].from;
                        poly.push_back(Point(x[from], y[from]));
                        e = prev[e^1];
                        if(e == G[u][i])
                            break;
                        assert(vis[e] == 0);
                    }
                    faces.push_back(poly);
                }
            }

        for(int i = 0; i < faces.size(); i++)
        {
            area[i] = PolygonArea(faces[i]);
        }
    }
};
