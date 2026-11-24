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

int dp[50][1 << 18];

void solve() {
    memset(dp, -1, sizeof dp);
    int N, M;
    cin >> N >> M;
    vector<int> A(M);
    for (auto i = 0; i < M; ++i) {
        int k;
        cin >> k;
        for (auto j = 0; j < k; ++j) {
            int p;
            cin >> p;
            A[i] |= 1 << p;
        }
    }
    for (auto i = 0; i < M; ++i) {
        for (auto j = i + 1; j < M; ++j) {
            if (A[i] == A[j]) {
                cout << "not possible\n";
                return;
            }
        }
    }
    constexpr auto inf = numeric_limits<int>::max() / 2;
    auto f = [&](this auto &&self, int leader, int mask) -> int {
        auto &ret = dp[leader][mask];
        if (~ret) {
            return ret;
        }
        vector<int> S;
        for (auto i = 0; i < M; ++i) {
            if ((A[leader] & mask) == (A[i] & mask)) {
                S.push_back(i);
            }
        }
        if (S.size() == 1) {
            return ret = 0;
        }
        assert(mask != ((1 << N) - 1));
        ret = inf;
        for (auto i = 0; i < N; ++i) {
            if ((mask >> i) & 1) {
                continue;
            }
            auto sum = int(S.size());
            for (auto b = 0; b < 2; ++b) {
                auto l = -1;
                for (auto j : S) {
                    if (((A[j] >> i) & 1) == b) {
                        l = j;
                        break;
                    }
                }
                if (l == -1) {
                    continue;
                }
                sum += self(l, mask | (1 << i));
            }
            ret = min(ret, sum);
        }
        return ret;
    };
    cout << fixed << setprecision(8);
    auto ans = (double)f(0, 0) / M;
    cout << ans << "\n";
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
