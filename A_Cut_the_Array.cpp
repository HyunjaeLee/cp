#include <bits/stdc++.h>
using namespace std;

using i8 = signed char;
using u8 = unsigned char;
using i32 = int;
using u32 = unsigned;
using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128;
using u128 = unsigned __int128;

// clang-format off
template <typename T> T ceil_div(T a, T b) { return a / b + static_cast<T>((a ^ b) > 0 && a % b != 0); }
template <typename T> T floor_div(T a, T b) { return a / b - static_cast<T>((a ^ b) < 0 && a % b != 0); }
void read(auto &a) { for (auto &x : a) cin >> x; }
void show(const auto &a, string_view sep = " ", string_view end = "\n") {
    for (auto it = a.begin(); it != a.end(); ++it) {
        if (it != a.begin()) cout << sep;
        cout << *it;
    }
    cout << end;
}
// clang-format on

#define TC
void solve() {
    int N;
    cin >> N;
    vector<int> A(N);
    read(A);
    for (auto i = 0; i < N - 1; ++i) {
        A[i + 1] += A[i];
    }
    auto a = 0, b = 0;
    for (auto i = 0; i < N; ++i) {
        for (auto j = i + 1; j <= N - 2; ++j) {
            auto x = A[i];
            auto y = A[j] - A[i];
            auto z = A[N - 1] - A[j];
            vector<int> v{x % 3, y % 3, z % 3};
            ranges::sort(v);
            if (v[0] == v[2] || v == vector{0, 1, 2}) {
                cout << i + 1 << " " << j + 1 << "\n";
                return;
            }
        }
    }
    cout << a << " " << b << "\n";
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
