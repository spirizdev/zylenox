//_za*mita_
#include <bits/stdc++.h>
#define PB push_back
#define F first
#define S second
#define bit(x, i) ((x >> i) & 1)
#define maxn 1000005
#define il (node * 2)
#define ir (il + 1)
#define mid (l + r) / 2
#define ll long long
#define pii pair <int, int>
#define MOD 1000000007
#define Task "rectangle"
using namespace std;
int n, m;
struct ltm{
    int x1, x2, y1, y2;
};
ltm a[maxn];
vector <int> c;
vector <pair<pii, pii>> luu;
int Tree[4 * maxn], Cnt[4 * maxn];

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

signed main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    if(fopen(Task".inp", "r")) {
        freopen(Task".inp", "r", stdin);
        freopen(Task".out", "w", stdout);
    }
    cin >> n;
    for (int i = 1; i <= n; i ++){
        int x, y, X, Y;
        cin >> x >> X >> y >> Y;
        a[i] = {x, X, y, Y};
        c.PB(y);
        c.PB(Y);
    }

    sort (c.begin(), c.end());
    c.resize(unique(c.begin(), c.end()) - c.begin());
    m = c.size() - 1;

    for (int i = 1; i <= n; i ++){
        a[i].y1 = lower_bound(c.begin(), c.end(), a[i].y1) - c.begin() + 1;
        a[i].y2 = lower_bound(c.begin(), c.end(), a[i].y2) - c.begin() + 1;
        luu.PB({{a[i].x1, 1},{a[i].y1, a[i].y2}});
        luu.PB({{a[i].x2, -1},{a[i].y1, a[i].y2}});
    }

    sort(luu.begin(), luu.end());   
    int last = -1;
    ll ans = 0;
    for (int i = 0; i < luu.size(); i ++){
        if (last != -1) ans += 1ll * (luu[i].F.F - last) * Tree[1];
        Update(1, 1, m, luu[i].S.F, luu[i].S.S - 1, luu[i].F.S);
        last = luu[i].F.F;
    }
    cout << ans;
    return 0;
}
