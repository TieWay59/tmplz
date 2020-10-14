/**
 *  @Source: myself
 *  @Author: Tieway59
 *  @Complexity: O(nklogn)
 *  @Description:
 *      g.addEdge(u, v, w);
 *      build graph & inverse_graph
 *
 *      g.AstarKSP(inv_g, s, t, kth, ... );
 *      return k-th shortest path length or -1
 *
 *      ! KSP might not be strictly longer than (k-1)SP
 *      ! it's MLE/TLE for large K
 *      ! be aware of int overflow
 *      ! the "cut" is one example for passing skip function.
 *      ! I know this code is too long,
 *        it'll be easier if wrote into single functions.
 *        Since you need two graphs, this graph class works out fine.
 *
 *  @Example:
 *
 *  @Verification:
 *      https://nanti.jisuanke.com/t/A1992 (input k)
 *      http://acm.hdu.edu.cn/showproblem.php?pid=6181 (k = 2)
 */

using node_t = int;
using cost_t = long long;
using pqnd_t = pair<cost_t, node_t>;

class Graph {
public:
    int nsize = 0;
    int esize = 0;

    struct Edge {
        node_t v;
        cost_t w;
        int nx;
    };

    vector<int> head;
    vector<Edge> edge;

    Graph() {}

    Graph(int n, int m) : nsize(n), esize(m) {
        head.assign(n, -1);
        edge.reserve(m);
    }

    // number from 0
    inline void addEdge(node_t u, node_t v, cost_t w) {
        edge.emplace_back((Edge) {v, w, head[u]});
        head[u] = edge.size() - 1;
    }

    static void dijkstra(const Graph &g, const node_t &s, vector<cost_t> &d);

    cost_t AstarKSP(const Graph &inv_g, node_t s, node_t t, int k, function<const bool(cost_t)> cut);
};

void Graph::dijkstra(const Graph &g, const node_t &s, vector<cost_t> &d) {
    d.assign(g.nsize, INF);
    d[s] = 0;

//    using pqnd_t = pair<cost_t, node_t>;
    priority_queue<pqnd_t, vector<pqnd_t>, greater<pqnd_t> > q;
    q.emplace(d[s], s);

    node_t u, v;
    cost_t w, du;
    while (!q.empty()) {
        du = q.top().first;
        u = q.top().second;
        q.pop();
        if (du > d[u])continue;
        for (int i = g.head[u]; i != -1; i = g.edge[i].nx) {
            v = g.edge[i].v;
            w = g.edge[i].w;
            if (du + w < d[v]) {
                d[v] = du + w;
                q.emplace(d[v], v);
            }
        }
    }
}

//O(nklogn) : beware of n-circle.
cost_t Graph::AstarKSP(const Graph &inv_g, node_t s, node_t t, int k,
                       function<const bool(cost_t)> cut) {
    vector<cost_t> dis_t;
    vector<int> vis(nsize, 0);
    Graph::dijkstra(inv_g, t, dis_t);

    // if(s==t) k++; when the node are not defined as a path.
    if (dis_t[s] == llINF)return -1;

    auto Astar = [&](pqnd_t x, pqnd_t y) -> bool {
        return x.first + dis_t[x.second] >
               y.first + dis_t[y.second];
    };
    // BFS-similar :
    node_t u = s;
    cost_t dis_s;
    priority_queue<pqnd_t, vector<pqnd_t>, decltype(Astar)> q(Astar);
    vis[u] = 1;
    q.emplace(0, u);
    while (!q.empty()) {
        dis_s = q.top().first;
        u = q.top().second;
        q.pop();

        if (u == t && vis[u] == k)return dis_s;

        for (int i = head[u]; i != -1; i = edge[i].nx) {
            node_t v = edge[i].v;
            cost_t w = edge[i].w;

            if (cut(dis_s + w))continue;
            if (cut(dis_s + w + dis_t[v]))continue;

            // below is a risky-but-worth skip, take care :
            // if k == 2, skip vis > k
            // else skip vis >= k
            // (proved practically not theoretically. )
            if (vis[v] >= max(3, k))continue;
            else vis[v]++;

            q.emplace(dis_s + w, v);
        }
    }
    return -1;
}


void solve(int kaseId = -1) {
    int n, m;
    node_t s, t, kth;
    cost_t limit = 0;

    const auto cut = [&](cost_t cost) -> bool {
        return cost > limit;
    };

    while (cin >> n >> m) {
        cin >> s >> t >> kth >> limit;
        s--, t--;
        Graph g(n, m);
        Graph inv_g(n, m);

        for (ll i = 1, u, v, w; i <= m; ++i) {
            cin >> u >> v >> w;
            u--, v--;
            g.addEdge(u, v, w);
            inv_g.addEdge(v, u, w);
        }
        cost_t res = g.AstarKSP(inv_g, s, t, kth, cut);
        if (res == -1 || cut(res))
            cout << "Whitesnake!" << endl;
        else
            cout << "yareyaredawa" << endl;
    }
}
