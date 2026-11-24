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

#ifndef ORDERED_SET_HPP
#define ORDERED_SET_HPP

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <functional>

template <typename T>
using ordered_set = __gnu_pbds::tree<T, __gnu_pbds::null_type, std::less<T>, __gnu_pbds::rb_tree_tag,
                                     __gnu_pbds::tree_order_statistics_node_update>;

#endif // ORDERED_SET_HPP

#define TC
void solve() {
    int N;
    cin >> N;
    vector<i64> p(N, -1), s(N, -1);
    s[0] = 0;
    for (auto i = 0; i < N; ++i) {
        char c;
        i64 x;
        cin >> c >> x;
        if (c == 'p') {
            p[i] = x - 1;
        } else {
            s[i] = x;
        }
    }
    vector<i64> A(N, -1);
    ordered_set<i64> S;
    for (auto i = 0; i < N; ++i) {
        S.insert(i);
    }
    for (auto i = N - 1; 0 < i;) {
        if (p[i] != -1) {
            A[i] = p[i];
            S.erase(p[i]);
            --i;
        } else {
            auto j = i - 1;
            while (s[j] == -1) {
                --j;
            }
            i64 I = 0;
            for (auto k = i - 1; j < k; --k) {
                A[k] = p[k];
                I += (int)S.size() - (int)S.order_of_key(p[k]) - 1;
                S.erase(p[k]);
            }
            auto pred = [&](int o) {
                auto x = *S.find_by_order(o);
                auto val = I + i - (int)S.order_of_key(x);
                for (auto k = i - 1; j < k; --k) {
                    val -= 2 * int(p[k] < x);
                }
                return val > s[i] - s[j];
            };
            auto it = ranges::partition_point(views::iota(0, (int)S.size()), pred);
            A[i] = *S.find_by_order(*it);
            S.erase(A[i]);
            i = j;
        }
    }
    A[0] = *S.begin();
    show<1>(A);
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
