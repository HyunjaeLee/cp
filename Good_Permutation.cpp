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

#define TC
void solve() {
    int N;
    cin >> N;
    vector<int> A(N);
    read<1>(A);
    vector<bool> visited(N);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    for (auto i = 0; i < N; ++i) {
        if (visited[i])
            continue;
        pair<int, int> e = {A[i], i};
        auto dfs = [&](this auto &&self, int u) -> void {
            e = min(e, {A[u], u});
            visited[u] = true;
            auto v = A[u];
            if (!visited[v]) {
                self(v);
            }
        };
        dfs(i);
        if (i != 0) {
            pq.push(e);
        }
    }
    for (auto i = 0; !pq.empty() && i < N; ++i) {
        auto [x, pos] = pq.top();
        if (x < A[i] || i == x - 1) {
            swap(A[i], A[pos]);
            pq.pop();
        }
    }
    show<1>(A);
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
