struct DSU {
    struct Data { int a, b, sza, parb; };
    vector<Data> history;
    vi par, siz;
    int cnt;
    void make_set(int u) {
        par[u] = u;
        siz[u] = 1;
    }
    DSU() {}
    DSU(int n) : par(n + 1), siz(n + 1), cnt(n) {
        for(int i = 0; i <= n; i++) make_set(i);
    }
    void init(int n) {
        par.assign(n + 1, 0);
        siz.assign(n + 1, 0);
        cnt = n;
        history.clear();
        for(int i = 0; i <= n; i++) make_set(i);
    }
    int save() { return sz(history); }
    int Find(int u) { return par[u] == u ? u : Find(par[u]); }
    bool same(int u, int v) { return Find(u) == Find(v); }
    bool Merge(int u, int v) {
        u = Find(u); v = Find(v);
        if (u == v) return false;
        if (siz[u] < siz[v]) swap(u, v);
        history.pb({u, v, siz[u], par[v]});
        par[v] = u;
        siz[u] += siz[v];
        --cnt;
        return true;
    }
    void roll_back(int pos) {
        while (sz(history) > pos) {
            Data tmp = history.back(); history.pop_back();
            par[tmp.b] = tmp.parb;
            siz[tmp.a] = tmp.sza;
            ++cnt;
        }
    }
};
