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

#define TC
void solve() {
    vector<pair<i64, i64>> rng;
    int N, M;
    cin >> N >> M;
    vector<pair<i64, i64>> A(N), A_;
    for (auto &[l, r] : A) {
        cin >> l >> r;
    }
    vector<pair<i64, i64>> B(M), B_;
    for (auto &[l, r] : B) {
        cin >> l >> r;
    }
    for (auto i = 0; i < N; ++i) {
        auto [l, r] = A[i];
        auto ok = true;
        for (auto j = 0; j < M; ++j) {
            if (B[j].first <= l && r <= B[j].second) {
                ok = false;
            }
        }
        if (ok) {
            A_.emplace_back(l, r);
        }
    }
    swap(A, A_);
    for (auto i = 0; i < M; ++i) {
        auto [l, r] = B[i];
        auto ok = true;
        for (auto j = 0; j < int(A.size()); ++j) {
            if (A[j].first <= l && r <= A[j].second) {
                ok = false;
            }
        }
        if (ok) {
            B_.emplace_back(l, r);
        }
    }
    swap(B, B_);
    rng = A;
    rng.insert(rng.end(), B.begin(), B.end());
    ranges::sort(rng);
    auto K = int(rng.size());
    vector<i64> S;
    for (auto i = 0; i < K; ++i) {
        auto [l, r] = rng[i];
        i64 a = 0, b = 0;
        if (0 < i && l <= rng[i - 1].second) {
            a = rng[i - 1].second - l + 1;
        }
        if (i + 1 < K && rng[i + 1].first <= r) {
            b = r - rng[i + 1].first + 1;
        }
        auto len = r - l + 1;
        S.push_back(len);
        S.push_back(len - a);
        S.push_back(len - b);
        S.push_back(len - a - b);
    }
    ranges::sort(S);
    S.erase(unique(begin(S), end(S)), end(S));
    auto L = int(S.size());
    auto I = [&](i64 x) {
        auto it = ranges::lower_bound(S, x);
        assert(it != S.end() && *it == x);
        auto pos = int(it - S.begin());
        return L - 1 - pos;
    };
    vector<vector<vector<int>>> dp(K, vector<vector<int>>(2));
    auto V = [&](this auto &&self, int pos, int state) -> vector<int> {
        if (pos == K) {
            return vector<int>(L);
        }
        auto &ret = dp[pos][state];
        if (!ret.empty())
            return ret;
        auto [l, r] = rng[pos];
        i64 a = 0, b = 0;
        if (0 < pos && l <= rng[pos - 1].second) {
            a = rng[pos - 1].second - l + 1;
        }
        if (pos + 1 < K && rng[pos + 1].first <= r) {
            b = r - rng[pos + 1].first + 1;
        }
        auto len = r - l + 1 - (state ? a : 0);
        auto x = self(pos + 1, 1);
        x[I(len)] += 1;
        auto y = self(pos + 1, 0);
        y[I(len - b)] += 1;
        ret = max(x, y);
        return ret;
    }(0, 0);
    vector<i64> ans;
    for (auto i = 0; i < L; ++i) {
        auto x = S[L - 1 - i];
        for (auto j = 0; j < V[i]; ++j) {
            ans.push_back(x);
        }
    }
    cout << size(ans) << "\n";
    show(ans);
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
