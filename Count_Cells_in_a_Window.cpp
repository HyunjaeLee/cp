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

// https://hitonanode.github.io/cplib-cpp/data_structure/rectangle_add_rectangle_sum.hpp
#line 2 "segmenttree/binary_indexed_tree.hpp"
#include <algorithm>
#include <vector>

// CUT begin
// 0-indexed BIT (binary indexed tree / Fenwick tree) (i : [0, len))
template <class T> struct BIT {
    int n;
    std::vector<T> data;
    BIT(int len = 0) : n(len), data(len) {}
    void reset() { std::fill(data.begin(), data.end(), T(0)); }
    void add(int pos, T v) { // a[pos] += v
        pos++;
        while (pos > 0 and pos <= n)
            data[pos - 1] += v, pos += pos & -pos;
    }
    T sum(int k) const { // a[0] + ... + a[k - 1]
        T res = 0;
        while (k > 0)
            res += data[k - 1], k -= k & -k;
        return res;
    }

    T sum(int l, int r) const { return sum(r) - sum(l); } // a[l] + ... + a[r - 1]

    template <class OStream> friend OStream &operator<<(OStream &os, const BIT &bit) {
        T prv = 0;
        os << '[';
        for (int i = 1; i <= bit.n; i++) {
            T now = bit.sum(i);
            os << now - prv << ',', prv = now;
        }
        return os << ']';
    }
};
#line 4 "data_structure/rectangle_add_rectangle_sum.hpp"
#include <tuple>
#line 6 "data_structure/rectangle_add_rectangle_sum.hpp"

// Static rectangle add rectangle sum
// Calculate sums of rectangular weights inside the given rectangles
// Complexity: O(q log q), q = # of rectangles / queries
template <class Int, class T> class RectangleAddRectangleSum {
    struct AddQuery {
        Int xl, xr, yl, yr;
        T val;
    };
    struct SumQuery {
        Int xl, xr, yl, yr;
    };
    std::vector<AddQuery> add_queries;
    std::vector<SumQuery> sum_queries;

public:
    RectangleAddRectangleSum() = default;

    // A[x][y] += val for (x, y) in [xl, xr) * [yl, yr)
    void add_rectangle(Int xl, Int xr, Int yl, Int yr, T val) { add_queries.push_back(AddQuery{xl, xr, yl, yr, val}); }

    // Get sum of A[x][y] for (x, y) in [xl, xr) * [yl, yr)
    void add_query(Int xl, Int xr, Int yl, Int yr) { sum_queries.push_back(SumQuery{xl, xr, yl, yr}); }

    std::vector<T> solve() const {
        std::vector<Int> ys;
        for (const auto &a : add_queries) {
            ys.push_back(a.yl);
            ys.push_back(a.yr);
        }
        std::sort(ys.begin(), ys.end());
        ys.erase(std::unique(ys.begin(), ys.end()), ys.end());

        const int Y = ys.size();

        std::vector<std::tuple<Int, int, int>> ops;
        for (int q = 0; q < int(sum_queries.size()); ++q) {
            ops.emplace_back(sum_queries[q].xl, 0, q);
            ops.emplace_back(sum_queries[q].xr, 1, q);
        }
        for (int q = 0; q < int(add_queries.size()); ++q) {
            ops.emplace_back(add_queries[q].xl, 2, q);
            ops.emplace_back(add_queries[q].xr, 3, q);
        }
        std::sort(ops.begin(), ops.end());

        BIT<T> b00(Y), b01(Y), b10(Y), b11(Y);
        std::vector<T> ret(sum_queries.size());
        for (auto o : ops) {
            int qtype = std::get<1>(o), q = std::get<2>(o);
            if (qtype >= 2) {
                const AddQuery &query = add_queries.at(q);
                int i = std::lower_bound(ys.begin(), ys.end(), query.yl) - ys.begin();
                int j = std::lower_bound(ys.begin(), ys.end(), query.yr) - ys.begin();
                T x = std::get<0>(o);
                T yi = query.yl, yj = query.yr;
                if (qtype & 1)
                    std::swap(i, j), std::swap(yi, yj);

                b00.add(i, x * yi * query.val);
                b01.add(i, -x * query.val);
                b10.add(i, -yi * query.val);
                b11.add(i, query.val);
                b00.add(j, -x * yj * query.val);
                b01.add(j, x * query.val);
                b10.add(j, yj * query.val);
                b11.add(j, -query.val);
            } else {
                const SumQuery &query = sum_queries.at(q);
                int i = std::lower_bound(ys.begin(), ys.end(), query.yl) - ys.begin();
                int j = std::lower_bound(ys.begin(), ys.end(), query.yr) - ys.begin();
                T x = std::get<0>(o);
                T yi = query.yl, yj = query.yr;
                if (qtype & 1)
                    std::swap(i, j), std::swap(yi, yj);

                ret[q] += b00.sum(i) + b01.sum(i) * yi + b10.sum(i) * x + b11.sum(i) * x * yi;
                ret[q] -= b00.sum(j) + b01.sum(j) * yj + b10.sum(j) * x + b11.sum(j) * x * yj;
            }
        }
        return ret;
    }
};

void solve() {
    int N, M, Q;
    cin >> N >> M >> Q;
    RectangleAddRectangleSum<int, i64> S;
    for (auto i = 0; i < N; ++i) {
        int L, R;
        cin >> L >> R;
        --L;
        S.add_rectangle(i, i + 1, L, R, 1);
    }
    while (Q--) {
        int r1, r2, c1, c2;
        cin >> r1 >> r2 >> c1 >> c2;
        --r1, --c1;
        S.add_query(r1, r2, c1, c2);
    }
    auto ans = S.solve();
    show(ans, "\n", "");
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
