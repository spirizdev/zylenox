// ac rồi nhưng code này gọn nên lưu lại tham khảo
#include<bits/stdc++.h>
#define taskname "elecar"

using namespace std;

#define int long long

const int inf=1e18;

struct Point{
   int x, y, i;
   Point(int a=0, int b=0, int c=0): x(a), y(b), i(c){}
   bool operator<(const Point& a) const {
      return y==a.y?x<a.x:y>a.y;
   }
};

struct Edge{
   int u, v, w;
   Edge (int a=0, int b=0, int c=0): u(a), v(b), w(c){}
   bool operator<(const Edge &a) const {
      return w<a.w;
   }
};

vector<Edge> edges;

const int N=2e5+1;
Point a[N];
int idx[N];
int n;

void generate_edges(){
   iota(idx, idx+n+1, 0);
   for (int k=0; k<4; ++k){
      sort(idx+1, idx+n+1, [&](int i, int j){ return a[i].x-a[j].x<a[j].y-a[i].y; });
      map<int, int> mp;
      for (int ii=1; ii<=n; ++ii){
         int i=idx[ii];
         for (auto it=mp.lower_bound(-a[i].y); it!=mp.end(); it=mp.erase(it)){
            int j=it->second;
            if (a[i].y-a[j].y>a[i].x-a[j].x) break;
            edges.emplace_back(i, j, a[i].x-a[j].x+a[i].y-a[j].y);
         }
         mp.insert({-a[i].y, i});
      }
      for (int i=1; i<=n; ++i) if (k&1) a[i].x=-a[i].x; else swap(a[i].x, a[i].y);
   }
}

struct DisjointSetUnion{
   vector<int> lab;

   void init(int _n){
      lab.assign(_n+1, -1);
   }

   int find_set(int v){
      return lab[v]<0?v:lab[v]=find_set(lab[v]);
   }

   bool union_sets(int a, int b){
      a=find_set(a); b=find_set(b);
      if (a!=b){
         if (lab[a]>lab[b]) swap(a, b);
         lab[a]+=lab[b];
         lab[b]=a;
         return 1;
      }
      return 0;
   }
} dsu;

const int LG=18;
int q, dep[N];
pair<int, int> up[N][LG];
vector<Edge> g[N];

void dfs(int u){
   dep[u]=dep[up[u][0].first]+1;
   for (int k=1; k<LG; ++k) up[u][k]={up[up[u][k-1].first][k-1].first, max(up[u][k-1].second, up[up[u][k-1].first][k-1].second)};
   for (auto &e:g[u]){
      if (e.v!=up[u][0].first){
         up[e.v][0]={u, e.w};
         dfs(e.v);
      }
   }
}

int query(int u, int v){
   int ans=0;
   if (dep[u]!=dep[v]){
      if (dep[u]<dep[v]) swap(u, v);
      int d=dep[u]-dep[v];
      for (int k=0; k<LG; ++k) if (d>>k&1) ans=max(ans, up[u][k].second), u=up[u][k].first;
   }
   if (u==v) return ans;
   for (int k=LG-1; k>=0; --k) if (up[u][k].first!=up[v][k].first) ans=max({ans, up[u][k].second, up[v][k].second}), u=up[u][k].first, v=up[v][k].first;
   return max({ans, up[u][0].second, up[v][0].second});
}

int32_t main(){
   ios_base::sync_with_stdio(false);
   cin.tie(nullptr);
   freopen(taskname".inp", "r", stdin);
   freopen(taskname".out", "w", stdout);
   cin >> n >> q;
   for (int i=1; i<=n; ++i) cin >> a[i].x >> a[i].y, a[i].i=i;
   generate_edges();
   sort(edges.begin(), edges.end());
   dsu.init(n);
   for (auto &i:edges){
      if (dsu.union_sets(i.u, i.v)){
         g[i.u].emplace_back(i.u, i.v, i.w);
         g[i.v].emplace_back(i.v, i.u, i.w);
      }
   }
   dfs(1);
   while (q--){
      int u, v; cin >> u >> v;
      cout << query(u, v) << '\n';
   }
   return 0;
}




















//_za*mita_
#include <bits/stdc++.h>
#define PB push_back
#define F first
#define S second
#define all(x) x.begin(), x.end()
#define bit(x, i) ((x >> i) & 1)
#define il (node * 2)
#define ir (il + 1)
#define maxn 200005
#define ll long long
#define pii pair <int, int>
#define MOD 1000000007
#define Task "elecar"
using namespace std;
int n, q, cnt = 0;
ll INF = 1e10;
int base[maxn], lab[maxn], par[maxn][19];
ll f[maxn][19];
pair <int, ll> near[maxn][8];
vector <pair<int, ll>> a[maxn];

