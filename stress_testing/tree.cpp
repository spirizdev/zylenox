#include <bits/stdc++.h>
using namespace std;
using ll = long long;
mt19937_64 make_rng(unsigned long long seed) {
    if (seed == 0) seed = chrono::high_resolution_clock::now().time_since_epoch().count();
    return mt19937_64(seed);
}
struct Edge { int u, v; ll w; };
void shuffle_labels(vector<Edge>& edges, mt19937_64 &rng, int n) {
    vector<int> perm(n+1);
    for (int i=1;i<=n;i++) perm[i]=i;
    shuffle(perm.begin()+1, perm.end(), rng);
    for (auto &e : edges) {
        e.u = perm[e.u];
        e.v = perm[e.v];
    }
}
void print_one_case(int n, const vector<Edge>& edges, bool weighted) {
    cout << n << '\n';
    if (!weighted) {
        for (auto &e : edges) cout << e.u << ' ' << e.v << '\n';
    } else {
        for (auto &e : edges) cout << e.u << ' ' << e.v << ' ' << e.w << '\n';
    }
}
vector<pair<int,int>> gen_chain(int n) {
    vector<pair<int,int>> E;
    for (int i=1;i<n;i++) E.emplace_back(i, i+1);
    return E;
}
vector<pair<int,int>> gen_star(int n) {
    vector<pair<int,int>> E;
    for (int i=2;i<=n;i++) E.emplace_back(1, i);
    return E;
}
vector<pair<int,int>> gen_kary(int n, int k) {
    vector<pair<int,int>> E;
    if (n<=1) return E;
    queue<int> q; q.push(1);
    int next = 2;
    while (!q.empty() && next <= n) {
        int u = q.front(); q.pop();
        for (int i=0;i<k && next<=n;i++) {
            E.emplace_back(u, next);
            q.push(next);
            next++;
        }
    }
    return E;
}
vector<pair<int,int>> gen_binary(int n) {
    return gen_kary(n, 2);
}
vector<pair<int,int>> gen_caterpillar(int n, mt19937_64 &rng) {
    vector<pair<int,int>> E;
    if (n<=1) return E;
    int spine = max(1, n/2);
    for (int i=1;i<spine;i++) E.emplace_back(i, i+1);
    int cur = spine + 1;
    uniform_int_distribution<int> dist(1, spine);
    while (cur <= n) {
        int attach = dist(rng);
        E.emplace_back(attach, cur);
        cur++;
    }
    return E;
}
vector<pair<int,int>> gen_almost_regular(int n, mt19937_64 &rng) {
    vector<pair<int,int>> E;
    if (n<=1) return E;
    deque<int> q; q.push_back(1);
    int next = 2;
    while (next <= n) {
        int u = q.front(); q.pop_front();
        int maxc = min(3, n - next + 1);
        uniform_int_distribution<int> dc(1, maxc);
        int take = dc(rng);
        for (int i=0;i<take && next<=n;i++) {
            E.emplace_back(u, next);
            q.push_back(next);
            next++;
        }
        q.push_back(u);
    }
    return E;
}
vector<pair<int,int>> gen_prufer(int n, mt19937_64 &rng) {
    vector<pair<int,int>> E;
    if (n==1) return E;
    if (n==2) { E.emplace_back(1,2); return E; }
    vector<int> prufer(n-2);
    uniform_int_distribution<int> dist(1, n);
    for (int i=0;i<n-2;i++) prufer[i] = dist(rng);
    vector<int> degree(n+1, 1);
    for (int x : prufer) degree[x]++;
    priority_queue<int, vector<int>, greater<int>> leaves;
    for (int i=1;i<=n;i++) if (degree[i]==1) leaves.push(i);
    for (int v : prufer) {
        int leaf = leaves.top(); leaves.pop();
        E.emplace_back(leaf, v);
        degree[leaf]--; degree[v]--;
        if (degree[v]==1) leaves.push(v);
    }
    int a = leaves.top(); leaves.pop();
    int b = leaves.top(); leaves.pop();
    E.emplace_back(a,b);
    return E;
}
struct Config {
    int T = 1;
    int minn = 2;
    int maxn = 100;
    unsigned long long seed = 0;
    bool shuffle = true;
    int kmax = 10;
    ll wmin = 1;
    ll wmax = 1000000000LL;
    bool weighted = false; // weighted
    vector<string> allowed_modes = {"prufer","chain","star","kary","binary","caterpillar","almost"};
};
int main(int argc, char** argv) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    Config cfg;
    for (int i=1;i<argc;i++) {
        string s = argv[i];
        if (s=="--T" && i+1<argc) cfg.T = stoi(argv[++i]);
        else if (s=="--minn" && i+1<argc) cfg.minn = stoi(argv[++i]);
        else if (s=="--maxn" && i+1<argc) cfg.maxn = stoi(argv[++i]);
        else if (s=="--seed" && i+1<argc) cfg.seed = stoull(argv[++i]);
        else if (s=="--no-shuffle") cfg.shuffle = false;
        else if (s=="--kmax" && i+1<argc) cfg.kmax = stoi(argv[++i]);
        else if (s=="--wmin" && i+1<argc) cfg.wmin = stoll(argv[++i]);
        else if (s=="--wmax" && i+1<argc) cfg.wmax = stoll(argv[++i]);
        else if (s=="--weighted") cfg.weighted = true;
        else if (s=="--unweighted") cfg.weighted = false;
        else if (s=="--modes" && i+1<argc) {
            string modes = argv[++i];
            cfg.allowed_modes.clear();
            string cur;
            for (char c : modes) {
                if (c==',') { if (!cur.empty()) { cfg.allowed_modes.push_back(cur); cur.clear(); } }
                else cur.push_back(c);
            }
            if (!cur.empty()) cfg.allowed_modes.push_back(cur);
        }
        else {
            cerr << "Unknown/incorrect arg: " << s << '\n';
            return 1;
        }
    }
    if (cfg.minn < 1) cfg.minn = 1;
    if (cfg.maxn < cfg.minn) cfg.maxn = cfg.minn;
    if (cfg.wmax < cfg.wmin) cfg.wmax = cfg.wmin;
    auto rng = make_rng(cfg.seed);
    uniform_int_distribution<int> dist_n(cfg.minn, cfg.maxn);
    uniform_int_distribution<int> dist_mode(0, (int)cfg.allowed_modes.size()-1);
