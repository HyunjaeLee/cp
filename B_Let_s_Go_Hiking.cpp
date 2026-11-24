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
    auto ans = 0;
    vector<array<int, 3>> W;
    for (auto i = 1; i < N - 1; ++i) {
        if (A[i - 1] < A[i] && A[i] > A[i + 1]) {
            auto l = i - 1;
            while (0 <= l - 1 && A[l - 1] < A[l]) {
                l--;
            }
            auto r = i + 1;
            while (r + 1 < N && A[r] > A[r + 1]) {
                r++;
            }
            W.push_back({l, i, r});
        }
    }
    multiset<int> S;
    if (A[N - 2] < A[N - 1]) {
        auto l = N - 2;
        while (0 <= l - 1 && A[l - 1] < A[l]) {
            l--;
        }
        S.insert(N - 1 - l);
    }
    if (A[0] > A[1]) {
        auto r = 1;
        while (r + 1 < N && A[r] > A[r + 1]) {
            r++;
        }
        S.insert(r - 0);
    }
    for (auto [l, i, r] : W) {
        auto x = i - l;
        auto y = r - i;
        S.insert(x);
        S.insert(y);
    }
    for (auto [l, i, r] : W) {
        auto ok = true;
        {
            auto x = i - l;
            auto y = r - i;
            S.erase(S.find(x));
            S.erase(S.find(y));
        }
        {
            auto x = i - l;
            if ((x & 1) == 0)
                x--;
            auto y = r - i;
            if (x >= y) {
                ok = false;
            }
        }
        {
            auto y = r - i;
            if ((y & 1) == 0)
                y--;
            auto x = i - l;
            if (y >= x) {
                ok = false;
            }
        }
        if (!S.empty()) {
            auto x = i - l;
            auto y = r - i;
            if (max(x, y) <= *S.rbegin()) {
                ok = false;
            }
        }
        {
            auto x = i - l;
            auto y = r - i;
            S.insert(x);
            S.insert(y);
        }
        if (ok) {
            ans++;
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
