const int MOD = 1e9 + 7;
struct Mat {
    int n, m;
    vector<vi> a;
    Mat() {}
    Mat(int _n, int _m) {
        n = _n;
        m = _m;
        a.assign(n, vi(m, 0));
    }
    Mat(vector<vi> v) {
        n = sz(v);
        m = n ? sz(v[0]) : 0;
        a = v;
    }
    inline void make_unit() {
        assert(n == m);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                a[i][j] = i == j;
    }
    inline Mat operator + (const Mat &b) {
        assert(n == b.n && m == b.m);
        Mat ans = Mat(n, m);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                ans.a[i][j] = (a[i][j] + b.a[i][j]) % MOD;
        return ans;
    }
    inline Mat operator - (const Mat &b) {
        assert(n == b.n && m == b.m);
        Mat ans = Mat(n, m);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                ans.a[i][j] = (a[i][j] - b.a[i][j] + MOD) % MOD;
        return ans;
    }
    inline Mat operator * (const Mat &b) {
        assert(m == b.n);
        Mat ans = Mat(n, b.m);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < b.m; j++)
                for (int k = 0; k < m; k++)
                    ans.a[i][j] = (ans.a[i][j] + 1ll * a[i][k] * b.a[k][j] % MOD) % MOD;
        return ans;
    }
    inline Mat pow(ll k) {
        assert(n == m);
        Mat ans(n, n), t = a;
        ans.make_unit();
        for (; k; k >>= 1, t = t * t)
            if (k & 1) ans = ans * t;
        return ans;
    }
    inline Mat& operator += (const Mat& b) {
        return *this = (*this) + b;
    }
    inline Mat& operator -= (const Mat& b) {
        return *this = (*this) - b;
    }
    inline Mat& operator *= (const Mat& b) {
        return *this = (*this) * b;
    }
    inline bool operator == (const Mat& b) {
        return a == b.a;
    }
    inline bool operator != (const Mat& b) {
        return a != b.a;
    }
};
void main(void) {
    ll n; cin >> n;
    Mat base(2, 2), m(2, 2);
    base.a = {{1, 0}, {0, 1}};
    m.a = {{1, 1}, {1, 0}};
    base *= m.pow(n);
    cout << base.a[0][1];
}