//    cout << cfg.T << '\n';
    for (int tc=0; tc<cfg.T; ++tc) {
        int n = dist_n(rng);
        string mode = cfg.allowed_modes[dist_mode(rng)];
        vector<pair<int,int>> edges_unw;
        if (mode=="prufer") edges_unw = gen_prufer(n, rng);
        else if (mode=="chain") edges_unw = gen_chain(n);
        else if (mode=="star") edges_unw = gen_star(n);
        else if (mode=="kary") {
            int k_upper = min(max(2, cfg.kmax), max(2, n-1));
            uniform_int_distribution<int> dk(2, k_upper);
            int k = dk(rng);
            edges_unw = gen_kary(n, k);
        }
        else if (mode=="binary") edges_unw = gen_binary(n);
        else if (mode=="caterpillar") edges_unw = gen_caterpillar(n, rng);
        else if (mode=="almost") edges_unw = gen_almost_regular(n, rng);
        else edges_unw = gen_prufer(n, rng);
        vector<Edge> edges;
        uniform_int_distribution<long long> wd(cfg.wmin, cfg.wmax);
        for (auto &e : edges_unw) {
            ll w = cfg.weighted ? wd(rng) : 0;
            edges.push_back({e.first, e.second, w});
        }
        if (cfg.shuffle) shuffle_labels(edges, rng, n);
        print_one_case(n, edges, cfg.weighted);
    }
    return 0;
}
