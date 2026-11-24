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

// https://suisen-cp.github.io/cp-library-cpp/library/range_query/range_chmin_chmax_add_range_sum.hpp
#line 1 "library/range_query/range_chmin_chmax_add_range_sum.hpp"

#include <algorithm>
#include <limits>

#line 1 "library/datastructure/segment_tree/segment_tree_beats.hpp"

#line 1 "library/datastructure/segment_tree/lazy_segment_tree.hpp"

#include <cassert>
#include <vector>
#line 1 "library/util/update_proxy_object.hpp"

#line 1 "library/type_traits/type_traits.hpp"

#line 5 "library/type_traits/type_traits.hpp"
#include <iostream>
#include <type_traits>

namespace suisen {
template <typename... Constraints>
using constraints_t = std::enable_if_t<std::conjunction_v<Constraints...>, std::nullptr_t>;

template <typename T, typename = std::nullptr_t> struct bitnum {
    static constexpr int value = 0;
};
template <typename T> struct bitnum<T, constraints_t<std::is_integral<T>>> {
    static constexpr int value = std::numeric_limits<std::make_unsigned_t<T>>::digits;
};
template <typename T> static constexpr int bitnum_v = bitnum<T>::value;
template <typename T, size_t n> struct is_nbit {
    static constexpr bool value = bitnum_v<T> == n;
};
template <typename T, size_t n> static constexpr bool is_nbit_v = is_nbit<T, n>::value;

template <typename T, typename = std::nullptr_t> struct safely_multipliable {
    using type = T;
};
template <typename T> struct safely_multipliable<T, constraints_t<std::is_signed<T>, is_nbit<T, 32>>> {
    using type = long long;
};
template <typename T> struct safely_multipliable<T, constraints_t<std::is_signed<T>, is_nbit<T, 64>>> {
    using type = __int128_t;
};
template <typename T> struct safely_multipliable<T, constraints_t<std::is_unsigned<T>, is_nbit<T, 32>>> {
    using type = unsigned long long;
};
template <typename T> struct safely_multipliable<T, constraints_t<std::is_unsigned<T>, is_nbit<T, 64>>> {
    using type = __uint128_t;
};
template <typename T> using safely_multipliable_t = typename safely_multipliable<T>::type;

template <typename T, typename = void> struct rec_value_type {
    using type = T;
};
template <typename T> struct rec_value_type<T, std::void_t<typename T::value_type>> {
    using type = typename rec_value_type<typename T::value_type>::type;
};
template <typename T> using rec_value_type_t = typename rec_value_type<T>::type;

template <typename T> class is_iterable {
    template <typename T_> static auto test(T_ e) -> decltype(e.begin(), e.end(), std::true_type{});
    static std::false_type test(...);

public:
    static constexpr bool value = decltype(test(std::declval<T>()))::value;
};
template <typename T> static constexpr bool is_iterable_v = is_iterable<T>::value;
template <typename T> class is_writable {
    template <typename T_> static auto test(T_ e) -> decltype(std::declval<std::ostream &>() << e, std::true_type{});
    static std::false_type test(...);

public:
    static constexpr bool value = decltype(test(std::declval<T>()))::value;
};
template <typename T> static constexpr bool is_writable_v = is_writable<T>::value;
template <typename T> class is_readable {
    template <typename T_> static auto test(T_ e) -> decltype(std::declval<std::istream &>() >> e, std::true_type{});
    static std::false_type test(...);

public:
    static constexpr bool value = decltype(test(std::declval<T>()))::value;
};
template <typename T> static constexpr bool is_readable_v = is_readable<T>::value;
} // namespace suisen

#line 5 "library/util/update_proxy_object.hpp"

namespace suisen {

template <typename T, typename UpdateFunc, constraints_t<std::is_invocable<UpdateFunc>> = nullptr>
struct UpdateProxyObject {
public:
    UpdateProxyObject(T &v, UpdateFunc update) : v(v), update(update) {}
    operator T() const { return v; }
    auto &operator++() && {
        ++v, update();
        return *this;
    }
    auto &operator--() && {
        --v, update();
        return *this;
    }
    auto &operator+=(const T &val) && {
        v += val, update();
        return *this;
    }
    auto &operator-=(const T &val) && {
        v -= val, update();
        return *this;
    }
    auto &operator*=(const T &val) && {
        v *= val, update();
        return *this;
    }
    auto &operator/=(const T &val) && {
        v /= val, update();
        return *this;
    }
    auto &operator%=(const T &val) && {
        v %= val, update();
        return *this;
    }
    auto &operator=(const T &val) && {
        v = val, update();
        return *this;
    }
    auto &operator<<=(const T &val) && {
        v <<= val, update();
        return *this;
    }
    auto &operator>>=(const T &val) && {
        v >>= val, update();
        return *this;
    }
    template <typename F, constraints_t<std::is_invocable_r<T, F, T>> = nullptr> auto &apply(F f) && {
        v = f(v), update();
        return *this;
    }

private:
    T &v;
    UpdateFunc update;
};

} // namespace suisen

