#include <bits/stdc++.h>
using namespace std;

using i8 = signed char;
using u8 = unsigned char;
using i32 = int;
using u32 = unsigned;
using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128;
using u128 = unsigned __int128;

// clang-format off
template <typename T> T ceil_div(T a, T b) { return a / b + static_cast<T>((a ^ b) > 0 && a % b != 0); }
template <typename T> T floor_div(T a, T b) { return a / b - static_cast<T>((a ^ b) < 0 && a % b != 0); }
void read(auto &a) { for (auto &x : a) cin >> x; }
void show(const auto &a, string_view sep = " ", string_view end = "\n") {
    for (auto it = a.begin(); it != a.end(); ++it) {
        if (it != a.begin()) cout << sep;
        cout << *it;
    }
    cout << end;
}
// clang-format on

#define TC
void solve() {
    int N;
    cin >> N;
    vector<i64> A(N);
    read(A);
    vector<int> I;
    for (auto i = 0; i < N; ++i) {
        if (i == 0 || i == N - 1 || (A[i - 1] & 1) != (A[i + 1] & 1)) {
            I.push_back(i);
        }
    }
    vector<pair<int, int>> rng;
    for (auto i = 0; i < int(I.size()) - 1; ++i) {
        auto l = I[i], r = I[i + 1] + 1;
        rng.emplace_back(l, r);
    }
    for (auto [l, r] : rng) {
        vector<i64> v(A.begin() + l, A.begin() + r);
        for (auto i = r - l - 2; 0 <= i; --i) {
            v[i + 1] -= v[i];
        }
        sort(v.begin() + 1, v.end());
        for (auto i = 0; i < r - l - 1; ++i) {
            v[i + 1] += v[i];
        }
        for (auto i = 0; i < r - l; ++i) {
            A[l + i] = v[i];
        }
    }
    show(A);
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
