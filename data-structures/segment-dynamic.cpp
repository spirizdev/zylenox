struct node {
    node *left, *right;
    int mx, cnt, lz;
    node() : left(nullptr), right(nullptr), mx(0), cnt(0), lz(0) {}
};
node *root;
void prep(node *&p, int l, int r) {
    if (!p) {
        p = new node();
        p->cnt = r - l + 1;
    }
}
void push(node *&p, int l, int r) {
    if (p->lz) {
        int mid = (l + r) >> 1;
        prep(p->left, l, mid);
        prep(p->right, mid + 1, r);
        for (auto &q : {p->left, p->right})
            q->mx += p->lz, q->lz += p->lz;
        p->lz = 0;
    }
}
void upd(node *&p, int l, int r, int u, int v, int val) {
    prep(p, l, r);
    if (u > r || v < l) return;
    if (u <= l && r <= v) return p->mx += val, p->lz += val, void();
    push(p, l, r);
    int mid = (l + r) >> 1;
    upd(p->left, l, mid, u, v, val);
    upd(p->right, mid + 1, r, u, v, val);
    if (p->left->mx == p->right->mx)
        p->mx = p->left->mx,
        p->cnt = p->left->cnt + p->right->cnt;
    else if (p->left->mx > p->right->mx)
        p->mx = p->left->mx,
        p->cnt = p->left->cnt;
    else
        p->mx = p->right->mx,
        p->cnt = p->right->cnt;
}
pii get(node *&p, int l, int r, int u, int v) {
    prep(p, l, r);
    if (u > r || v < l) return {-1, -1};
    if (u <= l && r <= v) return {p->mx, p->cnt};
    push(p, l, r);
    int mid = (l + r) >> 1;
    pii lo = get(p->left, l, mid, u, v);
    pii hi = get(p->right, mid + 1, r, u, v);
    if (lo.fi == hi.fi) return {lo.fi, lo.se + hi.se};
    if (lo.fi > hi.fi) return {lo.fi, lo.se};
    return {hi.fi, hi.se};
}