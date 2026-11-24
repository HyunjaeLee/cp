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

int safe_mod(int a, int n) { return ((a % n) + n) % n; }

void solve() {
    int N;
    cin >> N;
    vector<int> A(N);
    read(A);
    vector<i64> G(N);
    vector<i64> pref(N), suff(N);
    auto add_pref = [&](int l, int r, int x) {
        assert(l <= r);
        pref[l] += x;
        if (l + 1 < N) pref[l + 1] -= x;
        if (l + 1 < N) pref[l + 1] += 1;
        if (r + 1 < N) pref[r + 1] -= 1;
        if (r + 1 < N) pref[r + 1] -= x + (r - l);
        if (r + 2 < N) pref[r + 2] += x + (r - l);
    };
    auto add_suff = [&](int l, int r, int x) {
        assert(l <= r);
        suff[r] += x;
        if (0 <= r - 1) suff[r - 1] -= x;
        if (0 <= r - 1) suff[r - 1] += 1;
        if (0 <= l - 1) suff[l - 1] -= 1;
        if (0 <= l - 1) suff[l - 1] -= x + (r - l);
        if (0 <= l - 2) suff[l - 2] += x + (r - l);
    };
    auto act_pref = [&](int l, int r) {
        l = safe_mod(l, N);
        r = safe_mod(r, N);
        if (l <= r) {
            add_pref(l, r, 0);
        } else {
            add_pref(l, N - 1, 0);
            add_pref(0, r, 1 + N - l - 1);
        }
    };
    auto act_suff = [&](int l, int r) {
        l = safe_mod(l, N);
        r = safe_mod(r, N);
        if (l <= r) {
            add_suff(l, r, 0);
        } else {
            add_suff(0, r, 0);
            add_suff(l, N - 1, 1 + r);
        }
    };
    for (auto i = 0; i < N; ++i) {
        auto s = (N + A[i] - i) % N;
        act_pref(-s, -s + N / 2);
        act_suff(-s + N / 2 + 1, -s + N);
    }
    for (auto i = 0; i < N - 1; ++i) pref[i + 1] += pref[i];
    for (auto i = 0; i < N - 1; ++i) pref[i + 1] += pref[i];
    for (auto i = N - 1; 0 < i; --i) suff[i - 1] += suff[i];
    for (auto i = N - 1; 0 < i; --i) suff[i - 1] += suff[i];
    for (auto i = 0; i < N; ++i) {G[i] = pref[i] + suff[i];}
    cout << ranges::min(G) << "\n";
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
