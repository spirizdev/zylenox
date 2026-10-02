struct Sqrt {
    int block_size;
    vi nums;
    vector<ll> blocks;
    Sqrt(int sqrtn, int a[], int n) : block_size(sqrtn), blocks(sqrtn, 0) {
        nums.resize(n + 1);
        for (int i = 1; i <= n; i++) {
            nums[i] = a[i];
            blocks[(i - 1) / block_size] += nums[i];
        }
    }
    /** O(1) update to set nums[x] to v */
    void update(int x, int v) {
        blocks[(x - 1) / block_size] -= nums[x];
        nums[x] = v;
        blocks[(x - 1) / block_size] += nums[x];
    }
    /** O(sqrt(n)) query for sum of [l, r] */
    ll query(int l, int r) {
        ll res = 0;
        int block_start = (l - 1) / block_size, block_end = (r - 1) / block_size;
        if (block_start == block_end) {
            for (int i = l; i <= r; i++) res += nums[i];
        } else {
            for (int i = l; i <= (block_start + 1) * block_size; i++) res += nums[i];
            for (int i = block_start + 1; i < block_end; i++) res += blocks[i];
            for (int i = block_end * block_size + 1; i <= r; i++) res += nums[i];
        }
        return res;
    }
//    /** O(sqrt(n)) query for sum of [1, r] */
//    ll query(int r) {
//        ll res = 0;
//        for (int i = 0; i < (r - 1) / block_size; i++) res += blocks[i];
//        for (int i = ((r - 1) / block_size) * block_size + 1; i <= r; i++) res += nums[i];
//        return res;
//    }
//    /** O(sqrt(n)) query for sum of [l, r] */
//    ll query(int l, int r) {
//        return query(r) - query(l - 1);
//    }
};
void main(void) {
    int n, q; cin >> n >> q;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    Sqrt sq((int)ceil(sqrt(n)), a, n);
    for (int i = 0; i < q; i++) {
        int t, l, r; cin >> t >> l >> r;
        if (t == 1) sq.update(l, r);
        else cout << sq.query(l, r) << '\n';
    }
}
