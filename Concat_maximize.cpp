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

void solve() {
    int N, K;
    cin >> N >> K;
    vector<string> A(N);
    read(A);
    auto proj = [](const string &s) { return pair{s.size(), s}; };
    ranges::sort(A, greater(), proj);
    auto F = [&](const string &s) {
        i64 f = 0;
        for (auto x : s) {
            f = f * 10 + (x - '0');
        }
        return f;
    };
    string ans = "";
    auto comp = [&](string a, string b) {
        auto s = a + b;
        auto t = b + a;
        return s > t;
    };
    {
        vector<string> X(A.begin(), A.begin() + K);
        ranges::sort(X, comp);
        string S;
        auto start = false;
        for (const auto &s : X) {
            for (auto c : s) {
                if (c != '0')
                    start = true;
                if (!start && c == '0')
                    continue;
                S.push_back(c);
            }
        }
        ans = ranges::max(ans, S, {}, proj);
    }
    if (K < N) {
        vector<string> X{ranges::max(A | views::drop(K), {}, [&](const auto &s) { return F(s); })};
        X.insert(X.end(), A.begin(), A.begin() + K - 1);
        ranges::sort(X.begin(), X.end(), comp);
        string S;
        auto start = false;
        for (const auto &s : X) {
            for (auto c : s) {
                if (c != '0')
                    start = true;
                if (!start && c == '0')
                    continue;
                S.push_back(c);
            }
        }
        ans = ranges::max(ans, S, {}, proj);
    }
    if (ans == "")
        ans = "0";
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
