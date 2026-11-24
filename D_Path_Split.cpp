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
    read(A);
    auto ans = N;
    for (auto t = 0; t < 2; ++t) {
        vector<set<int>> F(2 * N + 2);
        for (auto i = 0; i < N; ++i) {
            F[A[i]].insert(i);
        }
        for (auto x = 1; x <= 2 * N; ++x) {
            if ((x & 1) == (t & 1)) {
                for (auto l = F[x].begin(); l != F[x].end();) {
                    auto r = F[x + 1].upper_bound(*l);
                    if (r != F[x + 1].end()) {
                        --ans;
                        l = F[x].erase(l);
                        F[x + 1].erase(r);
                    } else {
                        ++l;
                    }
                }
            } else {
                for (auto r = F[x].begin(); r != F[x].end();) {
                    auto l = F[x + 1].upper_bound(*r);
                    if (l != F[x + 1].begin()) {
                        --l;
                        --ans;
                        r = F[x].erase(r);
                        F[x + 1].erase(l);
                    } else {
                        ++r;
                    }
                }
            }
        }
    }
    cout << ans << "\n";
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