#line 7 "library/datastructure/segment_tree/lazy_segment_tree.hpp"

namespace suisen {
template <typename T, T (*op)(T, T), T (*e)(), typename F, T (*mapping)(F, T), F (*composition)(F, F), F (*id)(),
          bool enable_beats = false>
struct LazySegmentTree {
    using value_type = T;
    using operator_type = F;

    LazySegmentTree() : LazySegmentTree(0) {}
    LazySegmentTree(int n) : LazySegmentTree(std::vector<value_type>(n, e())) {}
    LazySegmentTree(const std::vector<value_type> &init)
        : n(init.size()), m(ceil_pow2(n)), lg(__builtin_ctz(m)), data(2 * m, e()), lazy(m, id()) {
        std::copy(init.begin(), init.end(), data.begin() + m);
        for (int k = m - 1; k > 0; --k)
            update(k);
    }

    void apply(int l, int r, const operator_type &f) {
        assert(0 <= l and l <= r and r <= n);
        push_to(l, r);
        for (int l2 = l + m, r2 = r + m; l2 < r2; l2 >>= 1, r2 >>= 1) {
            if (l2 & 1)
                all_apply(l2++, f);
            if (r2 & 1)
                all_apply(--r2, f);
        }
        update_from(l, r);
    }
    void apply(int p, const operator_type &f) { (*this)[p] = mapping(f, get(p)); }

    value_type operator()(int l, int r) {
        assert(0 <= l and l <= r and r <= n);
        push_to(l, r);
        value_type res_l = e(), res_r = e();
        for (l += m, r += m; l < r; l >>= 1, r >>= 1) {
            if (l & 1)
                res_l = op(res_l, data[l++]);
            if (r & 1)
                res_r = op(data[--r], res_r);
        }
        return op(res_l, res_r);
    }

    value_type prod(int l, int r) { return (*this)(l, r); }
    value_type prefix_prod(int r) { return (*this)(0, r); }
    value_type suffix_prod(int l) { return (*this)(l, m); }
    value_type all_prod() const { return data[1]; }

    auto operator[](int p) {
        assert(0 <= p and p < n);
        push_to(p);
        return UpdateProxyObject{data[p + m], [this, p] { update_from(p); }};
    }
    value_type get(int p) { return (*this)[p]; }
    void set(int p, value_type v) { (*this)[p] = v; }

    template <typename Pred, constraints_t<std::is_invocable_r<bool, Pred, value_type>> = nullptr>
    int max_right(int l, Pred g) {
        assert(0 <= l && l <= n);
        assert(g(e()));
        if (l == n)
            return n;
        l += m;
        for (int i = lg; i >= 1; --i)
            push(l >> i);
        value_type sum = e();
        do {
            while ((l & 1) == 0)
                l >>= 1;
            if (not g(op(sum, data[l]))) {
                while (l < m) {
                    push(l);
                    l = 2 * l;
                    if (g(op(sum, data[l])))
                        sum = op(sum, data[l++]);
                }
                return l - m;
            }
            sum = op(sum, data[l++]);
        } while ((l & -l) != l);
        return n;
    }
    template <bool (*f)(value_type)> int max_right(int l) { return max_right(l, f); }

    template <typename Pred, constraints_t<std::is_invocable_r<bool, Pred, value_type>> = nullptr>
    int min_left(int r, Pred g) {
        assert(0 <= r && r <= n);
        assert(g(e()));
        if (r == 0)
            return 0;
        r += m;
        for (int i = lg; i >= 1; --i)
            push(r >> i);
        value_type sum = e();
        do {
            r--;
            while (r > 1 and (r & 1))
                r >>= 1;
            if (not g(op(data[r], sum))) {
                while (r < m) {
                    push(r);
                    r = 2 * r + 1;
                    if (g(op(data[r], sum)))
                        sum = op(data[r--], sum);
                }
                return r + 1 - m;
            }
            sum = op(data[r], sum);
        } while ((r & -r) != r);
        return 0;
    }
    template <bool (*f)(value_type)> int min_left(int l) { return min_left(l, f); }

private:
    int n, m, lg;
    std::vector<value_type> data;
    std::vector<operator_type> lazy;

