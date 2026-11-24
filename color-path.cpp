#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using i128 = __int128;

#ifndef CSR_HPP
#define CSR_HPP

#include <cassert>
#include <ranges>
#include <utility>
#include <vector>

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

#endif // CSR_HPP

void solve() {
    int N, M, K;
    cin >> N >> M >> K;
    csr<pair<int, int>> g(N);
    for (auto i = 0; i < M; ++i) {
        int u, v, c;
        cin >> u >> v >> c;
        --u, --v, --c;
        g.add(u, {v, c});
        g.add(v, {u, c});
    }
    g.build();
    constexpr auto inf = numeric_limits<int>::max() / 2;
    auto ans = inf;
    for (auto x = 0; x < K; ++x) {
        deque<int> dq;
        dq.push_back(0);
        vector<int> dist(N, inf);
        dist[0] = 0;
        while (!dq.empty()) {
            auto u = dq.front();
            dq.pop_front();
            for (auto [v, c] : g[u]) {
                auto w = x == c ? 0 : 1;
                if (dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                    if (w == 0)
                        dq.push_front(v);
                    else
                        dq.push_back(v);
                }
            }
        }
        ans = min(ans, dist[N - 1]);
    }
    cout << ans << "\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}
