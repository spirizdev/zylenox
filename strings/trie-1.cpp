struct Trie {
    struct Node {
        int child[26];
        int exist, cnt;
    } nodes[N];
    int cur;
    Trie() : cur(0) {
        memset(nodes[0].child, -1, sizeof(nodes[cur].child));
        nodes[0].exist = nodes[0].cnt = 0;
    }
    int new_node() {
        cur++;
        memset(nodes[cur].child, -1, sizeof(nodes[cur].child));
        nodes[cur].exist = nodes[cur].cnt = 0;
        return cur;
    }
    void add_string(string s) {
        int pos = 0;
        for (auto f : s) {
            int c = f - 'a';
            if (nodes[pos].child[c] == -1)
                nodes[pos].child[c] = new_node();
            pos = nodes[pos].child[c];
            nodes[pos].cnt++;
        }
        nodes[pos].exist++;
    }
    bool delete_string_recursive(int pos, string &s, int i) {
        if (i != sz(s)) {
            int c = s[i] - 'a';
            bool isChildDeleted = delete_string_recursive(nodes[pos].child[c], s, i + 1);
            if (isChildDeleted) nodes[pos].child[c] = -1;
        }
        else nodes[pos].exist--;
        if (pos != 0) {
            nodes[pos].cnt--;
            if (nodes[pos].cnt == 0) return true;
        }
        return false;
    }
    void delete_string(string s) {
        if (find_string(s) == false) return;
        delete_string_recursive(0, s, 0);
    }
    bool find_string(string s) {
        int pos = 0;
        for (auto f : s) {
            int c = f - 'a';
            if (nodes[pos].child[c] == -1) return false;
            pos = nodes[pos].child[c];
        }
        return (nodes[pos].exist != 0);
    }
};
