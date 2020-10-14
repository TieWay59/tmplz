using cost_t = long long;   //beware of integer overflow
using node_t = int;
using edge_t = pair<node_t, cost_t>;
using pqnd_t = pair<cost_t, node_t>;

vector <vector<edge_t>> adj;

void dijkstra(int s, vector <cost_t> &d) {
    int n = adj.size();
    d.assign(n, INF);   // distance

    d[s] = 0;
    priority_queue <pqnd_t, vector<pqnd_t>, greater<pqnd_t>> q;
    q.emplace(0, s);

    node_t u, v;
    cost_t dis, len;
    while (!q.empty()) {
        dis = q.top().first;
        u = q.top().second;
        q.pop();
        if (dis > d[u]) // i.e. !=
            continue;

        for (auto edge : adj[u]) {
            v = edge.first;
            len = edge.second;
            if (d[u] + len < d[v]) {
                d[v] = d[u] + len;
                q.emplace(d[v], v);
            }
        }
    }
}

//  get path:

using cost_t = long long;   //beware of integer overflow
using node_t = int;
using edge_t = pair<node_t, cost_t>;
using pqnd_t = pair<cost_t, node_t>;

vector <vector<edge_t>> adj;
vector <cost_t> tag;

void dijkstra(int s, vector <cost_t> &d, vector <node_t> &p) {
    int n = adj.size();
    d.assign(n, INF);   // distance
    p.assign(n, -1);    // path-pre

    d[s] = 0;
    priority_queue <pqnd_t, vector<pqnd_t>, greater<pqnd_t>> q;
    q.emplace(0, s);

    node_t u, v;
    cost_t dis, len;
    while (!q.empty()) {
        dis = q.top().first;
        u = q.top().second;
        q.pop();
        if (dis > d[u]) // i.e. !=
            continue;

        for (auto edge : adj[u]) {
            v = edge.first;
            len = edge.second;
            if (d[u] + len + tag[v] < d[v]) {
                d[v] = d[u] + len + tag[v];
                p[v] = u;   //*
                q.emplace(d[v], v);
            }
        }
    }
}