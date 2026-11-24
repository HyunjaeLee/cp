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
    vector<int> A(N);
    read<1>(A);
    vector<pair<int, int>> ans;
    auto Act = [&](auto i, auto j) {
        auto x = A[i];
        auto y = A[i + 1];
        A.erase(A.begin() + i);
        A.erase(A.begin() + i);
        A.insert(A.begin() + j, y);
        A.insert(A.begin() + j, x);
        ans.emplace_back(i + 1, j);
    };
    for (auto i = 0; i < N - 2; ++i) {
        auto pos = ranges::find(A, i) - A.begin();
        if (pos == N - 1) {
            Act(pos - 1, N - 3);
            pos--;
        }
        Act(pos, i);
    }
    if (!ranges::is_sorted(A)) {
        cout << "No\n";
        return;
    }
    cout << "Yes\n";
    cout << ans.size() << "\n";
    for (auto [i, j] : ans) {
        cout << i << " " << j << "\n";
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
