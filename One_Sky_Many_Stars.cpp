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
    vector<i64> A(N), B(N);
    read(A);
    read(B);
    auto good = 0;
    constexpr auto inf = numeric_limits<i64>::max() / 2;
    auto update = [&](int i, int w) {
        if (i < 0 || N <= i)
            return;
        auto l = A[i] - B[i];
        auto r = A[i] + B[i];
        // bad <=> both l and r are hidden

        auto ll = 0 <= i - 1 ? A[i - 1] - B[i - 1] : -inf;
        auto lr = 0 <= i - 1 ? A[i - 1] + B[i - 1] : -inf;
        auto rl = i + 1 < N ? A[i + 1] - B[i + 1] : inf;
        auto rr = i + 1 < N ? A[i + 1] + B[i + 1] : inf;

        auto bad_l = (ll < l && l < lr) || (rl < l && l < rr);
        auto bad_r = (ll < r && r < lr) || (rl < r && r < rr);

        auto bad = bad_l && bad_r;

        if (!bad) {
            good += w;
        }
    };
    for (auto i = 0; i < N; ++i) {
        update(i, 1);
    }
    int Q;
    cin >> Q;
    while (Q--) {
        int i, s;
        cin >> i >> s;
        --i;
        update(i - 1, -1);
        update(i, -1);
        update(i + 1, -1);
        B[i] = s;
        update(i - 1, 1);
        update(i, 1);
        update(i + 1, 1);
        if (good == N) {
            cout << "Yes\n";
        } else {
            cout << "No\n";
        }
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
