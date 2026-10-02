struct Trie{
    struct Node{
        int child[2];
        int exist, cnt;
    } nodes[N];
    int cur;
    Trie() : cur(0) {
        memset(nodes[0].child, -1, sizeof(nodes[cur].child));
        nodes[0].exist = nodes[0].cnt = 0;
    };
    int new_node() {
        cur++;
        memset(nodes[cur].child, -1, sizeof(nodes[cur].child));
        nodes[cur].exist = nodes[cur].cnt = 0;
        return cur;
    }
    void add_number(int x) {
        int pos = 0;
        for (int i = 20; i >= 0; i--) {
            int c = (x >> i) & 1;
            if (nodes[pos].child[c] == -1) nodes[pos].child[c] = new_node();
            pos = nodes[pos].child[c];
            nodes[pos].cnt++;
        }
        nodes[pos].exist++;
    }
    void delete_number(int x) {
        if (find_number(x) == false) return;
        int pos = 0;
        for (int i = 20; i >= 0; i--) {
            int c = bit(i, x);
            int tmp = nodes[pos].child[c];
            nodes[tmp].cnt--;
            if (nodes[tmp].cnt == 0) {
                nodes[pos].child[c] = -1;
                return;
            }
            pos = tmp;
        }
        nodes[pos].exist--;
    }
    bool find_number(int x) {
        int pos = 0;
        for (int i = 20; i >= 0; i--) {
            //int c = (x & (1 << i) ? 1 : 0);
            int c = bit(i, x);
            if (nodes[pos].child[c] == -1) return false;
            pos = nodes[pos].child[c];
        }
        return (nodes[pos].exist != 0);
    }
};
