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
template <typename T> void read(vector<T> &a) { for (auto &x : a) cin >> x; }
template <typename T> void show(const vector<T> &a, string_view sep = " ", string_view end = "\n") {
    for (auto i = 0; i < int(a.size()); ++i) {
        if (i) cout << sep;
        cout << a[i];
    }
    cout << end;
}
// clang-format on

#define TC
void solve() {
    int N;
    cin >> N;
    vector<int> A(N);
    read(A);
    vector<array<int, 2>> P(N);
    vector<vector<int>> F(N + 1), G(N + 1);
    for (auto i = 0; i < N; ++i) {
        P[i][0] = N - A[i];
        P[i][1] = A[i];
        F[N - A[i]].push_back(i);
        G[A[i]].push_back(i);
    }
    vector<int> B(N);
    array<int, 2> cnt{};
    while (cnt[0] + cnt[1] < N) {
        auto upd = 0;
        for (auto s = 1; 0 <= s; --s) {
            auto x = N - cnt[0] - cnt[1];
            auto acc = 0;
            for (auto i : (s ? G : F)[cnt[s ^ 1]]) {
                if (B[i] == 0) {
                    B[i] = x * (s ? -1 : 1);
                    acc += 1;
                }
            }
            upd += acc;
            cnt[s] += acc;
            vector<int> tmp;
            swap((s ? G : F)[cnt[s ^ 1]], tmp);
        }
        if (!upd) {
            cout << "NO\n";
            return;
        }
    }
    cout << "YES\n";
    show(B);
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
