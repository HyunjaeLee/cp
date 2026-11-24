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
    for (auto i = 0; i < N - 1; ++i) {
        if (abs(A[i] - A[i + 1]) >= 2) {
            cout << "0\n";
            return;
        }
    }
    vector<int> S(N, -1);
    for (auto i = 0; i < N - 1; ++i) {
        if (A[i + 1] - A[i] == 0) {
            if (S[i] != -1) {
                S[i + 1] = S[i] ^ 1;
            }
        } else if (A[i + 1] - A[i] == 1) {
            S[i] = S[i + 1] = 0;
        } else if (A[i + 1] - A[i] == -1) {
            S[i] = S[i + 1] = 1;
        }
    }
    for (auto i = N - 2; 0 <= i; --i) {
        if (A[i + 1] - A[i] == 0) {
            if (S[i + 1] != -1) {
                S[i] = S[i + 1] ^ 1;
            }
        }
    }
    auto F = [&] {
        vector<int> P(N + 1);
        for (auto i = 0; i < N; ++i) {
            P[i + 1] = S[i] + P[i];
        }
        auto Count = [&](int l, int r, int x) {
            auto sum = P[r] - P[l];
            return x ? sum : r - l - sum;
        };
        for (auto i = 0; i < N; ++i) {
            if (A[i] != Count(0, i, 0) + 1 + Count(i + 1, N, 1)) {
                return 0;
            }
        }
        return 1;
    };
    auto ans = 0;
    if (ranges::fold_left(S, 0, plus()) == -N) {
        S[0] = 0;
        for (auto i = 1; i < N; ++i) {
            S[i] = S[i - 1] ^ 1;
        }
        ans += F();
        for (auto i = 0; i < N; ++i) {
            S[i] ^= 1;
        }
        ans += F();
    } else {
        ans = F();
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
