/// Created by Zylenox
#pragma GCC optimize("Ofast,unroll-loops,fast-math,inline,no-stack-protector")
//#pragma GCC target("avx2,avx,fma,bmi,bmi2,popcnt,lzcnt,tune=native")
#include <bits/allocator.h>
#include <bits/stdc++.h>
#define Task "PRODUCE24"
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
int n, m, k, scc, a[N], comp[N], pref[N][35], indeg[N], dp[N][35];
vi adj[N], radj[N], val[N], dag[N], order;
bool vis[N];
void dfs(int u) {
    vis[u] = 1;
    for (int v : adj[u]) if (!vis[v]) dfs(v);
    order.pb(u);
}
void dfs2(int u) {
    comp[u] = scc;
    for (int v : radj[u])
        if (comp[v] == -1) dfs2(v);
}
Nyaa() {
    cin.tie(nullptr)->sync_with_stdio(false);
    if (fopen(Task".inp", "r")) {
        freopen(Task".inp", "r", stdin);
        freopen(Task".out", "w", stdout);
    }
    memset(comp, -1, sizeof comp);
    cin >> n >> m >> k;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    for (int i = 0, u, v; i < m; i++)
        cin >> u >> v,
        adj[u].pb(v),
        radj[v].pb(u);
    for (int i = 1; i <= n; i++) if (!vis[i]) dfs(i);
    for (int i = n - 1; i >= 0; i--)
        if (comp[order[i]] == -1)
            dfs2(order[i]), ++scc;
     for (int i = 1; i <= n; i++)
        val[comp[i]].pb(a[i]);
    for (int i = 0; i < scc; i++) {
        sort(all(val[i]), greater<int>());
        for (int j = 1; j <= min(k, sz(val[i])); j++)
            pref[i][j] = pref[i][j - 1] + val[i][j - 1];
        for (int j = sz(val[i]) + 1; j <= k; j++)
            pref[i][j] = pref[i][j - 1];
    }
    for (int u = 1; u <= n; u++)
        for (int v : adj[u])
            if (comp[u] != comp[v])
                dag[comp[u]].pb(comp[v]);
    for (int i = 0; i < scc; i++) {
        sort(all(dag[i]));
        dag[i].erase(unique(all(dag[i])), dag[i].end());
        for (int v : dag[i]) ++indeg[v];
    }
    for (int i = 0; i < scc; i++)
        for (int j = 0; j <= k; j++)
            dp[i][j] = pref[i][j];
    queue<int> q;
    for (int i = 0; i < scc; i++) if (!indeg[i]) q.push(i);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : dag[u]) {
            vi nxt(k + 1);
            for (int i = 0; i <= k; i++) nxt[i] = dp[v][i];
            for (int i = 0; i <= k; i++)
            for (int j = 0; i + j <= k; j++)
                cmax(nxt[i + j], dp[u][i] + pref[v][j]);
            for (int i = 0; i <= k; i++)
                dp[v][i] = nxt[i];
            if (--indeg[v] == 0) q.push(v);
        }
    }
    int ans = 0;
    for (int i = 0; i < scc; i++)
        for (int j = 0; j <= k; j++)
            cmax(ans, dp[i][j]);
    cout << ans << '\n';
    cerr << "\nTime elapsed: " << 1000.0 * clock() / CLOCKS_PER_SEC << " ms.\n";
    return 0;
}