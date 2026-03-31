#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int MAXN = 1000005;

class SegmentTree {
private:
    int tree[MAXN * 4];
    int lazy[MAXN * 4];
    int n;

    void pushDown(int node, int l, int r) {
        if (lazy[node] != 0) {
            tree[node] += lazy[node];
            if (l != r) {
                lazy[node * 2] += lazy[node];
                lazy[node * 2 + 1] += lazy[node];
            }
            lazy[node] = 0;
        }
    }

    void build(int node, int l, int r, int k) {
        lazy[node] = 0;
        if (l == r) {
            tree[node] = k;
            return;
        }
        int mid = (l + r) / 2;
        build(node * 2, l, mid, k);
        build(node * 2 + 1, mid + 1, r, k);
        tree[node] = min(tree[node * 2], tree[node * 2 + 1]);
    }

    void update(int node, int l, int r, int ql, int qr, int val) {
        pushDown(node, l, r);
        if (ql > r || qr < l) return;
        if (ql <= l && r <= qr) {
            lazy[node] += val;
            pushDown(node, l, r);
            return;
        }
        int mid = (l + r) / 2;
        update(node * 2, l, mid, ql, qr, val);
        update(node * 2 + 1, mid + 1, r, ql, qr, val);
        pushDown(node * 2, l, mid);
        pushDown(node * 2 + 1, mid + 1, r);
        tree[node] = min(tree[node * 2], tree[node * 2 + 1]);
    }

    int query(int node, int l, int r, int ql, int qr) {
        if (ql > r || qr < l) return 1e9;
        pushDown(node, l, r);
        if (ql <= l && r <= qr) {
            return tree[node];
        }
        int mid = (l + r) / 2;
        return min(query(node * 2, l, mid, ql, qr),
                   query(node * 2 + 1, mid + 1, r, ql, qr));
    }

public:
    void init(int _n, int k) {
        n = _n;
        if (n > 0) {
            build(1, 0, n - 1, k);
        }
    }

    void rangeUpdate(int l, int r, int val) {
        if (n > 0 && l <= r) {
            update(1, 0, n - 1, l, r, val);
        }
    }

    int rangeQuery(int l, int r) {
        if (n > 0 && l <= r) {
            return query(1, 0, n - 1, l, r);
        }
        return 1e9;
    }
};

SegmentTree st;

int main() {
    int x, k, p;
    scanf("%d %d %d", &x, &k, &p);

    st.init(x - 1, k);  // x-1 segments between x stations

    for (int i = 0; i < p; i++) {
        int u, v, n;
        scanf("%d %d %d", &u, &v, &n);

        // Convert to 0-indexed segments [u-1, v-2]
        int left = u - 1;
        int right = v - 2;

        int min_seats = st.rangeQuery(left, right);

        if (min_seats >= n) {
            printf("T\n");
            st.rangeUpdate(left, right, -n);
        } else {
            printf("N\n");
        }
    }

    return 0;
}
