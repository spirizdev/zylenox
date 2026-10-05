#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using u64 = unsigned long long;
mt19937_64 make_rng(unsigned long long seed){
    if(seed==0) seed = chrono::high_resolution_clock::now().time_since_epoch().count();
    return mt19937_64(seed);
}
static inline u64 keypair(int a,int b){
    if (a > b) swap(a,b);
    return ((u64)(unsigned)a<<32) | (unsigned)b;
}
struct Config {
    int T=1;
    int n=10;
    int minn=2, maxn=100;
    long long m=-1;
    string mode="random";
    double p=0.1;
    int bip_left=-1;
    unsigned long long seed=0;
    bool simple=true;
    bool force_connected=true; // connectivity
    bool weighted=true; // weighted
    ll wmin = 1;
    ll wmax = 1000000000LL;
};
vector<pair<int,int>> all_edges(int n, bool directed, bool allow_self){
    vector<pair<int,int>> out;
    out.reserve((size_t)n * (size_t)n);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(!directed && j<=i) continue;
            if(!allow_self && i==j) continue;
            out.emplace_back(i,j);
        }
    }
    return out;
}
vector<pair<int,int>> sample_from_all(vector<pair<int,int>> v, mt19937_64 &rng, long long m){
    if((long long)v.size()<=m) return v;
    shuffle(v.begin(), v.end(), rng);
    v.resize((size_t)m);
    return v;
}
vector<pair<int,int>> sample_random(int n, bool directed, bool allow_self, long long m, mt19937_64 &rng){
    long long max_possible = directed ? 1LL*n*(n-1 + (allow_self?1:0)) : 1LL*n*(n-1)/2 + (allow_self? n:0);
    if(m > max_possible) m = max_possible;
    if(m * 3 >= max_possible){
        auto all = all_edges(n, directed, allow_self);
        return sample_from_all(move(all), rng, m);
    }
    unordered_set<u64> seen;
    vector<pair<int,int>> out; out.reserve((size_t)m);
    uniform_int_distribution<int> dn(1,n);
    while((long long)out.size() < m){
        int a = dn(rng), b = dn(rng);
        if(!allow_self && a==b) continue;
        int u=a, v=b;
        if(!directed){ if(u>v) swap(u,v); if(u==v) continue; }
        u64 k = keypair(u,v);
        if(seen.insert(k).second) out.emplace_back(u,v);
    }
    return out;
}
vector<pair<int,int>> gen_tree(int n, mt19937_64 &rng){
    vector<int> parent(n+1,0);
    for(int i=2;i<=n;i++){
        uniform_int_distribution<int> d(1,i-1);
        parent[i] = d(rng);
    }
    vector<pair<int,int>> edges;
    edges.reserve(max(0,n-1));
    for(int i=2;i<=n;i++) edges.emplace_back(parent[i], i);
    return edges;
}
vector<pair<int,int>> gen_unweighted(const Config &cfg, mt19937_64 &rng){
    int n = cfg.n;
    bool directed = true;
    bool allow_self = !cfg.simple;
    long long m = cfg.m;
    string mode = cfg.mode;
    if(mode=="tree"){
        if(n<=1) return {};
        return gen_tree(n, rng);
    }
    if(mode=="connected"){
        auto edges = gen_tree(n, rng);
        long long need = (m==-1) ? 0 : max(0LL, m - (long long)edges.size());
        if(need==0 && m==-1){
            uniform_int_distribution<int> ext(0, max(0, min(n,10)));
            need = ext(rng);
        }
        if(need>0){
            auto extras = sample_random(n, directed, allow_self, need, rng);
            unordered_set<u64> used; used.reserve(edges.size()*2+8);
            for(auto &e: edges){ int u=e.first, v=e.second; used.insert(keypair(u,v)); }
            for(auto &e: extras){
                int u=e.first, v=e.second;
                u64 k = keypair(u,v);
                if(used.insert(k).second) edges.emplace_back(u,v);
            }
        }
        return edges;
    }
    if(mode=="bipartite"){
        int L = cfg.bip_left <= 0 ? n/2 : cfg.bip_left;
        long long max_e = 1LL * L * (n-L);
        if(m==-1){
            uniform_int_distribution<int> mm(0, (int)min<long long>(max_e, max(1,n)));
            m = mm(rng);
        } else m = min<long long>(m, max_e);
        vector<pair<int,int>> all; all.reserve((size_t)max_e);
        for(int i=1;i<=L;i++) for(int j=L+1;j<=n;j++) all.emplace_back(i,j);
        if(m * 3 >= (long long)all.size()) { shuffle(all.begin(), all.end(), rng); all.resize((size_t)m); return all; }
        return sample_from_all(move(all), rng, m);
    }
    if(mode=="dag"){
        vector<int> order(n); for(int i=0;i<n;i++) order[i]=i+1;
        shuffle(order.begin(), order.end(), rng);
        long long max_e = 1LL*n*(n-1)/2;
        if(m==-1){ uniform_int_distribution<int> mm(0, max(1, n*(n-1)/4)); m = mm(rng); m = min<long long>(m, max_e); }
        else m = min<long long>(m, max_e);
        vector<pair<int,int>> all; all.reserve((size_t)max_e);
        for(int i=0;i<n;i++) for(int j=i+1;j<n;j++) all.emplace_back(order[i], order[j]);
        if(m * 3 >= (long long)all.size()){ shuffle(all.begin(), all.end(), rng); all.resize((size_t)m); return all; }
        return sample_from_all(move(all), rng, m);
    }
    long long max_possible = 1LL*n*(n-1 + (allow_self?1:0));
    if(mode=="dense" && m==-1){ uniform_int_distribution<long long> dm(max_possible/2, max_possible); m = dm(rng); }
    if(m==-1){
        double p = cfg.p;
        uniform_int_distribution<int> extra(0, max(1,n));
        long long expected = (long long)round(p * (double)max_possible);
        m = max(0LL, expected + extra(rng) - (extra(rng)/2));
        m = min<long long>(m, max_possible);
    }
    m = min<long long>(m, max_possible);
    if(cfg.simple){
        if(m * 3 >= max_possible){
            auto all = all_edges(n, directed, allow_self);
            shuffle(all.begin(), all.end(), rng);
            if((long long)all.size() > m) all.resize((size_t)m);
            return all;
        } else return sample_random(n, directed, allow_self, m, rng);
    } else {
        vector<pair<int,int>> out; out.reserve((size_t)m);
        uniform_int_distribution<int> dn(1,n);
        for(long long i=0;i<m;i++){
            int a=dn(rng), b=dn(rng);
            if(!allow_self && a==b){ --i; continue; }
            out.emplace_back(a,b);
        }
        return out;
    }
}
void ensure_weakly_connected(vector<pair<int,int>> &raw, const Config &cfg, mt19937_64 &rng){
    int n = cfg.n;
    vector<int> dsu(n+1);
    iota(dsu.begin(), dsu.end(), 0);
    function<int(int)> findp = [&](int x){ return dsu[x]==x ? x : dsu[x]=findp(dsu[x]); };
    auto unite = [&](int a, int b){
        a = findp(a); b = findp(b);
        if(a==b) return false;
        dsu[b]=a;
        return true;
    };
    unordered_set<u64> seen;
    seen.reserve(raw.size()*2 + 16);
    for(auto &e : raw){
        int u=e.first, v=e.second;
        u64 k = keypair(u,v);
        seen.insert(k);
        unite(u,v);
    }
    unordered_map<int, vector<int>> comp;
    comp.reserve(n);
    for(int i=1;i<=n;i++) comp[findp(i)].push_back(i);
    if(comp.size() <= 1) return;
    vector<int> reps;
    reps.reserve(comp.size());
    for(auto &kv : comp) reps.push_back(kv.first);
    shuffle(reps.begin(), reps.end(), rng);
    for(size_t idx=1; idx<reps.size(); ++idx){
        auto &A = comp[reps[idx-1]];
        auto &B = comp[reps[idx]];
        bool added = false;
        uniform_int_distribution<int> da(0, (int)A.size()-1);
        uniform_int_distribution<int> db(0, (int)B.size()-1);
        const int TRIES = 10;
        for(int t=0;t<TRIES && !added;t++){
            int u = A[da(rng)];
            int v = B[db(rng)];
            u64 k = keypair(u,v);
            if(seen.find(k) == seen.end()){
                raw.emplace_back(u, v);
                seen.insert(k);
                unite(u,v);
                A.insert(A.end(), B.begin(), B.end());
                added = true;
                break;
            }
        }
        if(added) continue;
        for(int aa : A){
            if(added) break;
            for(int bb : B){
                u64 k = keypair(aa, bb);
                if(seen.find(k) == seen.end()){
                    raw.emplace_back(aa, bb);
                    seen.insert(k);
                    unite(aa, bb);
                    A.insert(A.end(), B.begin(), B.end());
                    added = true;
                    break;
                }
            }
        }
        if(!added){
            A.insert(A.end(), B.begin(), B.end());
        }
    }
}
int main(int argc,char** argv){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    Config cfg;
    for(int i=1;i<argc;i++){
        string s=argv[i];
        if(s=="--T" && i+1<argc) cfg.T = stoi(argv[++i]);
        else if(s=="--n" && i+1<argc) cfg.n = stoi(argv[++i]);
        else if(s=="--minn" && i+1<argc) cfg.minn = stoi(argv[++i]);
        else if(s=="--maxn" && i+1<argc) cfg.maxn = stoi(argv[++i]);
        else if(s=="--m" && i+1<argc) cfg.m = stoll(argv[++i]);
        else if(s=="--mode" && i+1<argc) cfg.mode = argv[++i];
        else if(s=="--p" && i+1<argc) cfg.p = stod(argv[++i]);
        else if(s=="--bip-left" && i+1<argc) cfg.bip_left = stoi(argv[++i]);
        else if(s=="--seed" && i+1<argc) cfg.seed = stoull(argv[++i]);
        else if(s=="--no-simple") cfg.simple = false;
        else if(s=="--force-connected") cfg.force_connected = true;
        else if(s=="--weighted") cfg.weighted = true;
        else if(s=="--wmin" && i+1<argc) cfg.wmin = stoll(argv[++i]);
        else if(s=="--wmax" && i+1<argc) cfg.wmax = stoll(argv[++i]);
        else { cerr << "Unknown arg: " << s << '\n'; return 1; }
    }
    if(cfg.minn>0 && cfg.maxn < cfg.minn) cfg.maxn = cfg.minn;
    auto master = make_rng(cfg.seed);
//    cout << cfg.T << '\n';
    for(int tc=0; tc<cfg.T; ++tc){
        unsigned long long per = master();
        mt19937_64 rng(per);
        if(cfg.minn>=1){
            uniform_int_distribution<int> dn(cfg.minn, cfg.maxn);
            cfg.n = dn(rng);
        }
        if (cfg.mode == "random") {
            vector<string> modes = {
                "erdos", "tree", "connected", "bipartite", "dag", "dense"
            };
            uniform_int_distribution<int> pick(0, (int)modes.size() - 1);
            cfg.mode = modes[pick(rng)];
        }
        auto raw = gen_unweighted(cfg, rng);
        if(cfg.force_connected){
            ensure_weakly_connected(raw, cfg, rng);
        }
        cout << cfg.n << ' ' << (long long)raw.size() << '\n';
        if (!cfg.weighted) {
            for(auto &e: raw) cout << e.first << ' ' << e.second << '\n';
        } else {
            uniform_int_distribution<ll> wd(cfg.wmin, cfg.wmax);
            for(auto &e: raw) {
                ll w = wd(rng);
                cout << e.first << ' ' << e.second << ' ' << w << '\n';
            }
        }
    }
    return 0;
}