void DFS(int x, int y){
    for (auto [i, j]: a[x]){
        if (i == y) continue;
        base[i] = base[x] + 1;
        par[i][0] = x;
        f[i][0] = j;
        for (int t = 1; t <= 18; t ++){
            par[i][t] = par[par[i][t - 1]][t - 1];
            f[i][t] = max(f[i][t - 1], f[par[i][t - 1]][t - 1]);
        }
        DFS(i, x);
    }
}

ll lca(int x, int y){
    ll res = 0;
    int dis = abs(base[x] - base[y]);
    if (base[x] < base[y]) swap(x, y);
    for (int i = 0; i <= 18; i ++)
    if (bit(dis, i)){
        res = max(res, f[x][i]);
        x = par[x][i];
    }
    if (x == y) return res;
    for (int i = 18; i >= 0; i --)
    if (par[x][i] != par[y][i]){
        res = max({res, f[x][i], f[y][i]});
        x = par[x][i];
        y = par[y][i];
    }
    return max({res, f[x][0], f[y][0]});
}

int find_set(int u) {
    return lab[u] < 0 ? u : lab[u] = find_set(lab[u]);
}

bool union_set(int u, int v) {
    u = find_set(u);
    v = find_set(v);
    if (u == v) return false;
    if (-lab[u] < -lab[v]) swap(u, v);
    lab[u] += lab[v];
    lab[v] = u;
    return true;
}

struct ltm{
    ll x, y;
    int id;
    ll diff_yx() const { return y - x; }
    ll sum_xy() const { return x + y; }
    bool operator < (const ltm & T) const{
        if (y != T.y) return y > T.y;
        return x < T.x;
    }
} luu[maxn];
ll dis(ltm p, ltm q){
    return abs(p.x - q.x) + abs(p.y - q.y);
}
struct ltm1{
    int u, v;
    ll cost;
    bool operator < (const ltm1 & T) const{
        return (cost < T.cost);
    }
};
vector <ltm1> predict;
void rotate_90() {
    for (int i = 1; i <= n; i ++){
        int x = luu[i].x, y = luu[i].y;
        luu[i].x = -y;
        luu[i].y = x;
    }
}
void flip() {
    for (int i = 1; i <= n; i ++){
        luu[i].y = -luu[i].y;
    }
}

void solve(int l, int r, int type){
    if (l >= r) return;
    int mid = (l + r)/2;
    solve(l, mid, type);
    solve(mid + 1, r, type);

    vector<ltm> res;
    ltm MIN = {0, INF, -1};
    int it = l;

    for (int i = mid + 1; i <= r; i ++){
        ltm p = luu[i];
        while (it <= mid and luu[it].sum_xy() <= p.sum_xy()){
            if (MIN.diff_yx() > luu[it].diff_yx()) {
                MIN = luu[it];
            }
            res.PB(luu[it]);
            ++ it;
        }
        if (MIN.id != -1){
            ll val = dis(MIN, p);
            if (near[p.id][type].F == 0 || near[p.id][type].S > val)
                near[p.id][type] = {MIN.id, val};
        }
        res.PB(p);
    }
    for (int i = it; i <= mid; i ++)
        res.PB(luu[i]);
    it = l;
    for (auto i: res)
        luu[it ++] = i;
}
void prep(){
    for (int i = 0; i < 2; i ++){
        for (int j = 0; j < 4; j ++){
            sort(luu + 1, luu + n + 1);
            solve(1, n, cnt);
            rotate_90();
            cnt ++;
        }
        flip();
    }
    for (int i = 1; i <= n; i ++)
    for (int type = 0; type < cnt; type ++)
        if (near[i][type].F)
            predict.PB({i, near[i][type].F, near[i][type].S});
    sort(all(predict));
    for (auto [u, v, cost]: predict)
        if (union_set(u, v)){
            a[u].PB({v, cost});
            a[v].PB({u, cost});
        }
    DFS(1, 0);
}
signed main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    if(fopen(Task".inp", "r")) {
        freopen(Task".inp", "r", stdin);
        freopen(Task".out", "w", stdout);
    }
    cin >> n >> q;
    for (int i = 1; i <= n; i ++){
        lab[i] = -1;
        cin >> luu[i].x >> luu[i].y;
        luu[i].id = i;
    }
    prep();
    while (q --){
        int s, t;
        cin >> s >> t;
        cout << lca(s, t) << "\n";
    }
    return 0;
}
