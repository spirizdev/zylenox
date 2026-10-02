// Efficiently finds nearest smaller elements.
int n; vi a;
void useStack() {
    stack<int> st;
    int ans = 0;
    for (int i = 1; i <= n + 1; i++) {
        while (!st.empty() && (i > n || a[st.top()] > a[i])) {
            int h = a[st.top()]; st.pop();
            int l = st.empty() ? 0 : st.top();
            ans = max(ans, h * (i - l - 1));
        }
        st.push(i);
    }
    cout << ans << '\n';
}
void noneStack() {
    vi l(n + 1), r(n + 1);
    for (int i = 1; i <= n; i++) {
        l[i] = i - 1;
        while (a[l[i]] >= a[i])
            l[i] = l[l[i]];
    }
    for (int i = n; i >= 1; i--) {
        r[i] = i + 1;
        while (a[r[i]] >= a[i])
            r[i] = r[r[i]];
    }
    int ans = 0;
    for (int i = 1; i <= n; i++)
        ans = max(ans, (r[i] - l[i] - 1) * a[i]);
    cout << ans << '\n';
}
