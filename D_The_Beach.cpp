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

void solve() {
    int N, M;
    cin >> N >> M;
    i64 P, Q;
    cin >> P >> Q;
    vector<string> A(N);
    read(A);
    vector<vector<vector<tuple<int, int, i64>>>> adj(N, vector<vector<tuple<int, int, i64>>>(M));
    auto ok = [&](int r, int c) { return 0 <= r && r < N && 0 <= c && c < M; };
    for (auto i = 0; i < N; ++i) {
        for (auto j = 0; j < M; ++j) {
            if (A[i][j] == 'L') {
                if (ok(i - 1, j + 1))
                    adj[i - 1][j + 1].emplace_back(i, j, P);
                if (ok(i + 1, j + 1))
                    adj[i + 1][j + 1].emplace_back(i, j, P);
                if (ok(i, j + 2))
                    adj[i][j + 2].emplace_back(i, j, Q);
            } else if (A[i][j] == 'R') {
                if (ok(i - 1, j - 1))
                    adj[i - 1][j - 1].emplace_back(i, j, P);
                if (ok(i + 1, j - 1))
                    adj[i + 1][j - 1].emplace_back(i, j, P);
                if (ok(i, j - 2))
                    adj[i][j - 2].emplace_back(i, j, Q);
            } else if (A[i][j] == 'D') {
                if (ok(i - 1, j - 1))
                    adj[i - 1][j - 1].emplace_back(i, j, P);
                if (ok(i - 1, j + 1))
                    adj[i - 1][j + 1].emplace_back(i, j, P);
                if (ok(i - 2, j))
                    adj[i - 2][j].emplace_back(i, j, Q);
            } else if (A[i][j] == 'U') {
                if (ok(i + 1, j - 1))
                    adj[i + 1][j - 1].emplace_back(i, j, P);
                if (ok(i + 1, j + 1))
                    adj[i + 1][j + 1].emplace_back(i, j, P);
                if (ok(i + 2, j))
                    adj[i + 2][j].emplace_back(i, j, Q);
            }
        }
    }
    constexpr auto inf = numeric_limits<i64>::max() / 4;
    priority_queue<tuple<i64, int, int>, vector<tuple<i64, int, int>>, greater<>> pq;
    vector<vector<i64>> dist(N, vector<i64>(M, inf));
    for (auto i = 0; i < N; ++i) {
        for (auto j = 0; j < M; ++j) {
            if (A[i][j] == '.') {
                dist[i][j] = 0;
                pq.emplace(dist[i][j], i, j);
            }
        }
    }
    while (!pq.empty()) {
        auto [d, r, c] = pq.top();
        pq.pop();
        if (d != dist[r][c])
            continue;
        for (auto [x, y, w] : adj[r][c]) {
            if (dist[r][c] + w < dist[x][y]) {
                dist[x][y] = dist[r][c] + w;
                pq.emplace(dist[x][y], x, y);
            }
        }
    }
    auto ans = inf;
    for (auto i = 0; i < N; ++i) {
        for (auto j = 0; j < M - 1; ++j) {
            ans = min(ans, dist[i][j] + dist[i][j + 1]);
        }
    }
    for (auto i = 0; i < N - 1; ++i) {
        for (auto j = 0; j < M; ++j) {
            ans = min(ans, dist[i][j] + dist[i + 1][j]);
        }
    }
    if (inf <= ans) {
        ans = -1;
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