    static constexpr int ceil_pow2(int n) {
        int m = 1;
        while (m < n)
            m <<= 1;
        return m;
    }

    void all_apply(int k, const operator_type &f) {
        data[k] = mapping(f, data[k]);
        if (k < m) {
            lazy[k] = composition(f, lazy[k]);
            if constexpr (enable_beats)
                if (data[k].fail)
                    push(k), update(k);
        }
    }
    void push(int k) {
        all_apply(2 * k, lazy[k]), all_apply(2 * k + 1, lazy[k]);
        lazy[k] = id();
    }
    void push_to(int p) {
        p += m;
        for (int i = lg; i >= 1; --i)
            push(p >> i);
    }
    void push_to(int l, int r) {
        l += m, r += m;
        int li = __builtin_ctz(l), ri = __builtin_ctz(r);
        for (int i = lg; i >= li + 1; --i)
            push(l >> i);
        for (int i = lg; i >= ri + 1; --i)
            push(r >> i);
    }
    void update(int k) { data[k] = op(data[2 * k], data[2 * k + 1]); }
    void update_from(int p) {
        p += m;
        for (int i = 1; i <= lg; ++i)
            update(p >> i);
    }
    void update_from(int l, int r) {
        l += m, r += m;
        int li = __builtin_ctz(l), ri = __builtin_ctz(r);
        for (int i = li + 1; i <= lg; ++i)
            update(l >> i);
        for (int i = ri + 1; i <= lg; ++i)
            update(r >> i);
    }
};
} // namespace suisen

#line 5 "library/datastructure/segment_tree/segment_tree_beats.hpp"

namespace suisen {
template <typename T, T (*op)(T, T), T (*e)(), typename F, T (*mapping)(F, T), F (*composition)(F, F), F (*id)()>
using SegmentTreeBeats = LazySegmentTree<T, op, e, F, mapping, composition, id, /* enable_beats = */ true>;
} // namespace suisen

#line 8 "library/range_query/range_chmin_chmax_add_range_sum.hpp"

