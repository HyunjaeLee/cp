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
    int N, K;
    cin >> N >> K;
    if (N == 4 && K == 3) {
        cout << "-1\n";
        return;
    }
    auto mask = N - 1;
    vector<int> f(N);
    for (auto i = 0; i < N; ++i) {
        f[i] = mask ^ i;
    }
    if (K == N - 1) {
        f[N - 1] = N - 2;
        f[N - 2] = N - 1;
        f[N - 3] = 1;
        f[1] = N - 3;
        f[2] = 0;
        f[0] = 2;
    } else {
        auto a = K, b = N - 1, c = (K ^ mask), d = 0;
        f[a] = b;
        f[b] = a;
        f[c] = d;
        f[d] = c;
    }
    set<pair<int, int>> ans;
    for (auto i = 0; i < N; ++i) {
        ans.insert(minmax(i, f[i]));
    }
    assert(ssize(ans) == N / 2);
    i64 sum = 0;
    for (auto [x, y] : ans) {
        cout << x << " " << y << "\n";
        sum += x & y;
    }
    assert(sum == K);
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
