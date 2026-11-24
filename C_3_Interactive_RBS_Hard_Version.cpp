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

int query_range(int l, int r) { // [l, r)
    cout << "? " << r - l << " ";
    auto v = views::iota(l, r);
    ranges::copy(v, ostream_iterator<int>(cout, " "));
    cout << endl;
    int ret;
    cin >> ret;
    return ret;
}

void solve() {
    int n;
    cin >> n;
    auto pred = [&](int i) {
        assert(1 <= i && i <= n);
        auto r = query_range(1, i + 1);
        return r == 0;
    };
    auto it = ranges::partition_point(views::iota(1, n + 1), pred);
    auto open = *it - 1;
    constexpr auto B = 13;
    vector<int> T;
    for (auto i = 1; T.empty() || T.back() < (1 << B); ++i) {
        T.push_back(i * (i + 1) / 2);
    }
    auto query = [&](array<int, B> idx) -> int {
        vector<int> a;
        for (auto i = 0; i < B; ++i) {
            auto x = (1 << i);
            vector<int> v;
            for (auto j = int(T.size()) - 1; 0 <= j; --j) {
                auto t = T[j];
                while (t <= x) {
                    x -= t;
                    v.push_back(j + 1);
                }
            }
            for (auto s : v) {
                a.push_back(open);
                for (auto z = 0; z < s; ++z) {
                    a.push_back(open);
                    a.push_back(idx[i]);
                }
            }
        }
        cout << "? " << size(a) << " ";
        ranges::copy(a, ostream_iterator<int>(cout, " "));
        cout << endl;
        int r;
        cin >> r;
        return r;
    };
    string ans(n, '$');
    for (auto i = 1; i <= n; i += B) {
        array<int, B> idx;
        for (auto j = 0; j < B; ++j) {
            idx[j] = min(n, i + j);
        }
        auto mask = query(idx);
        for (auto j = 0; j < B; ++j) {
            if ((mask >> j) & 1) {
                ans[min(n, i + j) - 1] = ')';
            } else {
                ans[min(n, i + j) - 1] = '(';
            }
        }
    }
    cout << "! " << ans << endl;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}
