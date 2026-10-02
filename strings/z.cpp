vi z_function(string s) {
    int n = sz(s); vi z(n);
    int l = 0, r = 0; z[0] = n;
    rep(i, 1, n - 1) {
        if (i < r) z[i] = min(r - i, z[i - l]);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) ++z[i];
        if (i + z[i] > r) l = i, r = i + z[i];
    }
    return z;
}
