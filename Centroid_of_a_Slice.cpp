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

struct HilbertMo {
    HilbertMo(int n) : n_(n), log_(std::bit_width(unsigned(n))) {}
    void add(int l, int r) {
        assert(0 <= l && l <= r && r <= n_);
        auto index = int(queries_.size());
        auto order = hilbert_order(l, r);
        queries_.push_back({l, r, index, order});
    }
    void solve(auto add, auto remove, auto eval) { solve(add, add, remove, remove, eval); }
    void solve(auto add_left, auto add_right, auto remove_left, auto remove_right, auto eval) {
        sort(queries_.begin(), queries_.end());
        auto l = 0, r = 0;
        for (auto [left, right, index, order] : queries_) {
            while (left < l) {
                add_left(--l);
            }
            while (r < right) {
                add_right(r++);
            }
            while (l < left) {
                remove_left(l++);
            }
            while (right < r) {
                remove_right(--r);
            }
            eval(index);
        }
    }

private:
    struct query {
        int left, right, index;
        long long order;
        bool operator<(const query &other) const { return order < other.order; }
    };
    long long hilbert_order(int x, int y) const {
        auto d = 0LL;
        for (auto s = 1 << log_; s > 0; s >>= 1) {
            bool rx = x & s, ry = y & s;
            d = (d << 2) | ((rx * 3) ^ ry);
            if (!ry) {
                if (rx) {
                    x = ~x;
                    y = ~y;
                }
                std::swap(x, y);
            }
        }
        return d;
    }
    std::vector<query> queries_;
    const int n_, log_;
};

void solve() {
    int N, Q;
    cin >> N >> Q;
    vector<i64> X(2 * N), Y(2 * N);
    for (auto i = 0; i < N; ++i) {
        cin >> X[i] >> Y[i];
        X[N + i] = X[i];
        Y[N + i] = Y[i];
    }
    HilbertMo mo(2 * N);
    for (auto i = 0; i < Q; ++i) {
        int l, r;
        cin >> l >> r;
        --l, --r;
        if (l > r)
            r += N;
        mo.add(l, r + 1);
    }
    i64 sum1 = 0, sum2 = 0, sum3 = 0;
    deque<int> dq;
    auto update = [&](int p, int q, int sgn) {
        sum1 += sgn * (X[p] * Y[q] - X[q] * Y[p]);
        sum2 += sgn * (X[p] + X[q]) * (X[p] * Y[q] - X[q] * Y[p]);
        sum3 += sgn * (Y[p] + Y[q]) * (X[p] * Y[q] - X[q] * Y[p]);
    };
    auto add_left = [&](int i) {
        if (2 <= dq.size()) {
            auto p = dq.back();
            auto q = dq.front();
            update(p, q, -1);
        }
        dq.push_front(i);
        if (2 <= dq.size()) {
            auto p = dq[0];
            auto q = dq[1];
            update(p, q, 1);
        }
        if (2 <= dq.size()) {
            auto p = dq.back();
            auto q = dq.front();
            update(p, q, 1);
        }
    };
    auto remove_left = [&](int) {
        if (2 <= dq.size()) {
            auto p = dq.back();
            auto q = dq.front();
            update(p, q, -1);
        }
        if (2 <= dq.size()) {
            auto p = dq[0];
            auto q = dq[1];
            update(p, q, -1);
        }
        dq.pop_front();
        if (2 <= dq.size()) {
            auto p = dq.back();
            auto q = dq.front();
            update(p, q, 1);
        }
    };
    auto add_right = [&](int i) {
        if (2 <= dq.size()) {
            auto p = dq.back();
            auto q = dq.front();
            update(p, q, -1);
        }
        dq.push_back(i);
        if (2 <= dq.size()) {
            auto p = dq[int(dq.size()) - 2];
            auto q = dq[int(dq.size()) - 1];
            update(p, q, 1);
        }
        if (2 <= dq.size()) {
            auto p = dq.back();
            auto q = dq.front();
            update(p, q, 1);
        }
    };
    auto remove_right = [&](int) {
        if (2 <= dq.size()) {
            auto p = dq.back();
            auto q = dq.front();
            update(p, q, -1);
        }
        if (2 <= dq.size()) {
            auto p = dq[int(dq.size()) - 2];
            auto q = dq[int(dq.size()) - 1];
            update(p, q, -1);
        }
        dq.pop_back();
        if (2 <= dq.size()) {
            auto p = dq.back();
            auto q = dq.front();
            update(p, q, 1);
        }
    };
    vector<pair<double, double>> ans(Q);
    auto eval = [&](int i) {
        auto &[x, y] = ans[i];
        x = double(sum2) / double(sum1) / 3.0;
        y = double(sum3) / double(sum1) / 3.0;
    };
    mo.solve(add_left, add_right, remove_left, remove_right, eval);
    for (auto [x, y] : ans) {
        cout << x << " " << y << "\n";
    }
}

int main() {
    cout << fixed << setprecision(12);
    cin.tie(0)->sync_with_stdio(0);
    int t = 1;
#ifdef TC
    cin >> t;
#endif
    for (auto i = 0; i < t; ++i) {
        solve();
    }
}
