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
    vector<i64> A(N), D(N);
    read(A);
    read(D);
    set<int> alive, dead, color;
    auto Calc = [&](int i) {
        auto it = alive.find(i);
        assert(it != alive.end());
        i64 sum = 0;
        if (it != alive.begin()) {
            auto prv = *prev(it);
            sum += A[prv];
        }
        if (next(it) != alive.end()) {
            auto nxt = *next(it);
            sum += A[nxt];
        }
        if (D[i] < sum) {
            dead.insert(i);
        }
    };
    auto Touch = [&](int i) {
        if (dead.contains(i))
            return;
        assert(alive.contains(i));
        color.insert(i);
    };
    for (auto i = 0; i < N; ++i) {
        alive.insert(i);
    }
    for (auto i = 0; i < N; ++i) {
        Calc(i);
    }
    vector<int> ans;
    for (auto t = 0; t < N; ++t) {
        ans.push_back(int(dead.size()));
        for (auto i : dead) {
            auto it = alive.find(i);
            if (it != alive.begin()) {
                auto prv = *prev(it);
                Touch(prv);
            }
            if (next(it) != alive.end()) {
                auto nxt = *next(it);
                Touch(nxt);
            }
            alive.erase(i);
        }
        dead.clear();
        for (auto i : color) {
            Calc(i);
        }
        color.clear();
    }
    show(ans);
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
