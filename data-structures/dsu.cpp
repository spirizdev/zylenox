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
