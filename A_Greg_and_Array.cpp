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
    int N, M, K;
    cin >> N >> M >> K;
    vector<i64> A(N);
    read(A);
    A.push_back(0);
    vector<tuple<int, int, i64>> rng(M);
    for (auto &[l, r, x] : rng) {
        cin >> l >> r >> x;
        --l;
    }
    vector<int> P(M + 1);
    for (auto i = 0; i < K; ++i) {
        int l, r;
        cin >> l >> r;
        --l;
        P[l]++;
        P[r]--;
    }
    for (auto i = 0; i < M; ++i) {
        P[i + 1] += P[i];
    }
    for (auto i = N; 0 < i; --i) {
        A[i] -= A[i - 1];
    }
    for (auto i = 0; auto [l, r, x] : rng) {
        auto w = P[i] * x;
        A[l] += w;
        A[r] -= w;
        ++i;
    }
    for (auto i = 0; i < N; ++i) {
        A[i + 1] += A[i];
    }
    A.pop_back();
    show(A);
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
