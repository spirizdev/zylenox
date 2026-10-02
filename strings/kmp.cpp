vi build_lps(string p) {
    int n = sz(p);
    vi lps(n);
    int j = 0;
    rep(i, 1, n - 1) {
        while (j >= 0 && p[i] != p[j]) {
            if (j >= 1) j = lps[j - 1];
            else j = -1;
        }
        ++j;
        lps[i] = j;
    }
    return lps;
}
vi ans;
void kmp(vi lps, string s, string p) {
    int n = sz(s), m = sz(p);
    int j = 0;
    rep(i, 0, n - 1) {
        while (j >= 0 && p[j] != s[i]) {
            if (j >= 1) j = lps[j - 1];
            else j = -1;
        }
        ++j;
        if (j == m) {
            j = lps[j - 1];
            ans.pb(i - m + 1);
        }
    }
}
void main(void) {
    string s, p; cin >> s >> p;
    vi lps = build_lps(p);
    kmp(lps, s, p);
    cout << sz(ans) << '\n';
    for (int x : ans)
        cout << x << ' ';
}
