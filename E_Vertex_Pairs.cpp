#include <atcoder/fenwicktree>
#include <bits/stdc++.h>
using namespace std;

// clang-format off
using i8 = signed char; using u8 = unsigned char;
using i32 = int;        using u32 = unsigned;
using i64 = long long;  using u64 = unsigned long long;
using i128 = __int128;  using u128 = unsigned __int128;
template <typename T> T ceil_div(T a, T b) { return a / b + static_cast<T>((a ^ b) > 0 && a % b != 0); }
template <typename T> T floor_div(T a, T b) { return a / b - static_cast<T>((a ^ b) < 0 && a % b != 0); }
template <int I = 0> void read(auto &a) { for (auto &x : a) { cin >> x; if constexpr (I) { x -= I; } } }
template <int I = 0> void show(const auto &a, string_view sep = " ", string_view end = "\n") {
    for (auto it = a.begin(); it != a.end(); ++it) { if (it != a.begin()) { cout << sep; }
    auto x = *it; if constexpr (I) { x += I; } cout << x; } cout << end;
}
// clang-format on

void solve() {
    int N;
    cin >> N;
    vector<int> A(2 * N);
    read<1>(A);
    vector<vector<int>> adj(2 * N);
    for (auto i = 0; i < 2 * N - 1; ++i) {
        int u, v;
        cin >> u >> v;
        --u, --v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    vector<int> link(N);
    for (auto i = 0; i < 2 * N; ++i) {
        link[A[i]] ^= i;
    }
    auto twin = [&](int i) { return link[A[i]] ^ i; };
    vector<bool> active(2 * N, true);
    for (auto x : adj[2 * N - 1]) {
        auto s = [&](this auto &&self, int u, int p) -> set<int> {
            set<int> a;
            a.insert(A[u]);
            for (auto v : adj[u]) {
                if (v == p)
                    continue;
                auto b = self(v, u);
                if (a.size() < b.size())
                    swap(a, b);
                a.insert(b.begin(), b.end());
            }
            return a;
        }(x, 2 * N - 1);
        if (ssize(s) == N) {
            active[2 * N - 1] = false;
        }
    }
    auto root = active[2 * N - 1] ? 2 * N - 1 : twin(2 * N - 1);
    atcoder::fenwick_tree<int> must(2 * N);
    auto timer = 0;
    vector<int> in(2 * N), out(2 * N);
    [&](this auto &&self, int u, int p) -> void {
        in[u] = timer++;
        for (auto v : adj[u]) {
            if (v == p)
                continue;
            self(v, u);
        }
        out[u] = timer;
    }(root, root);
    [&](this auto &&self, int u, int p) -> pair<bool, set<int>> {
        auto ok = true;
        set<int> a;
        a.insert(A[u]);
        for (auto v : adj[u]) {
            if (v == p)
                continue;
            auto [good, b] = self(v, u);
            ok = ok && good;
            if (a.size() < b.size())
                swap(a, b);
            for (auto x : b) {
                auto [it, done] = a.insert(x);
                if (!done) {
                    ok = false;
                }
            }
        }
        if (!ok) {
            must.add(in[u], 1);
        }
        return pair(ok, std::move(a));
    }(root, root);
    assert(must.sum(in[root], in[root] + 1));
    vector<int> parent(2 * N, -1);
    [&](this auto &&self, int u) -> void {
        for (auto v : adj[u]) {
            if (v == parent[u])
                continue;
            parent[v] = u;
            self(v);
        }
    }(root);
    for (auto i = 2 * N - 1; 0 <= i; --i) {
        if (must.sum(in[i], out[i]))
            continue;
        [&](this auto &&self, int u) -> void {
            active[u] = false;
            must.add(in[twin(u)], 1);
            for (auto v : adj[u]) {
                if (v == parent[u] || !active[v])
                    continue;
                self(v);
            }
        }(i);
    }
    vector<int> ans;
    for (auto i = 0; i < 2 * N; ++i) {
        if (active[i]) {
            ans.push_back(i);
        }
    }
    cout << ans.size() << "\n";
    show<1>(ans);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int t = 1;
#ifdef TC
    cin >> t;
#endif
    for (auto i = 0; i < t; ++i) {
        solve();
    }
}
