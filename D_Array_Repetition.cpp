#include <bits/stdc++.h>
#define int i64
using namespace std;
using i64 = long long;
using i128 = __int128;

template <typename T, int N> struct MemoryPool {
    union Slot {
        alignas(T) char raw[sizeof(T)];
        int next;
    };
    static int alloc(auto &&...args) {
        int i;
        if (~head) {
            i = head;
            head = data[head].next;
        } else {
            assert(size < N);
            i = size++;
        }
        new (&data[i].raw) T(std::forward<decltype(args)>(args)...);
        return i;
    }
    static void free(int i) {
        if (~i) {
            destroy_at(&get(i));
            data[i].next = head;
            head = i;
        }
    }
    static T &get(int i) {
        assert(~i);
        return reinterpret_cast<T &>(data[i].raw);
    }
    inline static std::vector<Slot> data = std::vector<Slot>(N);
    inline static int head = -1;
    inline static int size = 0;
};

template <typename T, int N> struct IntrusivePtr {
    using M = MemoryPool<T, N>;
    int i = -1;
    IntrusivePtr() = default;
    IntrusivePtr(std::nullptr_t) {}
    IntrusivePtr(const IntrusivePtr &o) : i(o.i) {
        if (~i)
            M::get(i).ref_count++;
    }
    IntrusivePtr(IntrusivePtr &&o) noexcept : i(o.i) { o.i = -1; }
    IntrusivePtr &operator=(const IntrusivePtr &o) {
        if (this != &o) {
            auto new_i = o.i;
            if (~new_i)
                M::get(new_i).ref_count++;
            reset();
            i = new_i;
        }
        return *this;
    }
    IntrusivePtr &operator=(IntrusivePtr &&o) noexcept {
        if (this != &o) {
            reset();
            i = o.i;
            o.i = -1;
        }
        return *this;
    }
    ~IntrusivePtr() { reset(); }
    static IntrusivePtr create(auto &&...args) {
        IntrusivePtr p;
        p.i = M::alloc(std::forward<decltype(args)>(args)...);
        M::get(p.i).ref_count = 1;
        return p;
    }
    void reset() {
        if (~i) {
            if (--M::get(i).ref_count == 0)
                M::free(i);
            i = -1;
        }
    }
    T &operator*() const { return M::get(i); }
    T *operator->() const { return &M::get(i); }
    explicit operator bool() const { return ~i; }
    bool operator==(const IntrusivePtr &o) const { return i == o.i; }
};

