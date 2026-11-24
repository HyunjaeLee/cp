
#include <atcoder/segtree>
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
    vector<int> A(N), B(N);
    read(A);
    read(B);
    ranges::sort(A);
    ranges::sort(B);
    auto op = [](int a, int b) { return max(a, b); };
    auto e = [] { return 0; };
    atcoder::segtree<int, op, e> seg(N);
    auto j = N - 1;
    auto check = [&](array<int, 3> a) {
        ranges::sort(a);
        return a[0] + a[1] > a[2];
    };
    for (auto i = N - 1; 0 <= i; --i) {
        vector<int> re;
        while (0 <= j) {
            auto it = ranges::upper_bound(A, B[j]);
            if (it <= A.begin() + i)
                break;
            auto gap = 1'123'123'123;
            if (it != A.end()) {
                gap = *it - B[j];
            }
            if (it != A.begin()) {
                auto prv = prev(it);
                if (i != 0 && prv == A.begin() + i) {
                    --prv;
                }
                if (prv != A.begin() + i) {
                    gap = min(gap, B[j] - *prv);
                }
            }
            seg.set(j, gap);
            re.push_back(j);
            --j;
        }
        auto awin = seg.all_prod() < A[i];
        if ((i == 0 || !check({A[i], A[i - 1], B[0]})) && (i == N - 1 || !check({A[i], A[i + 1], B[0]}))) {
            awin = false;
        }
        if (awin) {
            cout << "Alice\n";
            return;
        }
        for (auto p : re) {
            auto it = ranges::upper_bound(A, B[p]);
            auto gap = 1'123'123'123;
            if (it != A.end()) {
                gap = *it - B[p];
            }
            if (it != A.begin()) {
                auto prv = prev(it);
                gap = min(gap, B[p] - *prv);
            }
            seg.set(p, gap);
        }
    }
    cout << "Bob\n";
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
