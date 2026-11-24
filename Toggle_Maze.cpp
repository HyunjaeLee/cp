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
    vector<vector<string>> A(2, vector<string>(N));
    read(A[0]);
    A[1] = A[0];
    for (auto i = 0; i < N; ++i) {
        for (auto j = 0; j < M; ++j) {
            if (A[0][i][j] == 'o') {
                A[1][i][j] = 'x';
            } else if (A[0][i][j] == 'x') {
                A[1][i][j] = 'o';
            } else {
                A[1][i][j] = A[0][i][j];
            }
        }
    }
    queue<tuple<int, int, int>> q;
    vector<vector<vector<int>>> dist(2, vector<vector<int>>(N, vector<int>(M, -1)));
    for (auto i = 0; i < N; ++i) {
        for (auto j = 0; j < M; ++j) {
            if (A[0][i][j] == 'S') {
                q.emplace(0, i, j);
                dist[0][i][j] = 0;
            }
        }
    }
    while (!q.empty()) {
        auto [t, r, c] = q.front();
        q.pop();
        array<int, 4> dr{1, -1, 0, 0};
        array<int, 4> dc{0, 0, 1, -1};
        for (auto i = 0; i < 4; ++i) {
            auto nr = r + dr[i];
            auto nc = c + dc[i];
            auto nt = A[t][r][c] == '?' ? (t ^ 1) : t;
            auto ok = 0 <= nr && nr < N && 0 <= nc && nc < M && A[nt][nr][nc] != '#' && A[nt][nr][nc] != 'x';
            if (!ok)
                continue;
            if (dist[nt][nr][nc] == -1) {
                dist[nt][nr][nc] = dist[t][r][c] + 1;
                q.emplace(nt, nr, nc);
            }
        }
    }
    auto ans = -1;
    for (auto t = 0; t < 2; ++t) {
        for (auto i = 0; i < N; ++i) {
            for (auto j = 0; j < M; ++j) {
                if (A[t][i][j] == 'G' && dist[t][i][j] != -1 && (ans == -1 || dist[t][i][j] < ans)) {
                    ans = dist[t][i][j];
                }
            }
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
