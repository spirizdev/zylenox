struct edge {
    int u, v;
    ll c, f, cost;
};
struct MinCostMaxFlow {
    const ll inf = 1e18;
    int n, s, t;
    vector<vi> a;
    vector<edge> e;
    vector<ll> dist, potential;
    vi parent;
    MinCostMaxFlow(int n, int s, int t) : n(n), s(s), t(t) {
        a.resize(n + 1);
        dist.resize(n + 1);
        potential.resize(n + 1);
        parent.resize(n + 1);
    }
    void AddEdge(int u, int v, ll c, ll cost) {
        a[u].pb(sz(e));
        e.pb({u, v, c, 0, cost});
        a[v].pb(sz(e));
        e.pb({v, u, 0, 0, -cost});
    }
    bool Dijkstra() {
        priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<>> pq;
        fill(all(dist), inf);
        dist[s] = 0;
        pq.push({0, s});
        while (!pq.empty()) {
            auto [d, u] = pq.top(); pq.pop();
            if (d != dist[u]) continue;
            for (int id : a[u]) {
                int v = e[id].v;
                ll residual = e[id].c - e[id].f;
                ll cost = e[id].cost + potential[u] - potential[v];
                if (residual > 0 && dist[v] > dist[u] + cost) {
                    dist[v] = dist[u] + cost;
                    parent[v] = id;
                    pq.push({dist[v], v});
                }
            }
        }
        return dist[t] != inf;
    }
    pair<ll, ll> MCMF() {
        ll flow = 0, cost = 0;
        fill(all(potential), 0);
        while (Dijkstra()) {
            for (int i = 0; i <= n; i++)
                if (dist[i] < inf) potential[i] += dist[i];
            ll push = inf;
            for (int v = t; v != s; v = e[parent[v]].u)
                cmin(push, e[parent[v]].c - e[parent[v]].f);
            for (int v = t; v != s; v = e[parent[v]].u) {
                e[parent[v]].f += push;
                e[parent[v] ^ 1].f -= push;
                cost += push * e[parent[v]].cost;
            }
            flow += push;
        }
        return {flow, cost};
    }
};
void main(void) {
    int n; cin >> n;
    MinCostMaxFlow G(2 * n + 2, 0, 2 * n + 1);
    for (int i = 1; i <= n; i++) {
        G.AddEdge(0, i, 1, 0);
        for (int j = 1; j <= n; j++) {
            int cost; cin >> cost;
            G.AddEdge(i, n + j, 1, cost);
        }
        G.AddEdge(n + i, 2 * n + 1, 1, 0);
    }
    auto [flow, cost] = G.MCMF();
    cout << cost << '\n';
    for (auto &ed : G.e)
        if (ed.u >= 1 && ed.u <= n && ed.v >= n + 1 && ed.v <= 2 * n && ed.f > 0)
            cout << ed.u << ' ' << ed.v - n << '\n';
}
