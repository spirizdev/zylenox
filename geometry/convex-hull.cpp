vector<point> convexHull(vector<point> &a) {
    int n = sz(a);
    if (n < 3) return a;
    sort(all(a), [](const point &p, const point &q) {
        return p.x < q.x | (p.x == q.x && p.y < q.y);
    });
    vector<point> hull;
    for (auto p : a) {
        while (sz(hull) >= 2 && cross(hull[sz(hull) - 2], hull.back(), p) <= 0)
            hull.pop_back();
        hull.pb(p);
    }
    int lower_size = sz(hull);
    for (int i = n - 2; i >= 0; i--) {
        while (sz(hull) > lower_size && cross(hull[sz(hull) - 2], hull.back(), a[i]) <= 0)
            hull.pop_back();
        hull.pb(a[i]);
    }
    hull.pop_back();
    return hull;
}
