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
    if (N == 1) {
        cout << "Yes\n1\n";
        return;
    }
    if (N == 2) {
        cout << "No\n";
        return;
    }
    vector<vector<int>> A(N + 1);
    for (auto i = 3; i <= N; ++i) {
        vector<int> v;
        for (auto j = 1; j < i; ++j) {
            v.push_back(j * (j + 1));
        }
        if (ranges::binary_search(v, i)) {
            A[i].push_back(2);
            for (auto x : A[i - 1]) {
                A[i].push_back(2 * x);
            }
        } else {
            v.push_back(i);
            A[i] = v;
        }
    }
    cout << "Yes\n";
    show(A[N]);
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
