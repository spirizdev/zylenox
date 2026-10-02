// Find the Mex of frequency counts for a subarray
// or update an element in the array.
const int N = 2e5 + 10;
const int S = 2154; // S = N ^ (2 / 3)
int n, q, a[N];
struct query {
    int l, r, t, id;
    bool operator < (const query &other) const {
        if (l / S == other.l / S) {
            if (r / S == other.r / S) return t < other.t;
            return r / S < other.r / S;
        }
        return l / S < other.l / S;
    }
} qs[N];
struct update {
    int pos, old, cur;
} up[N];
int cnt[N], f[N], ans[N];
int curL, curR, curU;
unordered_map<int, int> mp;
int nxt = 0;
int get(int x) {
    return mp.count(x) ? mp[x] : mp[x] = ++nxt;
}
void add(int x) {
    --f[cnt[x]], ++cnt[x], ++f[cnt[x]];
}
void del(int x) {
    --f[cnt[x]], --cnt[x], ++f[cnt[x]];
}
void update(int pos, int val) {
    if (curL <= pos && pos <= curR)
        add(val), del(a[pos]);
    a[pos] = val;
}
void main(void) {
    cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        a[i] = get(a[i]);
    }
    int nq = 0, nu = 0;
    for (int i = 1; i <= q; i++) {
        int type, l, r;
        cin >> type >> l >> r;
        if (type == 1) {
            qs[++nq] = {l, r, nu, nq};
        } else {
            up[++nu] = {l, a[l], get(r)};
            a[l] = up[nu].cur;
        }
    }
    sort(qs + 1, qs + nq + 1);
    curL = qs[0].l, curR = qs[0].l - 1, curU = nu;
    for (int i = 1; i <= nq; i++) {
        auto [l, r, t, id] = qs[i];
        while (curU < t) ++curU, update(up[curU].pos, up[curU].cur);
        while (curU > t) update(up[curU].pos, up[curU].old), --curU;
        while (curL < l) del(a[curL++]);
        while (curL > l) add(a[--curL]);
        while (curR < r) add(a[++curR]);
        while (curR > r) del(a[curR--]);
        int cur = 1;
        while (f[cur]) ++cur;
        ans[id] = cur;
    }
    for (int i = 1; i <= nq; i++)
        cout << ans[i] << '\n';
}
