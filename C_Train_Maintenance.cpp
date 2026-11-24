
#include <cassert>
#include <vector>


#include <cassert>
#include <numeric>
#include <type_traits>

namespace atcoder {

namespace internal {

#ifndef _MSC_VER
template <class T>
using is_signed_int128 =
    typename std::conditional<std::is_same<T, __int128_t>::value ||
                                  std::is_same<T, __int128>::value,
                              std::true_type,
                              std::false_type>::type;

template <class T>
using is_unsigned_int128 =
    typename std::conditional<std::is_same<T, __uint128_t>::value ||
                                  std::is_same<T, unsigned __int128>::value,
                              std::true_type,
                              std::false_type>::type;

template <class T>
using make_unsigned_int128 =
    typename std::conditional<std::is_same<T, __int128_t>::value,
                              __uint128_t,
                              unsigned __int128>;

template <class T>
using is_integral = typename std::conditional<std::is_integral<T>::value ||
                                                  is_signed_int128<T>::value ||
                                                  is_unsigned_int128<T>::value,
                                              std::true_type,
                                              std::false_type>::type;

template <class T>
using is_signed_int = typename std::conditional<(is_integral<T>::value &&
                                                 std::is_signed<T>::value) ||
                                                    is_signed_int128<T>::value,
                                                std::true_type,
                                                std::false_type>::type;

template <class T>
using is_unsigned_int =
    typename std::conditional<(is_integral<T>::value &&
                               std::is_unsigned<T>::value) ||
                                  is_unsigned_int128<T>::value,
                              std::true_type,
                              std::false_type>::type;

template <class T>
using to_unsigned = typename std::conditional<
    is_signed_int128<T>::value,
    make_unsigned_int128<T>,
    typename std::conditional<std::is_signed<T>::value,
                              std::make_unsigned<T>,
                              std::common_type<T>>::type>::type;

#else

template <class T> using is_integral = typename std::is_integral<T>;

template <class T>
using is_signed_int =
    typename std::conditional<is_integral<T>::value && std::is_signed<T>::value,
                              std::true_type,
                              std::false_type>::type;

template <class T>
using is_unsigned_int =
    typename std::conditional<is_integral<T>::value &&
                                  std::is_unsigned<T>::value,
                              std::true_type,
                              std::false_type>::type;

template <class T>
using to_unsigned = typename std::conditional<is_signed_int<T>::value,
                                              std::make_unsigned<T>,
                                              std::common_type<T>>::type;

#endif

template <class T>
using is_signed_int_t = std::enable_if_t<is_signed_int<T>::value>;

template <class T>
using is_unsigned_int_t = std::enable_if_t<is_unsigned_int<T>::value>;

template <class T> using to_unsigned_t = typename to_unsigned<T>::type;

}  // namespace internal

}  // namespace atcoder


namespace atcoder {

template <class T> struct fenwick_tree {
    using U = internal::to_unsigned_t<T>;

  public:
    fenwick_tree() : _n(0) {}
    explicit fenwick_tree(int n) : _n(n), data(n) {}

    void add(int p, T x) {
        assert(0 <= p && p < _n);
        p++;
        while (p <= _n) {
            data[p - 1] += U(x);
            p += p & -p;
        }
    }

    T sum(int l, int r) {
        assert(0 <= l && l <= r && r <= _n);
        return sum(r) - sum(l);
    }

  private:
    int _n;
    std::vector<U> data;

    U sum(int r) {
        U s = 0;
        while (r > 0) {
            s += data[r - 1];
            r -= r & -r;
        }
        return s;
    }
};

}  // namespace atcoder

#line 2 "C_Train_Maintenance.cpp"
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
    vector<pair<int, int>> A(N);
    for (auto &[x, y] : A) {
        cin >> x >> y;
    }
    atcoder::fenwick_tree<int> ft(M + 1);
    auto add_large = [&](int t, int k) {
        auto [x, y] = A[k];
        for (i64 i = t; i < M; i += x + y) {
            auto l = (int)min<i64>(M, i + x);
            auto r = (int)min<i64>(M, i + x + y);
            ft.add(l, 1);
            ft.add(r, -1);
        }
    };
    auto remove_large = [&](int t, int k) {
        auto [x, y] = A[k];
        for (i64 i = t; i < M; i += x + y) {
            auto l = (int)min<i64>(M, i + x);
            auto r = (int)min<i64>(M, i + x + y);
            ft.add(l, -1);
            ft.add(r, 1);
        }
    };
    auto query_large = [&](int t) { return ft.sum(0, t + 1); };
    constexpr auto B = 250;
    vector<vector<int>> F(B);
    for (auto i = 0; i < B; ++i) {
        F[i].resize(i);
    }
    auto add_small = [&](int t, int k) {
        auto [x, y] = A[k];
        assert(x + y < B);
        auto P = x + y;
        for (auto i = t + x; i < t + x + y; ++i) {
            ++F[P][i % P];
        }
    };
    auto remove_small = [&](int t, int k) {
        auto [x, y] = A[k];
        assert(x + y < B);
        auto P = x + y;
        for (auto i = t + x; i < t + x + y; ++i) {
            --F[P][i % P];
        }
    };
    auto query_small = [&](int t) {
        auto sum = 0;
        for (auto i = 2; i < B; ++i) {
            sum += F[i][t % i];
        }
        return sum;
    };
    vector<int> history(N, -1);
    auto add = [&](int t, int k) {
        auto [x, y] = A[k];
        if (x + y < B)
            add_small(t, k);
        else
            add_large(t, k);
    };
    auto remove = [&](int t, int k) {
        auto [x, y] = A[k];
        if (x + y < B)
            remove_small(t, k);
        else
            remove_large(t, k);
    };
    auto query = [&](int t) { return query_small(t) + query_large(t); };
    for (auto i = 0; i < M; ++i) {
        int op, k;
        cin >> op >> k;
        --k;
        if (op == 1) {
            history[k] = i;
            add(i, k);
        } else {
            remove(history[k], k);
            history[k] = -1;
        }
        cout << query(i) << "\n";
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