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
    int N;
    cin >> N;
    vector<int> A(N);
    read(A);
    if (N == 1) {
        cout << "YES\n";
        return;
    }
    vector<int> P, Q;
    for (auto i = 0; i < N; ++i) {
        if (i % 2 == 0) {
            P.push_back(A[i]);
        } else {
            Q.push_back(A[i]);
        }
    }
    ranges::sort(P);
    ranges::sort(Q);
    deque<int> D;
    if (P.back() < Q.back()) {
        D.push_back(Q.back());
        Q.pop_back();
    } else {
        D.push_back(P.back());
        P.pop_back();
        swap(P, Q);
    }
    while (!P.empty() || !Q.empty()) {
        if (!P.empty()) {
            auto ok = P.back() < D.front();
            if (!ok) {
                cout << "NO\n";
                return;
            }
            D.push_front(P.back());
            P.pop_back();
        }
        if (!P.empty()) {
            auto ok = P.back() < D.back();
            if (!ok) {
                cout << "NO\n";
                return;
            }
            D.push_back(P.back());
            P.pop_back();
        }
        swap(P, Q);
    }
    cout << "YES\n";
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
