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
    cin >> N;
    vector<int> A(N);
    read<1>(A);
    vector<int> I(N);
    for (auto i = 0; i < N; ++i) {
        I[A[i]] = i;
    }
    set<int> S;
    for (auto i = 0; i < N - 1; ++i) {
        S.insert(i);
    }
    vector<int> F(N, 1);
    auto update = [&](int i) {
        if (auto it = S.find(i - 1); it != S.end()) {
            S.erase(it);
        }
        if (auto it = S.find(i); it != S.end()) {
            S.erase(it);
        }
        F[i] = -1;
        if (0 <= i - 1 && F[i - 1] == F[i]) {
            S.insert(i - 1);
        }
        if (i + 1 < N && F[i] == F[i + 1]) {
            S.insert(i);
        }
    };
    vector<int> ans(N, -1);
    for (auto i : I) {
        update(i);
        if (i == 0 || i == N - 1) {
            continue;
        }
        if (F[i - 1] == F[i + 1]) {
            ans[i] = 3;
            continue;
        }
        if (auto it = S.lower_bound(i + 1); it != S.end()) {
            auto len = *it - i + 2;
            if (len % 2 == 0) {
                len++;
            }
            ans[i] = len;
        }
        if (auto it = S.lower_bound(i - 1); it != S.begin()) {
            --it;
            assert(*it < i - 1);
            auto len = i - *it + 1;
            if (len % 2 == 0) {
                len++;
            }
            if (ans[i] == -1 || len < ans[i]) {
                ans[i] = len;
            }
        }
    }
    {
        atcoder::fenwick_tree<int> ft(N);
        for (auto i = 0; i < N; ++i) {
            if (A[i] <= A[0]) {
                ft.add(i, -1);
            } else {
                ft.add(i, 1);
            }
        }
        for (auto i = 0; i < N; i += 2) {
            if (ft.sum(0, i + 1) != -1) {
                ans[0] = i + 1;
                break;
            }
        }
    }
    {
        atcoder::fenwick_tree<int> ft(N);
        for (auto i = 0; i < N; ++i) {
            if (A[i] <= A[N - 1]) {
                ft.add(i, -1);
            } else {
                ft.add(i, 1);
            }
        }
        for (auto i = N - 1; 0 <= i; i -= 2) {
            if (ft.sum(i, N) != -1) {
                ans[N - 1] = N - i;
                break;
            }
        }
    }
    show(ans);
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
