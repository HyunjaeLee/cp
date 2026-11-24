#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

// https://hitonanode.github.io/cplib-cpp/data_structure/fast_hash_map.hpp
// Fixed-capacity hash map for integer keys.
// At most n distinct keys can be stored.
template <std::integral K, typename V> struct HashMap {
    static_assert(sizeof(K) <= sizeof(std::uint64_t));

    HashMap(std::size_t n_) : n(std::bit_ceil(n_)), keys(n), values(n), versions(n), multiplier(make_multiplier()) {}
    void set(K key, V value) {
        std::size_t pos = hash(key);
        for (std::size_t step = 0; step < n; ++step) {
            if (versions[pos] != version) {
                keys[pos] = key;
                values[pos] = value;
                versions[pos] = version;
                assert(count < n);
                ++count;
                return;
            }
            if (keys[pos] == key) {
                values[pos] = value;
                return;
            }
            pos = (pos + 1) & (n - 1);
        }
        assert(false && "HashMap capacity exceeded");
    }
    std::optional<V> get(K key) const {
        std::size_t pos = hash(key);
        for (std::size_t step = 0; step < n; ++step) {
            if (versions[pos] != version) {
                return std::nullopt;
            }
            if (keys[pos] == key) {
                return values[pos];
            }
            pos = (pos + 1) & (n - 1);
        }
        return std::nullopt;
    }
    std::size_t size() const { return count; }
    bool empty() const { return count == 0; }
    void clear() {
        ++version;
        count = 0;
    }
    void reset() { clear(); }

private:
    std::size_t hash(K key) const {
        if (n == 1) {
            return 0;
        }
        int shift = 64 - std::countr_zero(n);
        return (static_cast<std::uint64_t>(key) * multiplier) >> shift;
    }
    static std::uint64_t make_multiplier() {
        // Use a nondeterministic seed
        std::mt19937_64 mt(std::chrono::steady_clock::now().time_since_epoch().count());
        return mt() | 1;
    }

    std::size_t n;
    std::vector<K> keys;
    std::vector<V> values;
    std::vector<std::uint32_t> versions;
    std::uint64_t multiplier;
    std::uint32_t version = 1;
    std::size_t count = 0;
};

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int N, M, Q;
    cin >> N >> M >> Q;
    HashMap<i64, int> E(1'000'000);
    auto f = [](pair<int, int> a) { return (i64(a.first) << 32) | a.second; };
    vector<vector<pair<int, int>>> G(N);
    for (auto i = 0; i < M; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        --u, --v;
        E.set(f(minmax(u, v)), w);
        G[u].emplace_back(v, w);
        G[v].emplace_back(u, w);
    }
    constexpr auto inf = numeric_limits<int>::max() / 4;
    auto Q1 = [&](int u, int v) {
        if (auto r = E.get(f(minmax(u, v))))
            return *r;
        return inf;
    };
    HashMap<i64, int> memo2(30'000'000);
    auto Q2 = [&](int u, int v) {
        if (pair(size(G[u]), u) > pair(size(G[v]), v)) {
            swap(u, v);
        }
        if (auto r = memo2.get(f({u, v})))
            return *r;
        auto d = inf;
        for (auto [x, w] : G[u])
            d = min(d, w + Q1(x, v));
        memo2.set(f({u, v}), d);
        return d;
    };
    HashMap<i64, int> memo3(1'000'000);
    auto Q3 = [&](int u, int v) {
        if (pair(size(G[u]), u) > pair(size(G[v]), v)) {
            swap(u, v);
        }
        if (auto r = memo3.get(f({u, v})))
            return *r;
        auto d = inf;
        for (auto [x, w] : G[u])
            d = min(d, w + Q2(x, v));
        memo3.set(f({u, v}), d);
        return d;
    };
    while (Q--) {
        int u, v;
        cin >> u >> v;
        --u, --v;
        auto ans = min({Q1(u, v), Q2(u, v), Q3(u, v)});
        if (inf <= ans) {
            ans = -1;
        }
        cout << ans << "\n";
    }
}
