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
    int N, M;
    cin >> N >> M;
    vector<string> S(N);
    read(S);
    auto total = 0;
    for (auto i = 0; i < N; ++i) {
        total += int(S[i].size());
    }
    set<string> T;
    for (auto i = 0; i < M; ++i) {
        string t;
        cin >> t;
        T.insert(t);
    }
    ranges::sort(S);
    do {
        string needle;
        [&](this auto &&self, int pos, int k) -> void {
            needle += S[pos];
            if (pos == N - 1) {
                assert(needle.size() <= 16);
                if (3 <= needle.size() && !T.contains(needle)) {
                    cout << needle << "\n";
                    exit(0);
                }
                for (auto i = 0; i < int(S[pos].size()); ++i) {
                    needle.pop_back();
                }
                return;
            }
            for (auto i = 1; i <= k; ++i) {
                needle.push_back('_');
                self(pos + 1, k - i);
            }
            while (!needle.empty() && needle.back() == '_') {
                needle.pop_back();
            }
            for (auto i = 0; i < int(S[pos].size()); ++i) {
                needle.pop_back();
            }
        }(0, 16 - total);
    } while (next_permutation(begin(S), end(S)));
    cout << "-1\n";
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
