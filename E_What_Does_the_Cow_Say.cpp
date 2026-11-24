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
    int N, K;
    cin >> N >> K;
    string S;
    cin >> S;
    vector<pair<char, int>> rle;
    for (auto i = 0; i < N; ++i) {
        if (!empty(rle) && rle.back().first == S[i]) {
            rle.back().second++;
        } else {
            rle.emplace_back(S[i], 1);
        }
    }
    rle.emplace_back('(', 0);
    auto head = rle[0].second;
    auto ans = head + K;
    vector<int> A(N), B(N);
    for (auto i = 0; i < N; ++i) {
        A[i] = (S[i] == '(' ? 1 : -1);
        B[i] = (S[i] == ')');
    }
    for (auto i = 0; i < N - 1; ++i) {
        A[i + 1] += A[i];
        B[i + 1] += B[i];
    }
    priority_queue<pair<int, int>> pq;
    for (auto i = N - 1; 0 <= i; --i) {
        while (!pq.empty() && K < pq.top().second - B[i]) {
            pq.pop();
        }
        if (!pq.empty()) {
            ans = max(ans, pq.top().first - A[i]);
        }
        pq.emplace(A[i], B[i]);
    }
    for (auto i = 1; i < ssize(rle); i += 2) {
        assert(rle[i].first == ')');
        if (K < rle[i].second) {
            break;
        }
        // consume
        K -= rle[i].second;
        head += rle[i + 1].second;
        ans = max(ans, head + K);
    }
    ans = min(ans, N / 2);
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
