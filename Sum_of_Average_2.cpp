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
    auto calc = [&](vector<int> a) {
        i64 sum = 0;
        for (auto i = 0; i < N - 1; ++i) {
            sum += (a[i] + a[i + 1]) / 2;
        }
        return sum;
    };
    auto ans = numeric_limits<i64>::max();
    { // 1 .. 1
        vector<int> B(N);
        vector<int> O, E;
        for (auto k = 0; k < N; ++k) {
            if (A[k] & 1)
                O.push_back(A[k]);
            else
                E.push_back(A[k]);
        }
        ranges::sort(O);
        ranges::sort(E);
        if (2 <= O.size()) {
            B[0] = O.back();
            O.pop_back();
            B[N - 1] = O.back();
            O.pop_back();
            for (auto k = 1; k < N - 1; ++k) {
                if (E.empty() || (!O.empty() && B[k - 1] % 2 == 0)) {
                    B[k] = O.back();
                    O.pop_back();
                } else {
                    B[k] = E.back();
                    E.pop_back();
                }
            }
            ans = min(ans, calc(B));
        }
    }
    { // 0 .. 0
        vector<int> B(N);
        vector<int> O, E;
        for (auto k = 0; k < N; ++k) {
            if (A[k] & 1)
                O.push_back(A[k]);
            else
                E.push_back(A[k]);
        }
        ranges::sort(O);
        ranges::sort(E);
        if (2 <= E.size()) {
            B[0] = E.back();
            E.pop_back();
            B[N - 1] = E.back();
            E.pop_back();
            for (auto k = 1; k < N - 1; ++k) {
                if (E.empty() || (!O.empty() && B[k - 1] % 2 == 0)) {
                    B[k] = O.back();
                    O.pop_back();
                } else {
                    B[k] = E.back();
                    E.pop_back();
                }
            }
            ans = min(ans, calc(B));
        }
    }
    { // 0 .. 1
        vector<int> B(N);
        vector<int> O, E;
        for (auto k = 0; k < N; ++k) {
            if (A[k] & 1)
                O.push_back(A[k]);
            else
                E.push_back(A[k]);
        }
        ranges::sort(O);
        ranges::sort(E);
        if (1 <= E.size() && 1 <= O.size()) {
            B[0] = E.back();
            E.pop_back();
            B[N - 1] = O.back();
            O.pop_back();
            for (auto k = 1; k < N - 1; ++k) {
                if (E.empty() || (!O.empty() && B[k - 1] % 2 == 0)) {
                    B[k] = O.back();
                    O.pop_back();
                } else {
                    B[k] = E.back();
                    E.pop_back();
                }
            }
            ans = min(ans, calc(B));
        }
    }
    { // 1 .. 0
        vector<int> B(N);
        vector<int> O, E;
        for (auto k = 0; k < N; ++k) {
            if (A[k] & 1)
                O.push_back(A[k]);
            else
                E.push_back(A[k]);
        }
        ranges::sort(O);
        ranges::sort(E);
        if (1 <= E.size() && 1 <= O.size()) {
            B[0] = O.back();
            O.pop_back();
            B[N - 1] = E.back();
            E.pop_back();
            for (auto k = 1; k < N - 1; ++k) {
                if (E.empty() || (!O.empty() && B[k - 1] % 2 == 0)) {
                    B[k] = O.back();
                    O.pop_back();
                } else {
                    B[k] = E.back();
                    E.pop_back();
                }
            }
            ans = min(ans, calc(B));
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
