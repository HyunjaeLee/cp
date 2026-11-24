#include <atcoder/fenwicktree>
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
    string S;
    cin >> N >> S;
    atcoder::fenwick_tree<int> A(N), B(N), C(N);
    for (auto i = 0; i < N; ++i) {
        if (S[i] == 'A') {
            A.add(i, 1);
        } else if (S[i] == 'B') {
            B.add(i, 1);
        } else {
            C.add(i, 1);
        }
    }
    auto ok = 3 <= A.sum(0, N) && 3 <= B.sum(0, N) && 3 <= C.sum(0, N);
    if (!ok) {
        cout << "0\n";
        return;
    }
    auto L = -1, R = -1;
    {
        set<int> st;
        for (auto i = 0; i < N; ++i) {
            st.insert(S[i]);
            if (st.size() == 3) {
                L = i + 1;
                break;
            }
        }
    }
    {
        set<int> st;
        for (auto i = N - 1; 0 <= i; --i) {
            st.insert(S[i]);
            if (st.size() == 3) {
                R = i;
                break;
            }
        }
    }
    i64 ans = 0;
    for (auto i = L; i < R; ++i) {
        auto pred = [&](int j) {
            auto r = A.sum(i, j + 1) && B.sum(i, j + 1) && C.sum(i, j + 1);
            return !r;
        };
        auto it = ranges::partition_point(views::iota(i, R), pred);
        ans += R - *it;
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
