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
    auto MAX_X = 500000;
    int N;
    cin >> N;
    vector<int> A(N), B(N);
    for (auto i = 0; i < N; ++i) {
        cin >> A[i] >> B[i];
    }
    map<pair<int, int>, int> F;
    for (auto i = 0; i < N; ++i) {
        F[{A[i], B[i]}]++;
    }
    vector<i64> E(MAX_X + 1);
    for (auto [p, f] : F) {
        auto [a, b] = p;
        for (auto x = b - a; x <= MAX_X; x += b) {
            E[x] -= i64(b) * f;
        }
    }
    inclusive_scan(begin(E), end(E), begin(E));
    auto sum = ranges::fold_left(A, 0LL, plus());
    for (auto x = 0; x <= MAX_X; ++x) {
        E[x] += i64(N) * x + sum;
    }
    int Q;
    cin >> Q;
    while (Q--) {
        int x;
        cin >> x;
        cout << E[x] << "\n";
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
