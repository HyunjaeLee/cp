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
    read(A);
    vector<int> ss(N);
    auto go = [&](array<int, 3> X) {
        vector<deque<int>> I(3);
        for (auto i = 0; i < N; ++i) {
            for (auto j = 0; j < 3; ++j) {
                if (X[j] == A[i]) {
                    I[j].push_back(i);
                }
            }
        }
        array<int, 3> ptr{-1, -1, -1};
        for (auto i = 0; i < N; ++i) {
            auto ok = true;
            for (auto j = 0; j < 3; ++j) {
                while (!I[j].empty() && j != 0 && ptr[j - 1] >= I[j].front()) {
                    I[j].pop_front();
                }
                if (I[j].empty()) {
                    ok = false;
                    break;
                }
                ptr[j] = I[j].front();
                I[j].pop_front();
            }
            if (!ok) {
                break;
            }
            auto len = N - ranges::max(ptr);
            ss[i] = max(ss[i], len);
            for (auto j = 0; j < 3; ++j) {
                if (i != ptr[j]) {
                    I[j].push_front(ptr[j]);
                }
                ptr[j] = -1;
            }
        }
    };
    for (auto i = 1; i <= 10; ++i) {
        for (auto j = 1; j <= 10; ++j) {
            for (auto k = 1; k <= 10; ++k) {
                if (j - i == k - j) {
                    go({i, j, k});
                }
            }
        }
    }
    auto ans = ranges::fold_left(ss, 0LL, plus());
    cout << ans << endl;
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
