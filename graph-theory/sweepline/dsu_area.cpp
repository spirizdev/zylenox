// TrungNotChung
#include <bits/stdc++.h>
#define pii pair<int, int>
#define fi first
#define se second
#define BIT(x, i) (1 & ((x) >> (i)))
#define MASK(x) (1LL << (x))
#define CNT(x) __builtin_popcountll(x)
#define task "area"
 
using namespace std;
const int N = (int)2e5 + 228;
const int INF =  (int)1e9 + 7;

struct Point {
    int x, y;
};

struct Segment {
    Point p1, p2;
};

struct Event {
    int x, l, r, tp, id;
    Event(int _x = 0, int _l = 0, int _r = 0, int _tp = 0) {
        x = _x, l = _l, r = _r, tp = _tp;
    }
    bool operator < (const Event& other) const {
        return (x == other.x ? tp < other.tp : x < other.x);
    }
}e[N];

int len[N];

namespace Area {
    struct SegmentTree {
        vector<int> cnt;
        vector<int> sum;
        int n;

        SegmentTree(int _n = 0) {
            n = _n;
            cnt.assign(4 * n + 7, 0);
            sum.assign(4 * n + 7, 0);
        }

        void update(int id, int l, int r, int u, int v, int tp) {
            if(l > v || r < u) {
                return;
            }
            if(u <= l && r <= v) {
                cnt[id] += tp;
                if(cnt[id] == 0) {
                    if(l != r) {
                        sum[id] = sum[id * 2] + sum[id * 2 + 1];
                    } else {
                        sum[id] = 0;
                    }
                } else {
                    sum[id] = len[r] - (l == 0 ? 0 : len[l-1]);
                }
                // cout << l << " " << r << " " << sum[id] << "\n";
                return;
            }
            int mid = (l + r) / 2;
            update(id * 2, l, mid, u, v, tp);
            update(id * 2 + 1, mid + 1, r, u, v, tp);
            if(cnt[id] == 0) {
                sum[id] = sum[id * 2] + sum[id * 2 + 1];
            } else {
                sum[id] = len[r] - (l == 0 ? 0 : len[l-1]);
            }
        }
    };

    long long calc(vector<Segment> candidates) {
        vector<int> py;
        int m = 0;
        for(int i = 0; i < (int)candidates.size(); ++i) {
            py.push_back(candidates[i].p1.y);
            py.push_back(candidates[i].p2.y + 1);
            e[++m] = Event(candidates[i].p1.x, candidates[i].p1.y, candidates[i].p2.y, 1);
            e[++m] = Event(candidates[i].p2.x + 1, candidates[i].p1.y, candidates[i].p2.y, -1);
        }

        py.push_back(-INF);
        sort(py.begin(), py.end());
        py.erase(unique(py.begin(), py.end()), py.end());
        int sz = (int)py.size() - 1;
        for(int i = 1; i < sz; ++i) {
            len[i] = len[i-1] + py[i+1] - py[i];
        }
        SegmentTree it = SegmentTree(sz);

        sort(e + 1, e + m + 1);
        long long ans = 0;
        for(int i = 1; i <= m; ++i) {
            if(i > 1) {
                ans += 1LL * (e[i].x - e[i-1].x) * it.sum[1];
            }
            // cout << it.sum[1] << "\n";
            int l = lower_bound(py.begin(), py.end(), e[i].l) - py.begin();
            int r = lower_bound(py.begin(), py.end(), e[i].r + 1) - py.begin() - 1;
            // cout << e[i].x << " " << l << " " << r << " " << len[r] - len[l-1] << " " << e[i].tp << "\n";
            it.update(1, 1, sz, l, r, e[i].tp);
        }
        return ans;
    }
}

namespace Component {
    bool isEnd[N];
    int endTime[N];

    struct DisjointSet
    {
        vector<int> lab;
        int n;
        DisjointSet(int _n = 0)
        {
            n = _n;
            lab.assign(n+7, -1);
        }
        int Find(int u)
        {
            if(lab[u] < 0)
                return u;
            return lab[u] = Find(lab[u]);
        }
        bool join(int u, int v)
        {
            u = Find(u), v = Find(v);
            if(u == v)
                return false;
            if(lab[u] < lab[v]) 
                swap(u, v);
            lab[v] += lab[u], lab[u] = v;
            return true;
        }
    }dsu;

    struct SegmentTree
    {
        vector<int> cnt;
        vector<vector<int> > node1, node2;
        int n;
        SegmentTree(int _n = 0)
        {
            n = _n;
            cnt.assign(4 * n + 7, 0);
            node1.assign(4 * n + 7, vector<int>());
            node2.assign(4 * n + 7, vector<int>());
        }

        void join(vector<int> &a, int node) {
            int best = -1;
            for(int x : a) {
                if(isEnd[x]) {
                    continue;
                }
                // cout << "Join: " << node << " " << x << '\n';
                if(best == -1 || endTime[x] > endTime[best]) {
                    best = x;
                }
                dsu.join(x, node);
            }
            a.clear();
            if(best != -1) {
                a.push_back(best);
            }
        }

