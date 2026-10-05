#include <bits/stdc++.h>
#define Task "task"
#define Nyaa main
#define fi first
#define se second
#define pb push_back
#define eb emplace_back
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define bit(i, x) (((x) >> (i)) & 1)
#define sz(x) (int)(x).size()
#define mem(a, b) memset(a, b, sizeof(a))
#define rep(i, a, b) for (int i = (a); i <= (b); ++i)
#define per(i, a, b) for (int i = (a); i >= (b); --i)
#define each(x, a) for (auto &x : (a))
#define ntest int t; cin >> t; while (t--) solve()
#define __lcm(a, b) (1ll * ((a) / __gcd((a), (b))) * (b))
#define yes cout << "yes\n"
#define no cout << "no\n"
using namespace std;
#ifdef LOCAL
#include "debug.cpp"
#else
#define debug(...) void()
#define debugArr(...) void()
#endif // LOCAL
#define int ll
typedef long long ll;
typedef long double db;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<pii> vii;
typedef vector<pll> vll;
typedef vector<vi> vvi;
typedef vector<vl> vvl;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
template <class X, class Y>
bool cmax(X &x, const Y &y) {
    return x < y ? x = y, true : false;
}
template <class X, class Y>
bool cmin(X &x, const Y &y) {
    return x > y ? x = y, true : false;
}
ifstream finp("input.txt");
ifstream fout("my.txt");
ifstream fans("correct.txt");
// finp >> n;
Nyaa() {
    cin.tie(nullptr)->sync_with_stdio(false);
    if (fopen("input.inp", "r")) {
        freopen("input.inp", "r", stdin);
        //freopen("output.out", "w", stdout);
    } else if (fopen(Task".inp", "r")) {
        freopen(Task".inp", "r", stdin);
        freopen(Task".out", "w", stdout);
    }
    
    cerr << "\nTime elapsed: " << 1000.0 * clock() / CLOCKS_PER_SEC << " ms.\n";
    return 0;
}
