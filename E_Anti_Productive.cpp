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
    int N, L;
    cin >> N >> L;
    vector<i64> A(N);
    read(A);
    ranges::sort(A, greater());
    auto S = int(sqrt((long double)L));
    while (L <= S * S)
        --S;
    i64 ans = numeric_limits<i64>::max();
    {
        i64 sum = 0;
        for (auto i = 0; i < N; ++i) {
            sum += max(0LL, A[i] - S);
        }
        ans = min(ans, sum);
    }
    {
        i64 sum = ranges::fold_left(A | views::drop(1), 0LL, plus());
        ans = min(ans, sum);
    }
    {
        auto X = A[0];
        auto T = ranges::fold_left(A | views::drop(1), 0LL, plus());
        priority_queue<i64, vector<i64>, greater<>> pq(begin(A) + 1, end(A));
        for (auto Y = 1; Y <= S; ++Y) {
            while (!pq.empty() && pq.top() <= Y) {
                T -= pq.top();
                pq.pop();
            }
            i64 sum = max(0LL, X - (L - 1) / Y);
            sum += T - Y * ssize(pq);
            ans = min(ans, sum);
        }
    }
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