template <typename Node> struct WeightBalancedTree {
private:
    using ptr_t = typename Node::ptr_t;
    using T = WeightBalancedTree;
    ptr_t root;
    explicit WeightBalancedTree(ptr_t _root) : root(_root) {}
    static bool is_heavy(int a, int b) { return a > i128(10) * b; }
    static ptr_t build(auto l, auto r) { // O(N)
        if (l == r)
            return nullptr;
        if (l + 1 == r) {
            return Node::make_node(decltype(Node::val){*l}); // make_leaf
        }
        auto mid = l + (r - l) / 2;
        return merge(build(l, mid), build(mid, r));
    }
    static ptr_t merge(ptr_t x, ptr_t y) {
        if (!x || !y)
            return x ? x : y;
        if (is_heavy(x->size, y->size)) {
            auto [a, b] = Node::propagate(x);
            if (is_heavy(b->size + y->size, a->size)) {
                auto [c, d] = Node::propagate(b);
                return merge(merge(a, c), merge(d, y));
            } else {
                return merge(a, merge(b, y));
            }
        } else if (is_heavy(y->size, x->size)) {
            auto [a, b] = Node::propagate(y);
            if (is_heavy(a->size + x->size, b->size)) {
                auto [c, d] = Node::propagate(a);
                return merge(merge(x, c), merge(d, b));
            } else {
                return merge(merge(x, a), b);
            }
        } else {
            return Node::make_node(x, y); // join
        }
    }
    static pair<ptr_t, ptr_t> split(ptr_t u, int p) { // [0, p), [p, N)
        if (!u)
            return {nullptr, nullptr};
        if (p == 0)
            return {nullptr, u};
        if (p == u->size)
            return {u, nullptr};
        auto [ul, ur] = Node::propagate(u);
        if (auto i = ul->size; i < p) {
            auto [l, r] = split(ur, p - i);
            return {merge(ul, l), r};
        } else {
            auto [l, r] = split(ul, p);
            return {l, merge(r, ur)};
        }
    }
    static void dfs(ptr_t u, auto f) {
        if (u->is_leaf()) {
            f(Node::prod(u));
        } else {
            auto [ul, ur] = Node::propagate(u);
            dfs(ul, f);
            dfs(ur, f);
        }
    }
    static ptr_t multiply(ptr_t x, int k) {
        ptr_t r = nullptr;
        while (0 < k) {
            if (k & 1) {
                r = merge(r, x);
            }
            x = merge(x, x);
            k >>= 1;
        }
        return r;
    }

public:
    WeightBalancedTree() : root(nullptr) {}
    explicit WeightBalancedTree(const auto &v) : root(build(v.begin(), v.end())) {}
    explicit WeightBalancedTree(decltype(Node::val) x) : root(Node::make_node(x)) {}

    T friend operator+(T l, T r) { return T(merge(l.root, r.root)); }
    // [0, p), [p, N)
    pair<T, T> split(int p) const {
        auto [l, r] = split(root, p);
        return {T(l), T(r)};
    }
    // [0, l), [l, r), [r, N)
    tuple<T, T, T> split(int l, int r) const {
        ptr_t a, b, c;
        tie(a, b) = split(root, l);
        tie(b, c) = split(b, r - l);
        return {T(a), T(b), T(c)};
    }
    T reverse() const { return T(Node::reverse(root)); }
    auto prod() const { return Node::prod(root); }
    template <typename V = Node> T apply(V::Action f) const { return T(Node::apply(root, f)); }
    void dfs(auto f) const {
        if (root)
            dfs(root, f);
    }
    int size() {
        if (root) {
            return root->size;
        } else {
            return 0;
        }
    }
    friend T operator*(T x, int k) { return T(multiply(x.root, k)); }
    friend T operator*(int k, T x) { return T(multiply(x.root, k)); }
};

// Nodes

template <typename Monoid, int MAXN> struct PersistentNode {
    using ptr_t = IntrusivePtr<PersistentNode, MAXN>;
    Monoid val;
    ptr_t l, r;
    int size;
    int ref_count = 0;
    explicit PersistentNode(Monoid x) : val(x), l(nullptr), r(nullptr), size(1) {}
    PersistentNode(ptr_t a, ptr_t b) : val(Monoid::op(prod(a), prod(b))), l(a), r(b), size((a->size + b->size)) {}
    PersistentNode(Monoid _val, ptr_t _l, ptr_t _r, int _size) : val(_val), l(_l), r(_r), size(_size) {}
    bool is_leaf() const { return !l && !r; }
    static Monoid prod(ptr_t u) { return u ? u->val : Monoid::e(); }
    static ptr_t make_node(auto &&...args) { return ptr_t::create(std::forward<decltype(args)>(args)...); }
    pair<ptr_t, ptr_t> static propagate(ptr_t u) {
        if (!u)
            return {nullptr, nullptr};
        return {u->l, u->r};
    }
};

// Monoids

template <typename T> struct Dummy {
    T val;
    static Dummy op(Dummy, Dummy) { return {}; }
    static Dummy e() { return {}; }
    static Dummy reverse(Dummy x) { return x; }
};

void solve() {
    constexpr auto inf = 1000000000000000000LL + 5;
    int N, Q;
    cin >> N >> Q;
    using T = WeightBalancedTree<PersistentNode<Dummy<int>, 1'000'000>>;
    T tree;
    for (auto i = 0; i < N; ++i) {
        i64 t, x;
        cin >> t >> x;
        if (inf < tree.size())
            continue;
        if (t == 1) {
            tree = tree + T({x});
        } else {
            auto pred = [&](int k) { return tree.size() * i128(k + 1) < inf; };
            x = *ranges::partition_point(views::iota(0, x), pred);
            tree = tree * (x + 1);
        }
    }
    for (auto i = 0; i < Q; ++i) {
        int k;
        cin >> k;
        --k;
        auto [a, b, c] = tree.split(k, k + 1);
        cout << b.prod().val << " ";
    }
    cout << "\n";
}

signed main() {
    cin.tie(0)->sync_with_stdio(0);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}
