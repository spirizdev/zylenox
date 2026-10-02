const ll inf = 1e18;
struct edge {
    int u, v;
    ll c, f;
};
struct Flow {
    int n, s, t;
    vector<vi> a;
    vector<edge> e;
    vector<bool> visited;
    vi d, cur;
    ll max_cap = 0;
    Flow(int n, int s, int t) : n(n), s(s), t(t) {
        a.resize(n + 1);
        d.resize(n + 1);
        cur.resize(n + 1);
        visited.resize(n + 1);
    }
    void AddEdge(int u, int v, ll c) {
        a[u].pb(sz(e));
        e.pb({u, v, c, 0});
        a[v].pb(sz(e));
        e.pb({v, u, 0, 0});
        if (c > 0) cmax(max_cap, c);
    }
    bool bfs(ll lim) {
        queue<int> q;
        fill(all(d), -1);
        d[s] = 1;
        q.push(s);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int id : a[u]) {
                int v = e[id].v;
                if (d[v] == -1 && (e[id].c - e[id].f) >= lim) {
                    d[v] = d[u] + 1;
                    q.push(v);
                }
            }
        }
        return d[t] >= 0;
    }
    ll dfs(int u, ll f, ll lim) {
        if (f == 0) return 0;
        if (u == t) return f;
        for (; cur[u] < sz(a[u]); cur[u]++) {
            int id = a[u][cur[u]], v = e[id].v;
            if (d[v] != d[u] + 1) continue;
            ll rem = e[id].c - e[id].f;
            if (rem < lim) continue;
            ll delta = dfs(v, min(f, rem), lim);
            if (delta) {
                e[id].f += delta;
                e[id ^ 1].f -= delta;
                return delta;
            }
        }
        return 0;
    }
    ll MaxFlow() {
        ll f = 0;
        if (s == t) return 0;
        if (max_cap == 0) return 0;
        ll lim = 1;
        while (lim <= max_cap) lim <<= 1;
        lim >>= 1;
        for (; lim > 0; lim >>= 1) {
            while (bfs(lim)) {
                fill(all(cur), 0);
                ll delta = dfs(s, inf, lim);
                while (delta) {
                    f += delta;
                    delta = dfs(s, inf, lim);
                }
            }
        }
        return f;
    }
    void FindMinCut() {
        fill(all(visited), false);
        queue<int> q;
        q.push(s);
        visited[s] = true;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int id : a[u]) {
                int v = e[id].v;
                if (e[id].c > e[id].f && !visited[v]) {
                    visited[v] = true;
                    q.push(v);
                }
            }
        }
    }
};
