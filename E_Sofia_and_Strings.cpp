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
    int N, M;
    string S, T;
    cin >> N >> M >> S >> T;
    vector<deque<int>> I('z' + 1);
    for (auto i = 0; i < N; ++i) {
        I[S[i]].push_back(i);
    }
    for (auto x : T) {
        if (I[x].empty()) {
            cout << "NO\n";
            return;
        }
        auto i = I[x].front();
        I[x].pop_front();
        for (int y = 'a'; y < x; ++y) {
            while (!I[y].empty() && I[y].front() < i) {
                I[y].pop_front();
            }
        }
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
