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

// https://en.wikipedia.org/wiki/Havel–Hakimi_algorithm
// O(N + M log N)
std::optional<std::vector<std::pair<int, int>>> havel_hakimi(std::vector<int> deg) {
    auto n = int(deg.size());
    std::priority_queue<std::pair<int, int>> pq;
    for (auto i = 0; i < n; ++i) {
        assert(0 <= deg[i]);
        if (0 < deg[i]) {
            pq.emplace(deg[i], i);
        }
    }
    std::vector<std::pair<int, int>> edges;
    while (!pq.empty()) {
        auto [k, u] = pq.top();
        pq.pop();
        if (int(pq.size()) < k) {
            return std::nullopt;
        }
        for (auto i = 0; i < k; ++i) {
            auto [d, v] = pq.top();
            pq.pop();
            --deg[v];
            edges.emplace_back(u, v);
        }
        for (auto [_, v] : edges | std::views::reverse | std::views::take(k)) {
            if (0 < deg[v]) {
                pq.emplace(deg[v], v);
            }
        }
    }
    return edges;
}

void solve() {
    int N, S;
    cin >> N >> S;
    vector<int> deg(N);
    read(deg);
    auto opt = havel_hakimi(deg);
    if (!opt) {
        cout << "No\n";
        return;
    }
    auto edges = *opt;
    cout << "Yes\n";
    cout << S / 2 << "\n";
    for (auto [u, v] : edges) {
        cout << u + 1 << " " << v + 1 << "\n";
    }
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
