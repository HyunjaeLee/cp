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
    vector<int> P1(N), P2(N);
    ranges::iota(P1, 1);
    ranges::iota(P2, 1);
    swap(P1[0], P1[1]);
    ranges::rotate(P2, P2.begin() + 1);
    cout << 2 << "\n";
    show(P1);
    show(P2);
    cout << flush;
    vector<int> Q(N);
    read(Q);
    vector<int> A;
    auto Swap = [&] {
        A.push_back(1);
        swap(Q[0], Q[1]);
    };
    auto Shift = [&] {
        A.push_back(2);
        ranges::rotate(Q, Q.begin() + 1);
    };
    for (auto i = 0; i < N; ++i) {
        for (auto j = 0; j < N - 1; ++j) {
            if (Q[0] > Q[1])
                Swap();
            Shift();
        }
        Shift();
    }
    cout << A.size() << " ";
    show(A);
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
