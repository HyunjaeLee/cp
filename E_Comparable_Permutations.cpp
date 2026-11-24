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
    auto query = [&](int i, int j) {
        assert(0 <= i && i < N);
        assert(0 <= j && j < N);
        cout << "? " << i + 1 << " " << j + 1 << endl;
        int r;
        cin >> r;
        if (r == -1)
            exit(0);
        return r;
    };
    auto answer = [&](vector<int> a) {
        cout << "! ";
        show<1>(a, " ", "");
        cout << endl;
    };
    vector<int> lt(N - 1);
    for (auto i = 0; i < N - 1; ++i) {
        lt[i] = query(i, i + 1);
    }
    auto pivot = -1;
    for (auto i = N - 3; 0 <= i; --i) {
        if (lt[i] && !lt[i + 1]) {
            pivot = i;
            break;
        }
    }
    if (pivot == -1) {
        cout << "! -1" << endl;
        return;
    }
    auto l = pivot + 1;
    auto mid = N;
    for (auto i = l; i < N - 2; ++i) {
        if (!lt[i] && lt[i + 1]) {
            mid = i + 1;
            break;
        }
    }
    vector<int> A(N);
    ranges::iota(A, 0);
    auto r = int(ranges::lower_bound(A.begin() + mid, A.end(), l, query) - A.begin());
    ranges::reverse(A.begin() + l, A.begin() + mid);
    ranges::inplace_merge(A.begin() + l, A.begin() + mid, A.begin() + r, query);
    auto it = ranges::lower_bound(A.begin() + l, A.begin() + r, pivot, query);
    swap(A[pivot], *it);
    answer(A);
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
