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
    int N, Q;
    cin >> N >> Q;
    vector<int> A(N), rank(1);
    vector<vector<int>> V(1);
    auto comp = [&](const vector<int> &a, const vector<int> &b) {
        auto n = int(a.size());
        auto m = int(b.size());
        for (auto i = 0; i < min(n, m); ++i) {
            if (rank[a[i]] != rank[b[i]]) {
                return rank[a[i]] < rank[b[i]];
            }
        }
        return n < m;
    };
    auto create = [&](const vector<int> &v) {
        auto r = 0;
        vector<bool> rerank(V.size());
        for (auto i = 0; i < int(V.size()); ++i) {
            if (comp(V[i], v)) {
                ++r;
            } else if (comp(v, V[i])) {
                rerank[i] = true;
            } else {
                return i;
            }
        }
        for (auto i = 0; i < int(V.size()); ++i) {
            if (rerank[i]) {
                ++rank[i];
            }
        }
        rank.push_back(r);
        V.push_back(v);
        return int(V.size()) - 1;
    };
    auto act = [&](int p, int q) {
        auto v = V[A[p]];
        auto it = ranges::lower_bound(v, A[q], [&](int a, int b) { return rank[a] > rank[b]; });
        v.insert(it, A[q]);
        A[p] = create(v);
    };
    while (Q--) {
        char c;
        int i, j;
        cin >> c >> i >> j;
        --i, --j;
        if (c == '!') {
            act(i, j);
        } else {
            if (rank[A[i]] < rank[A[j]]) {
                cout << "<\n";
            } else if (rank[A[i]] > rank[A[j]]) {
                cout << ">\n";
            } else {
                cout << "=\n";
            }
        }
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
