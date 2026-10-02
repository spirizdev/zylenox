const int LG = 20;
void induced_sort(const vi &vec, int val_range, vi &SA, const vector<bool> &sl, const vi &lms_idx) {
    vi l(val_range, 0), r(val_range, 0);
    each(c, vec) {
        if (c + 1 < val_range) ++l[c + 1];
        ++r[c];
    }
    partial_sum(all(l), l.begin());
    partial_sum(all(r), r.begin());
    fill(all(SA), -1);
    per(i, sz(lms_idx) - 1, 0)
        SA[--r[vec[lms_idx[i]]]] = lms_idx[i];
    each(i, SA)
        if (i >= 1 && sl[i - 1]) {
            SA[l[vec[i - 1]]++] = i - 1;
        }
    fill(all(r), 0);
    each(c, vec) ++r[c];
    partial_sum(all(r), r.begin());
    for (int k = sz(SA) - 1, i = SA[k]; k >= 1; --k, i = SA[k])
        if (i >= 1 && !sl[i - 1]) {
            SA[--r[vec[i - 1]]] = i - 1;
        }
}
vi SA_IS(const vi &vec, int val_range) {
    const int n = sz(vec);
    vi SA(n), lms_idx;
    vector<bool> sl(n);
    sl[n - 1] = false;
    per(i, n - 2, 0) {
        sl[i] = (vec[i] > vec[i + 1] || (vec[i] == vec[i + 1] && sl[i + 1]));
        if (sl[i] && !sl[i + 1]) lms_idx.pb(i + 1);
    }
    reverse(all(lms_idx));
    induced_sort(vec, val_range, SA, sl, lms_idx);
    vi new_lms_idx(sz(lms_idx)), lms_vec(sz(lms_idx));
    for (int i = 0, k = 0; i < n; ++i)
        if (!sl[SA[i]] && SA[i] >= 1 && sl[SA[i] - 1]) {
            new_lms_idx[k++] = SA[i];
        }
    int cur = 0;
    SA[n - 1] = cur;
    rep(k, 1, sz(new_lms_idx) - 1) {
        int i = new_lms_idx[k - 1], j = new_lms_idx[k];
        if (vec[i] != vec[j]) {
            SA[j] = ++cur;
            continue;
        }
        bool flag = false;
        for (int a = i + 1, b = j + 1;; ++a, ++b) {
            if (vec[a] != vec[b]) {
                flag = true;
                break;
            }
            if ((!sl[a] && sl[a - 1]) || (!sl[b] && sl[b - 1])) {
                flag = !((!sl[a] && sl[a - 1]) && (!sl[b] && sl[b - 1]));
                break;
            }
        }
        SA[j] = (flag ? ++cur : cur);
    }
    rep(i, 0, sz(lms_idx) - 1) lms_vec[i] = SA[lms_idx[i]];
    if (cur + 1 < sz(lms_idx)) {
        auto lms_SA = SA_IS(lms_vec, cur + 1);
        rep(i, 0, sz(lms_idx) - 1) new_lms_idx[i] = lms_idx[lms_SA[i]];
    }
    induced_sort(vec, val_range, SA, sl, new_lms_idx);
    return SA;
}
vi suffix_array(const string &s, const int LIM = 128) {
    vi vec(sz(s) + 1);
    copy(all(s), begin(vec));
    vec.back() = '!';
    auto ret = SA_IS(vec, LIM);
    ret.erase(ret.begin());
    return ret;
}
struct SuffixArray {
    int n;
    string s;
    vi sa, rank, lcp;
    vvi t;
    vi lg;
    SuffixArray() {}
    SuffixArray(string _s) {
        n = sz(_s);
        s = _s;
        sa = suffix_array(s);
        rank.resize(n);
        rep(i, 0, n - 1) rank[sa[i]] = i;
        costruct_lcp();
        prec();
        build();
    }
    void costruct_lcp() {
        int k = 0;
        lcp.resize(n - 1, 0);
        rep(i, 0, n - 1) {
            if (rank[i] == n - 1) {
                k = 0;
                continue;
            }
            int j = sa[rank[i] + 1];
            while (i + k < n && j + k < n && s[i + k] == s[j + k]) k++;
            lcp[rank[i]] = k;
            if (k) k--;
        }
    }
    void prec() {
        lg.resize(n, 0);
        rep(i, 2, n - 1) lg[i] = lg[i / 2] + 1;
    }
    void build() {
        int szl = n - 1;
        t.resize(szl);
        rep(i, 0, szl - 1) {
            t[i].resize(LG);
            t[i][0] = lcp[i];
        }
        rep(k, 1, LG - 1) {
            for (int i = 0; i + (1 << k) - 1 < szl; ++i) {
                t[i][k] = min(t[i][k - 1], t[i + (1 << (k - 1))][k - 1]);
            }
        }
    }
    int query(int l, int r) {
        int k = lg[r - l + 1];
        return min(t[l][k], t[r - (1 << k) + 1][k]);
    }
    int get_lcp(int i, int j) {
        if (i == j) return n - i;
        int l = rank[i], r = rank[j];
        if (l > r) swap(l, r);
        return query(l, r - 1);
    }
    int lower_bound(string &tt) {
        int l = 0, r = n - 1, k = sz(tt), ans = n;
        while (l <= r) {
            int mid = l + r >> 1;
            if (s.substr(sa[mid], min(n - sa[mid], k)) >= tt) ans = mid, r = mid - 1;
            else l = mid + 1;
        }
        return ans;
    }
    int upper_bound(string &tt) {
        int l = 0, r = n - 1, k = sz(tt), ans = n;
        while (l <= r) {
            int mid = l + r >> 1;
            if (s.substr(sa[mid], min(n - sa[mid], k)) > tt) ans = mid, r = mid - 1;
            else l = mid + 1;
        }
        return ans;
    }
    pii find_occurrence(int p, int len) {
        p = rank[p];
        pii ans = {p, p};
        int l = 0, r = p - 1;
        while (l <= r) {
            int mid = l + r >> 1;
            if (query(mid, p - 1) >= len) ans.fi = mid, r = mid - 1;
            else l = mid + 1;
        }
        l = p + 1, r = n - 1;
        while (l <= r) {
            int mid = l + r >> 1;
            if (query(p, mid - 1) >= len) ans.se = mid, l = mid + 1;
            else r = mid - 1;
        }
        return ans;
    }
};
