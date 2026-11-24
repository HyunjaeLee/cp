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

#include <atcoder/dsu>

#define TC
void solve() {
    int N, K;
    cin >> N >> K;
    vector<int> A(N);
    read(A);
    vector<int> F(N + 1);
    for (auto i = 0; i < N; ++i) {
        ++F[A[i]];
    }
    for (auto i = 0; i < N; ++i) {
        F[i + 1] += F[i];
    }
    auto X = 0, Y = N;
    for (auto y = 1; y <= N; ++y) {
        auto pred = [&](int x) { return K <= 2 * (F[y] - F[x - 1]) - N; };
        auto x = *ranges::partition_point(views::iota(1, y + 1), pred) - 1;
        if (x != 0 && y - x < Y - X) {
            X = x, Y = y;
        }
    }
    atcoder::dsu dsu(N);
    vector<pair<int, int>> st;
    for (auto i = 0; i < N; ++i) {
        auto s = X <= A[i] && A[i] <= Y ? 1 : -1;
        st.emplace_back(s, i);
        if (2 <= st.size() && st[int(st.size()) - 1].first * st[int(st.size()) - 2].first < 0) {
            auto [s1, p1] = st[int(st.size()) - 1];
            auto [s2, p2] = st[int(st.size()) - 2];
            st.pop_back();
            st.pop_back();
            dsu.merge(p1, p2);
        }
    }
    vector<int> S;
    for (auto i = 0; i < N; ++i) {
        if (dsu.size(i) == 1) {
            S.push_back(i);
        }
    }
    for (auto i = 0; i < N; ++i) {
        if (dsu.size(i) == 2) {
            auto it = ranges::lower_bound(S, i);
            if (it == S.end())
                --it;
            dsu.merge(*it, i);
        }
    }
    vector<int> L;
    for (auto i = 0; i < N; ++i) {
        if (dsu.leader(i) == i) {
            L.push_back(i);
        }
    }
    for (auto i = 0; i < int(L.size()) - (K - 1); ++i) {
        dsu.merge(L[0], L[i]);
    }
    cout << X << " " << Y << "\n";
    for (auto g : dsu.groups()) {
        auto [l, r] = ranges::minmax(g);
        cout << l + 1 << " " << r + 1 << "\n";
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
