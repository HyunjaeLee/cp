#include <atcoder/modint>
#include <bits/stdc++.h>
using namespace std;
using Z = atcoder::modint998244353;

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

struct bit_vector {
    explicit bit_vector(int n) : data_((n + 63) >> 6), sum_(data_.size() + 1) {}
    void set(int pos) { data_[pos >> 6] |= 1ULL << (pos & 63); }
    int rank(int l, int r, bool value) const {
        auto count = rank(r) - rank(l);
        return value ? count : r - l - count;
    }
    bool operator[](int pos) const {
        return static_cast<bool>(data_[pos >> 6] >> (pos & 63) & 1);
    }
    void build() {
        for (auto i = 0; i < static_cast<int>(data_.size()); ++i) {
            sum_[i + 1] = sum_[i] + __builtin_popcountll(data_[i]);
        }
    }

private:
    // Returns the number of bits that are set to true in [0, pos)
    int rank(int pos) const {
        return sum_[pos >> 6] +
               __builtin_popcountll(data_[pos >> 6] &
                                    ((1ULL << (pos & 63)) - 1ULL));
    }
    std::vector<unsigned long long> data_;
    std::vector<int> sum_;
};

template <typename T> struct wavelet_matrix {
    // data must not be empty
    wavelet_matrix(std::vector<T> data)
        : n_(static_cast<int>(data.size())),
          log_(std::numeric_limits<T>::digits), data_(log_, bit_vector(n_)),
          mid_(log_) {
        assert(std::all_of(data.begin(), data.end(),
                           [](auto x) { return x >= 0; }));
        for (auto i = log_ - 1; i >= 0; --i) {
            for (auto j = 0; j < n_; ++j) {
                if (data[j] >> i & 1) {
                    data_[i].set(j);
                }
            }
            data_[i].build();
            auto it =
                std::stable_partition(data.begin(), data.end(),
                                      [&](auto x) { return !(x >> i & 1); });
            mid_[i] = static_cast<int>(it - data.begin());
        }
    }
    T access(int pos) const {
        assert(0 <= pos && pos < n_);
        T result = 0;
        for (auto i = log_ - 1; i >= 0; --i) {
            if (data_[i][pos]) {
                result |= static_cast<T>(1) << i;
                pos = mid_[i] + data_[i].rank(0, pos, true);
            } else {
                pos = data_[i].rank(0, pos, false);
            }
        }
        return result;
    }
    int rank(int l, int r, T x) const {
        assert(0 <= l && l <= r && r <= n_);
        for (auto i = log_ - 1; i >= 0; --i) {
            if (x >> i & 1) {
                l = mid_[i] + data_[i].rank(0, l, true);
                r = mid_[i] + data_[i].rank(0, r, true);
            } else {
                l = data_[i].rank(0, l, false);
                r = data_[i].rank(0, r, false);
            }
        }
        return r - l;
    }
    T quantile(int l, int r, int k) const {
        assert(0 <= l && l <= r && r <= n_ && 0 <= k && k < r - l);
        T result = 0;
        for (auto i = log_ - 1; i >= 0; --i) {
            if (auto count = data_[i].rank(l, r, false); count <= k) {
                result |= static_cast<T>(1) << i;
                k -= count;
                l = mid_[i] + data_[i].rank(0, l, true);
                r = mid_[i] + data_[i].rank(0, r, true);
            } else {
                l = data_[i].rank(0, l, false);
                r = data_[i].rank(0, r, false);
            }
        }
        return result;
    }
    int range(int l, int r, T x, T y) const {
        return range(l, r, y) - range(l, r, x);
    }

private:
    int range(int l, int r, T x) const {
        auto count = 0;
        for (auto i = log_ - 1; i >= 0; --i) {
            if (x >> i & 1) {
                count += data_[i].rank(l, r, false);
                l = mid_[i] + data_[i].rank(0, l, true);
                r = mid_[i] + data_[i].rank(0, r, true);
            } else {
                l = data_[i].rank(0, l, false);
                r = data_[i].rank(0, r, false);
            }
        }
        return count;
    }
    const int n_, log_;
    std::vector<bit_vector> data_;
    std::vector<int> mid_;
};

void solve() {
    int N;
    cin >> N;
    vector<int> A(N);
    read<1>(A);
    auto L = 0, R = N - 1;
    auto rev = 0;
    Z ans = 0;
    wavelet_matrix<int> wm(A);
    while (L < R) {
        if (rev) {
            if (A[L] < A[R]) {
                ans++;
                rev ^= 1;
            }
        } else {
            if (A[L] > A[R]) {
                ans++;
                rev ^= 1;
            }
        }
        if (rev) {
            auto larger = wm.range(L + 1, R + 1, A[L] + 1, N);
            if (larger) {
                ans += Z(2).pow(larger - 1);
            }
            L++;
        } else {
            auto larger = wm.range(L, R, A[R] + 1, N);
            if (larger) {
                ans += Z(2).pow(larger - 1);
            }
            R--;
        }
    }
    cout << ans.val() << "\n";
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
