#include <bits/stdc++.h>

template <typename T> struct csr {
    explicit csr(int n) : n_(n) {}
    void add(int i, T x) {
        assert(!built_);
        assert(0 <= i && i < n_);
        buf_.emplace_back(i, x);
    }
    void build() {
        assert(!built_);
        ptr_.assign(n_ + 2, 0);
        csr_.resize(buf_.size());
        for (auto [i, x] : buf_) {
            ++ptr_[i + 2];
        }
        for (int i = 0; i < n_; ++i) {
            ptr_[i + 1] += ptr_[i];
        }
        for (auto [i, x] : buf_) {
            csr_[ptr_[i + 1]++] = x;
        }
        built_ = true;
    }
    auto operator[](int i) {
        assert(built_);
        assert(0 <= i && i < n_);
        return std::ranges::subrange(csr_.begin() + ptr_[i], csr_.begin() + ptr_[i + 1]);
    }
    auto operator[](int i) const {
        assert(built_);
        assert(0 <= i && i < n_);
        return std::ranges::subrange(csr_.begin() + ptr_[i], csr_.begin() + ptr_[i + 1]);
    }
    int size() const { return n_; }

private:
    int n_;
    bool built_ = false;
    std::vector<std::pair<int, T>> buf_;
    std::vector<T> csr_;
    std::vector<int> ptr_;
};

template <typename T> struct static_range_frequency {
    explicit static_range_frequency(const std::vector<T> &a) : n(int(a.size())), v(compress(a)), f(int(v.size())) {
        for (auto i = 0; i < n; ++i) {
            auto c = int(std::ranges::lower_bound(v, a[i]) - v.begin());
            f.add(c, i);
        }
        f.build();
    }
    int query(int l, int r, T x) const { // [l, r)
        assert(0 <= l && l <= r && r <= n);
        if (l == r) {
            return 0;
        }
        auto it = std::ranges::lower_bound(v, x);
        if (it == v.end() || *it != x) {
            return 0;
        }
        auto c = int(it - v.begin());
        return int(std::ranges::lower_bound(f[c], r) - std::ranges::lower_bound(f[c], l));
    }

private:
    static std::vector<T> compress(std::vector<T> a) {
        std::ranges::sort(a);
        auto [l, r] = std::ranges::unique(a);
        a.erase(l, r);
        return a;
    }
    int n;
    std::vector<T> v;
    csr<int> f;
};

int main() {
    std::cin.tie(0)->sync_with_stdio(0);
    int N, Q;
    std::cin >> N >> Q;
    std::vector<int> A(N);
    for (auto &x : A) {
        std::cin >> x;
    }
    static_range_frequency<int> f(A);
    while (Q--) {
        int l, r, x;
        std::cin >> l >> r >> x;
        std::cout << f.query(l, r, x) << "\n";
    }
}
