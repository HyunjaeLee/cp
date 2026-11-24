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

int mex(vector<int> a) {
    auto n = int(a.size());
    vector<bool> f(n);
    for (auto i = 0; i < n; ++i) {
        if (a[i] < n) {
            f[a[i]] = true;
        }
    }
    for (auto i = 0; i < n; ++i) {
        if (!f[i]) {
            return i;
        }
    }
    return n;
}

#define TC
void solve() {
    int N, K;
    cin >> N >> K;
    --K;
    vector<int> A(N);
    read(A);
    auto x = mex(vector<int>(begin(A), begin(A) + N - K));
    if (x == N - K) {
        cout << "-1\n";
        return;
    }
    auto p = -1, q = -1;
    for (auto i = 0; i < N - K; ++i) {
        if (p == -1 || A[p] < A[i]) {
            p = i;
        }
    }
    for (auto i = N - K; i < N; ++i) {
        if (x == A[i]) {
            q = i;
            break;
        }
    }
    assert(0 <= p && 0 <= q);
    cout << p + 1 << " " << q + 1 << "\n";
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
