
#include <algorithm>
#include <cassert>
#include <vector>

namespace atcoder {

struct dsu {
  public:
    dsu() : _n(0) {}
    explicit dsu(int n) : _n(n), parent_or_size(n, -1) {}

    int merge(int a, int b) {
        assert(0 <= a && a < _n);
        assert(0 <= b && b < _n);
        int x = leader(a), y = leader(b);
        if (x == y) return x;
        if (-parent_or_size[x] < -parent_or_size[y]) std::swap(x, y);
        parent_or_size[x] += parent_or_size[y];
        parent_or_size[y] = x;
        return x;
    }

    bool same(int a, int b) {
        assert(0 <= a && a < _n);
        assert(0 <= b && b < _n);
        return leader(a) == leader(b);
    }

    int leader(int a) {
        assert(0 <= a && a < _n);
        return _leader(a);
    }

    int size(int a) {
        assert(0 <= a && a < _n);
        return -parent_or_size[leader(a)];
    }

    std::vector<std::vector<int>> groups() {
        std::vector<int> leader_buf(_n), group_size(_n);
        for (int i = 0; i < _n; i++) {
            leader_buf[i] = leader(i);
            group_size[leader_buf[i]]++;
        }
        std::vector<std::vector<int>> result(_n);
        for (int i = 0; i < _n; i++) {
            result[i].reserve(group_size[i]);
        }
        for (int i = 0; i < _n; i++) {
            result[leader_buf[i]].push_back(i);
        }
        result.erase(
            std::remove_if(result.begin(), result.end(),
                           [&](const std::vector<int>& v) { return v.empty(); }),
            result.end());
        return result;
    }

  private:
    int _n;
    std::vector<int> parent_or_size;

    int _leader(int a) {
        if (parent_or_size[a] < 0) return a;
        return parent_or_size[a] = _leader(parent_or_size[a]);
    }
};

}  // namespace atcoder

#line 2 "halfshuffle.cpp"
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using i128 = __int128;

template <typename T> T ceil_div(T a, T b) { return a / b + static_cast<T>((a ^ b) > 0 && a % b != 0); }

void solve() {
    int N;
    cin >> N;
    vector<int> A(2 * N);
    for (auto i = 0; i < 2 * N; ++i) {
        cin >> A[i];
        --A[i];
    }
    atcoder::dsu dsu(2 * N);
    for (auto i = 0; i < 2 * N; ++i) {
        dsu.merge(i, A[i]);
    }
    vector<int> C;
    for (auto i = 0; i < 2 * N; ++i) {
        if (i == dsu.leader(i) && 1 < dsu.size(i)) {
            C.emplace_back(dsu.size(i));
        }
    }
    auto sum = accumulate(begin(C), end(C), 0);
    auto ans = 0;
    if (sum == 0) {
        ans = 0;
    } else if (sum <= N) {
        ans = 1;
    } else if (sum < 2 * N) {
        ans = 2;
    } else {
        auto K = int(C.size());
        vector<vector<int>> dp(K + 1, vector<int>(N + 1, -1));
        auto f = [&](this auto &&self, int i, int acc) -> bool {
            if (N < acc)
                return false;
            if (i == K)
                return acc == N;
            auto &ret = dp[i][acc];
            if (~ret)
                return ret;
            ret = self(i + 1, C[i] + acc) || self(i + 1, acc);
            return ret;
        };
        if (f(0, 0)) {
            ans = 2;
        } else {
            ans = 3;
        }
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