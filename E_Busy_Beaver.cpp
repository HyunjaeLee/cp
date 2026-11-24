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
    i64 N, X;
    cin >> N >> X;
    vector<vector<i64>> A(N);
    vector<vector<i64>> B(N);
    for (auto i = 0; i < N; ++i) {
        int M;
        cin >> M;
        A[i].resize(M);
        B[i].resize(M);
        read(A[i]);
        read(B[i]);
    }
    vector<queue<array<i64, 3>>> G(N);
    for (auto i = 0; i < N; ++i) {
        auto M = int(A[i].size());
        array<i64, 3> blk{-1, -1, -1};
        i64 acc = 0;
        for (auto j = 0; j < M; ++j) {
            if (blk[2] == -1) {
                acc = A[i][j];
                blk = {A[i][j], B[i][j] - A[i][j], j};
            } else {
                acc += A[i][j] - B[i][j - 1];
                blk[0] = max(blk[0], acc);
                blk[1] += B[i][j] - A[i][j];
            }
            if (0 <= blk[1] || j == M - 1) {
                G[i].push(blk);
                blk = {-1, -1, -1};
            }
        }
    }
    vector<i64> I(N);
    using S = array<i64, 3>;
    priority_queue<S, vector<S>, greater<>> pq;
    for (auto i = 0; i < N; ++i) {
        auto [need, profit, pos] = G[i].front();
        G[i].pop();
        I[i] = pos;
        if (0 <= profit) {
            pq.push({need, profit, i});
        }
    }
    while (!pq.empty()) {
        auto [need, profit, i] = pq.top();
        pq.pop();
        if (X < need) {
            break;
        }
        X += profit;
        if (!G[i].empty()) {
            auto blk = G[i].front();
            G[i].pop();
            I[i] = blk[2];
            if (0 <= blk[1]) {
                pq.push({blk[0], blk[1], i});
            }
        } else {
            I[i] = ssize(A[i]);
        }
    }
    vector<pair<i64, i64>> R(N);
    for (auto i = 0; i < N; ++i) {
        auto M = int(A[i].size());
        i64 cap = X;
        auto cnt = 0;
        for (auto j = I[i]; j < M; ++j) {
            if (cap < A[i][j]) {
                break;
            }
            cnt += 1;
            cap = cap - A[i][j] + B[i][j];
        }
        R[i] = {I[i] + cnt, -i};
    }
    auto [h, i] = ranges::max(R);
    i = -i + 1;
    cout << h << " " << i << "\n";
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
