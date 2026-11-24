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

i64 F(string s) {
    i64 acc = 0;
    i64 ans = 0;
    for (auto c : s) {
        if (c == 'X') {
            acc++;
        } else {
            ans += acc * (c - '0');
        }
    }
    return ans;
}

void solve() {
    int N;
    cin >> N;
    vector<string> S(N);
    read(S);
    vector<pair<i64, i64>> A(N);
    for (auto i = 0; i < N; ++i) {
        auto &[x, y] = A[i];
        for (auto c : S[i]) {
            if (c == 'X')
                x++;
            else
                y += c - '0';
        }
    }
    i64 sum = 0;
    for (auto i = 0; i < N; ++i) {
        sum += F(S[i]);
    }
    auto comp = [&](pair<i64, i64> a, pair<i64, i64> b) {
        if (a.first * b.second != a.second * b.first) {
            return a.first * b.second > a.second * b.first;
        }
        return a > b;
    };
    ranges::sort(A, comp);
    [&](this auto &&self, int l, int r) -> void {
        if (r - l <= 1) return;
        auto mid = (l + r) / 2;
        i64 X = 0;
        for (auto i = l; i < mid; ++i) {
            X += A[i].first;
        }
        i64 Y = 0;
        for (auto i = mid; i < r; ++i) {
            Y += A[i].second;
        }
        sum += X * Y;
        self(l, mid);
        self(mid, r);
    }(0, N);
    cout << sum << "\n";
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
