const int N = 1e5 + 10;
int n, a[N];
struct ST {
    #define lc (id << 1)
    #define rc (id << 1 | 1)
    int T[N << 2], lz[N << 2];
    void init(int id = 1, int l = 1, int r = n) {
        if (l == r) {
            T[id] = a[l];
            return;
        }
        int mid = (l + r) >> 1;
        init(lc, l, mid);
        init(rc, mid + 1, r);
        T[id] = T[lc] + T[rc];
    }
    void push(int id, int l, int r) {
        if (lz[id]) {
            int mid = (l + r) >> 1;
            T[lc] += lz[id] * (mid - l + 1);
            lz[lc] += lz[id];
            T[rc] += lz[id] * (r - mid);
            lz[rc] += lz[id];
            lz[id] = 0;
        }
    }
    void upd(int u, int v, int val, int id = 1, int l = 1, int r = n) {
        if (u > r || v < l) return;
        if (u <= l && r <= v) {
            T[id] += val * (r - l + 1);
            lz[id] += val;
            return;
        }
        push(id, l, r);
        int mid = (l + r) >> 1;
        upd(u, v, val, lc, l, mid);
        upd(u, v, val, rc, mid + 1, r);
        T[id] = T[lc] + T[rc];
    }
    int get(int u, int v, int id = 1, int l = 1, int r = n) {
        if (u > r || v < l) return 0;
        if (u <= l && r <= v) return T[id];
        push(id, l, r);
        int mid = (l + r) >> 1;
        return get(u, v, lc, l, mid) + get(u, v, rc, mid + 1, r);
    }
};