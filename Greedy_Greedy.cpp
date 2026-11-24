#include <bits/stdc++.h>

// O(n^3), requires distinct positive integers including 1
// return (is canonical, smallest counterexample w, M(w))
// David Pearson, "A Polynomial-time Algorithm for the Change-Making Problem"
template <typename T> std::tuple<bool, T, std::vector<T>> greedy_optimality(std::vector<T> coins) {
    auto n = int(coins.size());
    std::sort(coins.rbegin(), coins.rend());
    auto greedy = [&](T x) {
        std::vector<T> v(n);
        for (auto i = 0; i < n; ++i) {
            v[i] = x / coins[i];
            x %= coins[i];
        }
        return v;
    };
    auto count = [](const std::vector<T> &v) { return std::accumulate(v.begin(), v.end(), T(0)); };
    auto comp = [&](const auto &a, const auto &b) {
        const auto &[ca, wa, ma] = a;
        const auto &[cb, wb, mb] = b;
        if (ca != cb)
            return ca < cb;
        if (wa != wb)
            return wa < wb;
        auto sa = count(ma);
        auto sb = count(mb);
        if (sa != sb)
            return sa < sb;
        return ma > mb;
    };
    std::tuple<bool, T, std::vector<T>> ans{true, -1, {}};
    for (auto i = 1; i < n; ++i) {
        auto v = greedy(coins[i - 1] - 1);
        for (auto j = i; j < n; ++j) {
            std::vector<T> mw(n);
            std::copy(v.begin(), v.begin() + j, mw.begin());
            mw[j] = v[j] + 1;
            auto w = std::inner_product(coins.begin(), coins.end(), mw.begin(), T(0));
            auto gw = greedy(w);
            if (count(mw) < count(gw)) {
                ans = std::ranges::min(ans, {false, w, mw}, comp);
            }
        }
    }
    return ans;
}

int main() {
    std::cin.tie(0)->sync_with_stdio(0);
    for (int t = 1, N; (std::cin >> N) && N; ++t) {
        std::cout << "Case #" << t << ": ";
        std::vector<int> A(N);
        for (auto &x : A) {
            std::cin >> x;
        }
        if (A[0] != 1) {
            std::cout << "Cannot pay some amount\n";
            continue;
        }
        auto [canonical, w, mw] = greedy_optimality(A);
        if (canonical) {
            std::cout << "OK\n";
        } else {
            std::cout << "Cannot use greedy algorithm\n";
        }
    }
}
