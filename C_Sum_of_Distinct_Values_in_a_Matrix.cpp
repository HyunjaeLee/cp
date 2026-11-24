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

#define TC
void solve() {
    int N, M, X, Y;
    cin >> N >> M >> X >> Y;
    vector<i64> A(X), B(Y);
    read(A);
    read(B);
    ranges::reverse(A);
    ranges::reverse(B);
    auto F = [&](int p, int q) {
        vector<int> freq(N + M + 2);
        for (auto i = 0; i < min(p, X); ++i) {
            freq[A[i]]++;
        }
        for (auto i = 0; i < min(q, Y); ++i) {
            freq[B[i]]++;
        }
        vector<i64> pool;
        for (auto i = p; i < X; ++i) {
            pool.push_back(A[i]);
        }
        for (auto i = q; i < Y; ++i) {
            pool.push_back(B[i]);
        }
        ranges::sort(pool);
        i64 sum = 0;
        for (auto x = N + M + 1; 1 <= x; --x) {
            if (freq[x] == 2) {
                if (!pool.empty()) {
                    auto y = pool.back();
                    pool.pop_back();
                    freq[y] += 1;
                }
                freq[x] -= 1;
            }
            assert(freq[x] <= 1);
            sum += freq[x] * x;
        }
        return sum;
    };
    auto ans = max(F(N - 1, M), F(N, M - 1));
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
