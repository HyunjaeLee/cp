#include <bits/stdc++.h>
using namespace std;

using i8 = signed char;
using u8 = unsigned char;
using i32 = int;
using u32 = unsigned;
using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128;
using u128 = unsigned __int128;

// clang-format off
template <typename T> T ceil_div(T a, T b) { return a / b + static_cast<T>((a ^ b) > 0 && a % b != 0); }
template <typename T> T floor_div(T a, T b) { return a / b - static_cast<T>((a ^ b) < 0 && a % b != 0); }
void read(auto &a) { for (auto &x : a) cin >> x; }
void show(const auto &a, string_view sep = " ", string_view end = "\n") {
    for (auto it = a.begin(); it != a.end(); ++it) {
        if (it != a.begin()) cout << sep;
        cout << *it;
    }
    cout << end;
}
// clang-format on

void solve() {
    int N;
    cin >> N;
    vector<int> A(N);
    read(A);
    auto total = ranges::fold_left(A, 0, plus());
    vector<vector<int>> dp(N, vector<int>(total + 1, -1));
    auto f = [&](this auto &&self, int i, int sum) -> int {
        if (sum < 0)
            return 0;
        if (i == N)
            return sum == 0;
        auto &ret = dp[i][sum];
        if (~ret)
            return ret;
        ret = self(i + 1, sum - A[i]) || self(i + 1, sum);
        return ret;
    };
    if (total % 2 == 0 && f(0, total / 2)) {
        cout << "Second" << endl;
        vector<int> color(N + 1);
        [&](this auto &&self, int i, int sum) -> void {
            if (i == N)
                return;
            if (f(i + 1, sum - A[i])) {
                color[i] = 1;
                self(i + 1, sum - A[i]);
            } else {
                color[i] = 0;
                self(i + 1, sum);
            }
        }(0, total / 2);
        while (true) {
            int i;
            cin >> i;
            --i;
            if (i < 0) {
                exit(0);
            }
            auto j = 0;
            for (; j < N; ++j) {
                if (i != j && 0 < A[j] && color[j] != color[i]) {
                    cout << j + 1 << endl;
                    break;
                }
            }
            auto x = min(A[i], A[j]);
            A[i] -= x;
            A[j] -= x;
        }
    } else {
        cout << "First" << endl;
        while (true) {
            auto i = 0;
            for (; i < N; ++i) {
                if (0 < A[i]) {
                    cout << i + 1 << endl;
                    break;
                }
            }
            int j;
            cin >> j;
            --j;
            if (j < 0) {
                exit(0);
            }
            auto x = min(A[i], A[j]);
            A[i] -= x;
            A[j] -= x;
        }
    }
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
