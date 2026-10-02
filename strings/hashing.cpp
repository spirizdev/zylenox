const int N = 1e6 + 10;
const int MOD1 = 127657753, MOD2 = 987654319;
const int p1 = 137, p2 = 277;
int ip1, ip2;
pii pw[N], ipw[N];
void prec() {
    pw[0] =  {1, 1};
    for (int i = 1; i < N; i++) {
        pw[i].fi = 1ll * pw[i - 1].fi * p1 % MOD1;
        pw[i].se = 1ll * pw[i - 1].se * p2 % MOD2;
    }
    ip1 = binpow(p1, MOD1 - 2, MOD1);
    ip2 = binpow(p2, MOD2 - 2, MOD2);
    ipw[0] =  {1, 1};
    for (int i = 1; i < N; i++) {
        ipw[i].fi = 1ll * ipw[i - 1].fi * ip1 % MOD1;
        ipw[i].se = 1ll * ipw[i - 1].se * ip2 % MOD2;
    }
}
struct Hashing {
    int n;
    string s; // 0 - indexed
    vii hs; // 1 - indexed
    Hashing() {}
    Hashing(string _s) {
        n = sz(_s);
        s = _s;
        hs.eb(0, 0);
        for (int i = 0; i < n; i++) {
            pii p;
            p.fi = (hs[i].fi + 1ll * pw[i].fi * s[i] % MOD1) % MOD1;
            p.se = (hs[i].se + 1ll * pw[i].se * s[i] % MOD2) % MOD2;
            hs.pb(p);
        }
    }
    pii get_hash(int l, int r) {
        assert(1 <= l && l <= r && r <= n);
        pii ans;
        ans.fi = (hs[r].fi - hs[l - 1].fi + MOD1) * 1ll * ipw[l - 1].fi % MOD1;
        ans.se = (hs[r].se - hs[l - 1].se + MOD2) * 1ll * ipw[l - 1].se % MOD2;
        return ans;
    }
    pii get_hash() {
        return get_hash(1, n);
    }
};
void main(void) {
    prec();
    int n; while (cin >> n) {
        string s, p; cin >> p >> s;
        Hashing h(s);
        auto hs = Hashing(p).get_hash();
        for (int i = 1; i + n - 1 <= sz(s); i++)
            if (h.get_hash(i, i + n - 1) == hs)
                cout << i - 1 << '\n';
        cout << '\n';
    }
}
