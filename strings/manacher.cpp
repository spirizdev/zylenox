int n; string s;
int d_odd[N], d_even[N];
void calc_d_odd() {
    int l = 1, r = 0;
    for (int i = 1; i <= n; i++) {
        if (i > r) d_odd[i] = 0;
        else d_odd[i] = min(r - i, d_odd[l + (r - i)]);
        while (i - d_odd[i] - 1 > 0 && i + d_odd[i] + 1 <= n && s[i - d_odd[i] - 1] == s[i + d_odd[i] + 1]) ++d_odd[i];
        if (i + d_odd[i] > r) r = i + d_odd[i], l = i - d_odd[i];
    }
}
void calc_d_even() {
    int l = 1, r = 0;
    for (int i = 1; i < n; i++) {
        int j = i + 1;
        if (j > r) d_even[i] = 0;
        else d_even[i] = min(r - j + 1, d_even[l + (r - j)]);
        while (i - d_even[i] > 0 && j + d_even[i] <= n && s[i - d_even[i]] == s[j + d_even[i]]) ++d_even[i];
        if (i + d_even[i] > r) r = i + d_even[i], l = j - d_even[i];
    }
}
void solve() {
    cin >> s; n = sz(s);
    s = ' ' + s;
    calc_d_odd();
    calc_d_even();
    for (int i = 1; i < n; i++)
        cout << d_odd[i] * 2 + 1 << ' ' << d_even[i] * 2 << ' ';
    cout << d_odd[n] * 2 + 1;
}
