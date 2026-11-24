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
    int N;
    string S;
    cin >> N >> S;
    vector<int> A(N);
    for (auto i = 0; i < N; ++i) {
        A[i] = S[i] - '0';
    }
    vector<int> can;
    auto F = [&](auto cnt) {
        if (abs(cnt[0] - cnt[1]) <= 1) {
            can.push_back(cnt[0] + cnt[1]);
        }
    };
    for (auto x : {0, 1}) {
        array<int, 2> cnt{};
        vector<int> v;
        for (auto i = 0; i < N; ++i) {
            if (A[i] == x) {
                x ^= 1;
                v.push_back(A[i]);
            } else {
                cnt[A[i]]++;
            }
        }
        F(cnt);
        if (v.empty())
            continue;
        {
            auto cnt_ = cnt;
            cnt_[v.front()] += 1;
            F(cnt_);
        }
        {
            auto cnt_ = cnt;
            cnt_[v.back()] += 1;
            F(cnt_);
        }
        {
            auto cnt_ = cnt;
            cnt_[v.front()] += 1;
            cnt_[v.back()] += 1;
            F(cnt_);
        }
    }
    auto ans = 0;
    if (can.empty()) {
        ans = -1;
    } else {
        ans = ranges::min(can);
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
