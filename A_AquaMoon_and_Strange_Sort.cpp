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

#include <atcoder/fenwicktree>

#define TC
void solve() {
    int N;
    cin >> N;
    vector<int> A(N);
    read(A);
    vector<int> I(N);
    const auto M = ranges::max(A) + 1;
    {
        atcoder::fenwick_tree<int> ft(M);
        for (auto i = 0; i < N; ++i) {
            I[i] += ft.sum(A[i] + 1, M);
            ft.add(A[i], 1);
        }
    }
    {
        atcoder::fenwick_tree<int> ft(M);
        for (auto i = N - 1; 0 <= i; --i) {
            I[i] += ft.sum(0, A[i]);
            ft.add(A[i], 1);
        }
    }
    vector<vector<int>> F(M);
    for (auto i = 0; i < N; ++i) {
        auto b = (I[i] & 1) ^ 1;
        F[A[i]].push_back(b);
    }
    for (auto x = 1; x < M; ++x) {
        vector<int> st;
        for (auto b : F[x]) {
            if (st.empty() || st.back() != b) {
                st.push_back(b);
            } else {
                st.pop_back();
            }
        }
        for (auto b : st) {
            if (b == 0) {
                cout << "NO\n";
                return;
            }
        }
    }
    cout << "YES\n";
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
