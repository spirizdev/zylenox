//_za*mita_
#include <bits/stdc++.h>
#define PB push_back
#define F first
#define S second
#define all(x) x.begin(), x.end()
#define bit(x, i) ((x >> i) & 1)
#define il (node * 2)
#define ir (il + 1)
#define mid (l + r)/2
#define maxn 400005
#define ll long long
#define pii pair <int, int>
#define MOD 1000000007
#define Task "poly"
#define int long long
using namespace std;
int n, m, use[21], vis[maxn], Cnt[maxn * 4], Tree[maxn * 4];
struct ndla{
    int x, y, id;
} a[21], b[21];
vector <int> luu[21], c, d;
vector <pair<pii, pii>> edge, e;
bool col(ndla p, ndla q){
    if (p.y != q.y) return p.y < q.y;
    return p.x < q.x;
}
bool row(ndla p, ndla q){
    if (p.x != q.x) return p.x < q.x;
    return p.y < q.y;
}
bool prio(int p, int q){
    return b[p].y < b[q].y;
}
void DFS(int u){
    use[u] = 1;
    sort(all(luu[u]), prio);
    for (int v: luu[u]){
        if (use[v]) continue;
        if (b[u].y == b[v].y){
            int y = b[u].y;
            int ux = b[u].x, vx = b[v].x;
            if (ux < vx) e.PB({{y, 1}, {ux, vx}});
            else e.PB({{y, -1}, {vx, ux}});
        }
        DFS(v);
    }
}
void Prep(){
    d.clear();
    e.clear();
    cin >> n;
    for (int i = 1; i <= n; i ++){
        int x, y, id = i;
        cin >> x >> y;
        a[i] = b[i] = {x, y, id};
        use[i] = 0;
        luu[i].clear();
        c.PB(x);
        d.PB(x);
    }
    sort(a + 1, a + n + 1, col);
    for (int i = 1; i <= n; i ++){
        int cur = i, pos = i;
        while (i < n && a[i + 1].y == a[cur].y){
            i ++;
            if (!pos) pos = i;
            else {
                luu[a[i].id].PB(a[pos].id);
                luu[a[pos].id].PB(a[i].id);
                pos = 0;
            }
        }
        if (pos){
            cout << -1;
            exit(0);
        }
    }
    sort(a + 1, a + n + 1, row);
    for (int i = 1; i <= n; i ++){
        int cur = i, pos = i;
        while (i < n && a[i + 1].x == a[cur].x){
            i ++;
            if (!pos) pos = i;
            else {
                luu[a[i].id].PB(a[pos].id);
                luu[a[pos].id].PB(a[i].id);
                pos = 0;
            }
        }
        if (pos){
            cout << -1;
            exit(0);
        }
    }
    DFS(a[1].id);
    sort(all(d));
    d.resize(unique(all(d)) - d.begin());
    sort(all(e));
    int last = -MOD, N = d.size() - 1, M = e.size() - 1;
    for (int i = 0; i <= N; i ++)
        vis[i] = 0;
    for (int i = 0; i <= M; i ++){
        if (last != -MOD){
            for (int j = 1; j <= N; j ++)
            if (vis[j]){
                int cur = j;
                while (j < N && vis[j + 1]) j ++;
                edge.PB({{last, 1},{d[cur - 1], d[j]}});
                edge.PB({{e[i].F.F, -1},{d[cur - 1], d[j]}});
//                cout << last << " " << e[i].F.F << " " << d[cur - 1] << " " << d[j] << "\n";
            }
        }
        last = e[i].F.F;
        int cur = i;
        for (int j = cur; j <= N && e[j].F.F == e[cur].F.F; j ++){
            i = j;
            int l = e[j].S.F, r = e[j].S.S, add = e[j].F.S;
            for (int t = 0; t <= N; t ++)
                if (d[t] > l && d[t] <= r)
                    vis[t] += add;
        }
    }
}
void Update(int node, int l, int r, int x, int y, int w){
    if (l > y || r < x || x > y) return;
    if (l >= x && r <= y){
        Cnt[node] += w;
        if (Cnt[node] <= 0) Tree[node] = Tree[il] + Tree[ir];
        else Tree[node] = c[r] - c[l - 1];
        return;
    }
    Update(il, l, mid, x, y, w);
    Update(ir, mid + 1, r, x, y, w);
    if (Cnt[node] <= 0) Tree[node] = Tree[il] + Tree[ir];
}
signed main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    if(fopen(Task".inp", "r")) {
        freopen(Task".inp", "r", stdin);
        freopen(Task".out", "w", stdout);
    }
    cin >> m;
    while (m --)
        Prep();
    sort (all(c));
    c.resize(unique(all(c)) - c.begin());
    m = c.size() - 1;
    sort(all(edge));
    int last = -MOD, ans = 0;
    for (int i = 0; i < edge.size(); i ++){
        edge[i].S.F = lower_bound(all(c), edge[i].S.F) - c.begin() + 1;
        edge[i].S.S = lower_bound(all(c), edge[i].S.S) - c.begin() + 1;
        if (last != -MOD) ans += (edge[i].F.F - last) * Tree[1];
        Update(1, 1, m, edge[i].S.F, edge[i].S.S - 1, edge[i].F.S);
        last = edge[i].F.F;
    }
    cout << ans;
    return 0;
}
