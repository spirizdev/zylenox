/// Created by Zylenox
#pragma GCC optimize("Ofast,unroll-loops,fast-math,inline,no-stack-protector")
//#pragma GCC target("avx2,avx,fma,bmi,bmi2,popcnt,lzcnt,tune=native")
#include <bits/allocator.h>
#include <bits/stdc++.h>
#define Task "task"
#define Nyaa main
#define fi first
#define se second
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define bit(i, x) (((x) >> (i)) & 1)
#define sz(x) (int)(x).size()
#define ntest int t; cin >> t; while (t--) solve()
#define __lcm(a, b) (1ll * ((a) / __gcd((a), (b))) * (b))
#define yes cout << "yes\n"
#define no cout << "no\n"
#define int ll
using namespace std;
typedef long long ll;
typedef long double db;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<pii> vii;
typedef vector<pll> vll;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
template <class X, class Y>
bool cmax(X &x, const Y &y) {
    return x < y ? x = y, true : false;
}
template <class X, class Y>
bool cmin(X &x, const Y &y) {
    return x > y ? x = y, true : false;
}
const int inf = 0x3f3f3f3f3f3f3f3f;
const int N = 1e5 + 10;
int n, m, a[N];
vi adj[N], radj[N], adj2[N];
pii edges[N];
namespace owo {
    void main(void) {
        vi dist(n + 1, inf);
        priority_queue<pii, vii, greater<pii>> pq;
        dist[1] = a[1];
        pq.emplace(dist[1], 1);
        while (!pq.empty()) {
            auto [d, u] = pq.top();
            pq.pop();
            if (d > dist[u]) continue;
            for (int v : adj[u])
                if (cmin(dist[v], dist[u] + a[v]))
                    pq.emplace(dist[v], v);
        }
        cout << (dist[n] == inf ? -1 : dist[n]) << '\n';
    }
}
namespace uwu {
    int comp[N], vis[N], scc = 0;
    int cw[N], indeg[N], dp[N];
    vi order;
    void dfs1(int u) {
        vis[u] = true;
        for (int v : adj[u])
            if (!vis[v]) dfs1(v);
        order.pb(u);
    }
    void dfs2(int u) {
        comp[u] = scc;
        for (int v : radj[u])
            if (comp[v] == -1) dfs2(v);
    }
    void main(void) {
        memset(comp, -1, sizeof comp);
        memset(dp, -0x3f, sizeof dp);
        for (int i = 1; i <= n; i++)
            if (!vis[i]) dfs1(i);
        for (int i = sz(order) - 1; i >= 0; i--)
            if (comp[order[i]] == -1)
                dfs2(order[i]), ++scc;
        for (int i = 1; i <= n; i++)
            cw[comp[i]] += a[i];
        for (int i = 0; i < m; i++) {
            auto [u, v] = edges[i];
            if (comp[u] != comp[v])
                adj2[comp[u]].pb(comp[v]),
                ++indeg[comp[v]];
        }
        int s = comp[1], t = comp[n];
        dp[s] = cw[s];
        queue<int> q;
        for (int i = 0; i < scc; i++)
            if (indeg[i] == 0) q.push(i);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int v : adj2[u]) {
                if (dp[u] != -inf) cmax(dp[v], dp[u] + cw[v]);
                if (--indeg[v] == 0) q.push(v);
            }
        }
        cout << (dp[t] < 0 ? -1 : dp[t]) << '\n';
    }
}
Nyaa() {
    cin.tie(nullptr)->sync_with_stdio(false);
    if (fopen(Task".inp", "r")) {
        freopen(Task".inp", "r", stdin);
        //freopen(Task".out", "w", stdout);
    }
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    for (int i = 0, u, v; i < m; i++)
        cin >> u >> v,
        adj[u].pb(v),
        radj[v].pb(u),
        edges[i] = {u, v};
    vector<bool> vis(n + 1, false);
    vis[1] = true;
    queue<int> q;
    q.push(1);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : adj[u]) if (!vis[v])
            vis[v]=true, q.push(v);
    }
    if (!vis[n]) return cout << "-1\n", 0;
    owo::main();
    uwu::main();
    cerr << "\nTime elapsed: " << 1000.0 * clock() / CLOCKS_PER_SEC << " ms.\n";
    return 0;
}