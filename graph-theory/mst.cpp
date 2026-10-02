struct DSU {
    vi lab;
    DSU() {}
    DSU(int n) : lab(n + 1, -1) {}
    int Find(int u) {
        return lab[u] < 0 ? u : lab[u] = Find(lab[u]);
    }
    bool same(int u, int v) {
        return Find(u) == Find(v);
    }
    bool Merge(int u, int v) {
        u = Find(u); v = Find(v);
        if (u == v) return false;
        if (lab[u] > lab[v]) swap(u, v);
        lab[u] += lab[v];
        lab[v] = u;
        return true;
    }
    int getSize(int u) {
        return -lab[Find(u)];
    }
};
struct Edge {
    int u, v, w;
    Edge() {}
    Edge(int _u, int _v, int _w) : u(_u), v(_v), w(_w) {}
    bool operator < (const Edge &other) const {
        return w < other.w;
    }
};
int kruskal(int n, vector<Edge> &edges) {
    sort(all(edges));
    DSU dsu(n);
    int cost = 0, used = 0;
    each(e, edges) {
        if (dsu.Merge(e.u, e.v)) {
            cost += e.w;
            used++;
            if (used == n - 1) break;
        }
    }
    assert(used == n - 1);
    return cost;
}
void main(void) {
    int n, m;
    cin >> n >> m;
    vector<Edge> edges;
    rep(i, 1, m) {
        int u, v, w;
        cin >> u >> v >> w;
        edges.eb(u, v, w);
    }
    cout << kruskal(n, edges) << '\n';
}
