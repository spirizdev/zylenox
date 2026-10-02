struct hash_pair {
    template <class T1, class T2>
    size_t operator()(const pair<T1, T2> &p) const {
        size_t hash1 = hash<T1>{}(p.fi);
        size_t hash2 = hash<T2>{}(p.se);
        return hash1 ^ (hash2 + 0x9e3779b9 + (hash1 << 6) + (hash1 >> 2));
    }
};
struct hash_tuple {
    template <class T1, class T2, class T3>
    size_t operator()(const tuple<T1, T2, T3>& x) const {
        return get<0>(x) ^ get<1>(x) ^ get<2>(x);
    }
};
struct hash_vector {
    template <class T>
    size_t operator()(const vector<T> &vec) const {
        size_t seed = 0;
        for (const auto &i : vec)
            seed ^= hash<T>()(i) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        return seed;
    }
};
