const int inf = 1e9;
struct HopcroftKarp {
    int n;
    vi l, r, d;
    vvi g;
    HopcroftKarp(int _n, int _m) {
        n = _n;
        int p = _n + _m + 1;
        g.resize(p);
        l.resize(p, 0);
        r.resize(p, 0);
        d.resize(p, 0);
    }
    void AddEdge(int u, int v) {
        g[u].pb(v + n);
    }
    bool bfs() {
        queue<int> q;
        rep(u, 1, n) {
            if (!l[u]) d[u] = 0, q.push(u);
            else d[u] = inf;
        }
        d[0] = inf;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            each(v, g[u]) {
                if (d[r[v]] == inf) {
                    d[r[v]] = d[u] + 1;
                    q.push(r[v]);
                }
            }
        }
        return d[0] != inf;
    }
    bool dfs(int u) {
        if (!u) return true;
        each(v, g[u]) {
            if (d[r[v]] == d[u] + 1 && dfs(r[v])) {
                l[u] = v;
                r[v] = u;
                return true;
            }
        }
        d[u] = inf;
        return false;
    }
    int MaxMatching() {
        int ans = 0;
        while (bfs()) {
            rep(u, 1, n) if (!l[u] && dfs(u)) ++ans;
        }
        return ans;
    }
};