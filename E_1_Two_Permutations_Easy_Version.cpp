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
    int N, M;
    cin >> N >> M;
    vector<int> A(N), B(M);
    read<1>(A);
    read<1>(B);
    vector<int> op_a, op_b;
    auto swap_a = [&](int i, int j) {
        assert(i != j);
        if (i > j)
            swap(i, j);
        swap(A[i], A[j]);
        auto s1 = i;
        auto s2 = j - i - 1;
        auto s3 = N - j - 1;
        op_a.push_back(s1);
        op_a.push_back(s2);
        op_a.push_back(s3);
    };
    auto swap_b = [&](int i, int j) {
        assert(i != j);
        if (i > j)
            swap(i, j);
        swap(B[i], B[j]);
        auto s1 = i;
        auto s2 = j - i - 1;
        auto s3 = M - j - 1;
        op_b.push_back(s1);
        op_b.push_back(s2);
        op_b.push_back(s3);
    };
    for (auto i = 0; i < N - 1; ++i) {
        auto p = -1;
        for (auto j = 0; j < N; ++j) {
            if (A[j] == i) {
                p = j;
            }
        }
        if (p != i) {
            swap_a(i, p);
        }
    }
    for (auto i = 0; i < M - 1; ++i) {
        auto p = -1;
        for (auto j = 0; j < M; ++j) {
            if (B[j] == i) {
                p = j;
            }
        }
        if (p != i) {
            swap_b(i, p);
        }
    }
    if ((op_a.size() & 1) != (op_b.size() & 1)) {
        if (N % 2 == 0 && M % 2 == 0) {
            cout << "-1\n";
            return;
        }
        if (N & 1) {
            for (auto i = 0; i < N; ++i) {
                op_a.push_back(0);
            }
        } else {
            for (auto i = 0; i < M; ++i) {
                op_b.push_back(0);
            }
        }
    }
    while (op_a.size() < op_b.size()) {
        op_a.push_back(0);
        op_a.push_back(N - 1);
    }
    while (op_a.size() > op_b.size()) {
        op_b.push_back(0);
        op_b.push_back(M - 1);
    }
    auto k = int(op_a.size());
    cout << k << "\n";
    for (auto i = 0; i < k; ++i) {
        cout << op_a[i] + 1 << " " << op_b[i] + 1 << "\n";
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
