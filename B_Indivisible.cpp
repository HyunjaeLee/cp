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

bool check(vector<int> a) {
    auto n = int(a.size());
    for (auto i = 0; i < n; ++i) {
        auto sum = 0;
        for (auto j = i; j < n; ++j) {
            sum += a[j];
            if (i < j && sum % (j - i + 1) == 0) {
                return false;
            }
        }
    }
    return true;
}

#define TC
void solve() {
    int N;
    cin >> N;
    if (N <= 2) {
        show(views::iota(1, N + 1));
        return;
    }
    if (N % 2) {
        cout << "-1\n";
        return;
    }
    vector<int> A(N);
    ranges::iota(A, 1);
    for (auto i = 0; i < N; i += 2) {
        swap(A[i], A[i + 1]);
    }
    show(A);
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