namespace suisen {
template <typename T> struct RangeChMinMaxAddRangeSum {
    friend struct DataType;
    struct DataType {
        friend struct RangeChMinMaxAddRangeSum;

        bool fail = false;

        constexpr DataType() : lo(inf), lo2(inf), hi(-inf), hi2(-inf), sum(0), siz(0), num_lo(0), num_hi(0) {}
        constexpr DataType(T x, int num = 1)
            : lo(x), lo2(inf), hi(x), hi2(-inf), sum(x * num), siz(num), num_lo(num), num_hi(num) {}

        T get_min() const { return lo; }
        T get_max() const { return hi; }
        T get_second_min() const { return lo2; }
        T get_second_max() const { return hi2; }
        T get_min_num() const { return num_lo; }
        T get_max_num() const { return num_hi; }
        T get_sum() const { return sum; }

    private:
        T lo, lo2, hi, hi2, sum;
        int siz, num_lo, num_hi;
    };

    explicit RangeChMinMaxAddRangeSum(const int n = 0) : RangeChMinMaxAddRangeSum(std::vector<T>(n, 0)) {}
    RangeChMinMaxAddRangeSum(const std::vector<T> &init) {
        const int n = init.size();
        std::vector<DataType> a(n);
        for (int i = 0; i < n; ++i) {
            a[i] = DataType{init[i]};
        }
        seg = SegmentTreeBeats<DataType, op, e, F, mapping, composition, id>{a};
    }

    void chmin(int l, int r, T val) { seg.apply(l, r, F::chmin_query(val)); }
    void chmax(int l, int r, T val) { seg.apply(l, r, F::chmax_query(val)); }
    void update(int l, int r, T val) { seg.apply(l, r, F::update_query(val)); }
    void add(int l, int r, T val) { seg.apply(l, r, F::add_query(val)); }
    T max(int l, int r) { return seg.prod(l, r).get_max(); }
    T min(int l, int r) { return seg.prod(l, r).get_min(); }
    T sum(int l, int r) { return seg.prod(l, r).get_sum(); }
    DataType prod(int l, int r) { return seg.prod(l, r); }
    template <bool (*pred)(DataType)> int max_right(int l) { return seg.max_right<pred>(l); }
    template <typename Pred> int max_right(int l, Pred &&pred) { return seg.max_right(l, std::forward<Pred>(pred)); }
    template <bool (*pred)(DataType)> int min_left(int r) { return seg.min_left<pred>(r); }
    template <typename Pred> int min_left(int r, Pred &&pred) { return seg.min_left(r, std::forward<Pred>(pred)); }

private:
    static constexpr T inf = std::numeric_limits<T>::max() / 2;

    struct F {
        T lb, ub, add;
        constexpr F(T lb = -inf, T ub = inf, T add = 0) : lb(lb), ub(ub), add(add) {}
        static constexpr F chmin_query(T x) { return F{-inf, x, 0}; }
        static constexpr F chmax_query(T x) { return F{x, inf, 0}; }
        static constexpr F update_query(T x) { return F{x, x, 0}; }
        static constexpr F add_query(T x) { return F{-inf, inf, x}; }
    };

    static constexpr T second_lo(T lo11, T lo12, T lo21, T lo22) {
        if (lo11 == lo21)
            return std::min(lo12, lo22);
        if (lo12 <= lo21)
            return lo12;
        if (lo22 <= lo11)
            return lo22;
        return std::max(lo11, lo21);
    }
    static constexpr T second_hi(T hi11, T hi12, T hi21, T hi22) {
        if (hi11 == hi21)
            return std::max(hi12, hi22);
        if (hi12 >= hi21)
            return hi12;
        if (hi22 >= hi11)
            return hi22;
        return std::min(hi11, hi21);
    }

    static constexpr DataType op(DataType x, DataType y) {
        DataType z{};
        z.lo = std::min(x.lo, y.lo);
        z.hi = std::max(x.hi, y.hi);
        z.lo2 = second_lo(x.lo, x.lo2, y.lo, y.lo2);
        z.hi2 = second_hi(x.hi, x.hi2, y.hi, y.hi2);
        z.sum = x.sum + y.sum;
        z.siz = x.siz + y.siz;
        z.num_lo = (z.lo == x.lo) * x.num_lo + (z.lo == y.lo) * y.num_lo;
        z.num_hi = (z.hi == x.hi) * x.num_hi + (z.hi == y.hi) * y.num_hi;
        return z;
    }
    static constexpr DataType e() { return DataType{}; }

    static constexpr DataType mapping(F f, DataType x) {
        if (x.siz == 0) {
            return e();
        } else if (x.lo == x.hi or f.lb == f.ub or f.lb >= x.hi or f.ub <= x.lo) {
            return DataType{std::clamp(x.lo, f.lb, f.ub) + f.add, x.siz};
        } else if (x.lo2 == x.hi) { // 2
            x.lo = x.hi2 = std::max(x.lo, f.lb) + f.add;
            x.hi = x.lo2 = std::min(x.hi, f.ub) + f.add;
            x.sum = x.lo * x.num_lo + x.hi * x.num_hi;
            return x;
        } else if (f.lb < x.lo2 and f.ub > x.hi2) { // >= 3
            T nlo = std::max(x.lo, f.lb);
            T nhi = std::min(x.hi, f.ub);
            x.sum += (nlo - x.lo) * x.num_lo + (nhi - x.hi) * x.num_hi + f.add * x.siz;
            x.lo = nlo + f.add;
            x.hi = nhi + f.add;
            x.lo2 += f.add;
            x.hi2 += f.add;
            return x;
        }
        x.fail = true;
        return x;
    }
    static constexpr F composition(F f, F g) {
        F h;
        h.lb = std::clamp(g.lb + g.add, f.lb, f.ub) - g.add;
        h.ub = std::clamp(g.ub + g.add, f.lb, f.ub) - g.add;
        h.add = f.add + g.add;
        return h;
    }
    static constexpr F id() { return F{}; }

    SegmentTreeBeats<DataType, op, e, F, mapping, composition, id> seg;
};
} // namespace suisen

#define TC
void solve() {
    int N, Q;
    cin >> N >> Q;
    string S, T;
    cin >> S >> T;
    vector<pair<int, int>> qs(Q);
    for (auto &[l, r] : qs) {
        cin >> l >> r;
        --l;
    }
    suisen::RangeChMinMaxAddRangeSum<int> seg(N);
    for (auto i = 0; i < N; ++i) {
        seg.update(i, i + 1, T[i] - '0');
    }
    for (auto [l, r] : qs | views::reverse) {
        array<int, 2> cnt;
        cnt[1] = seg.sum(l, r);
        cnt[0] = r - l - cnt[1];
        if (cnt[0] == cnt[1]) {
            println("NO");
            return;
        }
        if (cnt[0] < cnt[1]) {
            seg.chmax(l, r, 1);
        } else {
            seg.chmin(l, r, 0);
        }
    }
    for (auto i = 0; i < N; ++i) {
        if (S[i] - '0' != seg.sum(i, i + 1)) {
            println("NO");
            return;
        }
    }
    println("YES");
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
