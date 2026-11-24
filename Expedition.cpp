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
    vector<pair<int, int>> A(N + 1);
    for (auto i = 1; i <= N; ++i) {
        cin >> A[i].first >> A[i].second;
    }
    sort(A.begin(), A.end());
    int L, P;
    cin >> L >> P;
    priority_queue<int> pq;
    auto ans = 0;
    for (auto i = N; 0 <= i; --i) {
        P -= L - A[i].first;
        L = A[i].first;
        while (!pq.empty() && P < 0) {
            P += pq.top();
            pq.pop();
            ans += 1;
        }
        if (P < 0) {
            cout << "-1\n";
            return;
        }
        pq.push(A[i].second);
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
