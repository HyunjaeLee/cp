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
    vector<pair<i64, i64>> A(N);
    i64 S = 0;
    for (auto &[h, w] : A) {
        cin >> h >> w;
        S += h * w;
    }
    auto F = [&](i64 H, i64 W) {
        map<i64, vector<int>> hmp, wmp;
        for (auto i = 0; i < N; ++i) {
            hmp[A[i].first].push_back(i);
            wmp[A[i].second].push_back(i);
        }
        vector<bool> used(N);
        while (0 < H && 0 < W) {
            auto a = H, b = W;
            for (auto i : hmp[H]) {
                if (!used[i]) {
                    auto [h, w] = A[i];
                    W -= w;
                    used[i] = true;
                }
            }
            hmp[H].clear();
            for (auto i : wmp[W]) {
                if (!used[i]) {
                    auto [h, w] = A[i];
                    H -= h;
                    used[i] = true;
                }
            }
            wmp[W].clear();
            if (a == H && b == W)
                break;
        }
        return H == 0 || W == 0;
    };
    auto H = ranges::max(A | views::transform([](auto p) { return p.first; }));
    auto W = ranges::max(A | views::transform([](auto p) { return p.second; }));
    vector<pair<i64, i64>> ans;
    if (S % H == 0 && F(H, S / H)) {
        ans.emplace_back(H, S / H);
    }
    if (S % W == 0 && F(S / W, W)) {
        ans.emplace_back(S / W, W);
    }
    ranges::sort(ans);
    ans.erase(unique(begin(ans), end(ans)), end(ans));
    cout << ssize(ans) << "\n";
    for (auto [h, w] : ans) {
        cout << h << " " << w << "\n";
    }
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