        void update(int id, int l, int r, int u, int v, int node)
        {
            if(l > v || r < u) {
                return;
            }
            join(node1[id], node);

            if(u <= l && r <= v) {
                // node2[id].push_back(node);
                // node1[id].push_back(node);
                join(node2[id], node);
                return;
            }
            // node2[id].push_back(node);
            int mid = (l + r) / 2;
            update(id * 2, l, mid, u, v, node);
            update(id * 2 + 1, mid + 1, r, u, v, node);
        }

        void add(int id, int l, int r, int u, int v, int node)
        {
            if(l > v || r < u) {
                return;
            }

            if(u <= l && r <= v) {
                node2[id].push_back(node);
                node1[id].push_back(node);
                return;
            }
            node2[id].push_back(node);

            int mid = (l + r) / 2;
            add(id * 2, l, mid, u, v, node);
            add(id * 2 + 1, mid + 1, r, u, v, node);
        }
    };

    vector<int> calc(vector<Segment> candidates) {
        int n = (int)candidates.size();
        vector<int> py;
        int m = 0;
        for(int i = 0; i < (int)candidates.size(); ++i) {
            py.push_back(candidates[i].p1.y-1);
            py.push_back(candidates[i].p1.y);
            py.push_back(candidates[i].p2.y);
            py.push_back(candidates[i].p2.y + 1);
            e[++m] = Event(candidates[i].p1.x, candidates[i].p1.y - 1, candidates[i].p2.y + 1, 1);
            e[m].id = i + 1;
            endTime[i+1] = candidates[i].p2.x;
            e[++m] = Event(candidates[i].p2.x + 1, candidates[i].p1.y, candidates[i].p2.y, -1);
            e[m].id = i + 1 + n;
            endTime[i+1+n] = candidates[i].p2.x + 1;
        }

        dsu = DisjointSet(n * 2);
        for(int i = 1; i <= n; ++i) {
            dsu.join(i, i + n);
        }
        py.push_back(-INF);
        sort(py.begin(), py.end());
        py.erase(unique(py.begin(), py.end()), py.end());
        int sz = (int)py.size();
        SegmentTree it = SegmentTree(sz);

        sort(e + 1, e + m + 1);
        priority_queue<pii, vector<pii>, greater<pii> > pq;
        for(int i = 1; i <= m; ++i) {
            while(pq.size() && pq.top().fi < e[i].x) {
                int id = pq.top().se;
                // cout << i << " " << id << '\n';
                pq.pop();
                isEnd[id] = true;
            }
            int id = e[i].id;
            int l = lower_bound(py.begin(), py.end(), e[i].l) - py.begin();
            int r = lower_bound(py.begin(), py.end(), e[i].r) - py.begin();
            // cout << e[i].x << " " << id << " " << l << " " << r << '\n';
            if(id <= n) {
                int x = lower_bound(py.begin(), py.end(), e[i].l + 1) - py.begin();
                int y = lower_bound(py.begin(), py.end(), e[i].r - 1) - py.begin();
                // cout << x << " " << y << '\n';
                it.update(1, 1, sz, x, y, id);
            }
            // cout << "Add:\n";
            it.add(1, 1, sz, l, r, id);
            pq.push({endTime[id], id});
        }

        vector<int> ans;
        for(int i = 1; i <= n; ++i) {
            ans.push_back(dsu.Find(i));
        }
        return ans;
    }
}

int n;
Segment segs[N];
 
void solve() {
    cin >> n;
    for(int i = 1; i <= n; ++i) {
        int x, y, u, v;
        cin >> x >> y >> u >> v;
        segs[i].p1 = {x, y};
        segs[i].p2 = {u, v};
    }
    
    vector<Segment> candidates;
    for(int i = 1; i <= n; ++i) {
        if(segs[i].p1.x > segs[i].p2.x) {
            continue;
        }
        if(segs[i].p1.y > segs[i].p2.y) {
            continue;
        }
        candidates.push_back(segs[i]);
    }

    vector<int> comp = Component::calc(candidates);
    // for(int x : comp) {
    //     cout << x << " ";
    // }
    // cout << '\n';
    vector<int> perm;
    for(int i = 1; i <= n; ++i) {
        perm.push_back(i);
    }
    sort(perm.begin(), perm.end(), [&](int u, int v) {
        return comp[u-1] < comp[v-1];
    });

    long long ans = 0;
    int cur = 0;
    while(cur < n) {
        int nxt = cur;
        while(nxt < n && comp[perm[nxt] - 1] == comp[perm[cur] - 1]) {
            ++nxt;
        }
        vector<Segment> tmp;
        for(int i = cur; i < nxt; ++i) {
            tmp.push_back(segs[perm[i]]);
        }
        ans = max(ans, Area::calc(tmp));
        cur = nxt;
    }

    cout << ans;
}
 
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    freopen(task ".inp", "r", stdin);
    freopen(task ".out", "w", stdout);
    solve();
    // cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
    return 0;
}
