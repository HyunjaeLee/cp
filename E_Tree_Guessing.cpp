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
    auto query = [&](const vector<int> &a) {
        cout << "? 1 ";
        show(a);
        cout << flush;
        int r;
        cin >> r;
        if (r == -1)
            exit(0);
        return r;
    };
    vector<int> sz(N);
    sz[0] = N;
    for (auto i = 1; i < N; ++i) {
        vector<int> a(N, -1);
        a[0] = N - 1;
        a[i] = N;
        auto p = 1;
        for (auto j = 0; j < N; ++j) {
            if (a[j] == -1) {
                a[j] = p++;
            }
        }
        auto sum = query(a);
        sz[i] = sum - N * (N - 1);
    }
    vector<int> parent(N, -1);
    vector<int> I(N);
    ranges::iota(I, 0);
    ranges::sort(I, {}, [&](int i) { return -sz[i]; });
    for (auto i : I | views::drop(1)) {
        vector<int> a(N, -1);
        a[i] = 1;
        auto p = 2;
        for (auto j = 0; j < N; ++j) {
            if (a[I[j]] == -1) {
                a[I[j]] = p++;
            }
        }
        auto sum = query(a);
        auto x = sum - (N + 2) * (N - 1) / 2;
        for (auto j = 0; j < N; ++j) {
            if (a[j] == x) {
                parent[i] = j;
            }
        }
    }
    cout << "!\n";
    for (auto i = 1; i < N; ++i) {
        cout << i + 1 << " " << parent[i] + 1 << "\n";
    }
    cout << flush;
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
