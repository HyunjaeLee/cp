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

auto encode(vector<int> A) {
    auto N = int(A.size());
    vector<pair<int, int>> en;
    for (auto i = 0; i < N; ++i) {
        if (en.empty() || en.back().first != A[i]) {
            en.emplace_back(A[i], 1);
        } else {
            en.back().second++;
        }
    }
    return en;
}

void solve() {
    int N;
    cin >> N;
    vector<int> A(N);
    read(A);
    vector<int> v;
    for (auto [x, f] : encode(A)) {
        for (auto i = 0; i < min(f, 2); ++i) {
            v.push_back(x);
        }
    }
    auto M = int(v.size());
    vector<int> P;
    P.push_back(0);
    for (auto i = 0; i < M - 1; ++i) {
        if (v[i] == v[i + 1]) {
            P.push_back(i + 1);
        }
    }
    P.push_back(M);
    vector<int> Q;
    for (auto [l, r] : views::pairwise(P)) {
        auto split = v[l] == v[r - 1] && r != M;
        if (split) {
            for (auto i = l; i < r - 1; ++i) {
                if (v[i] != v[r - 1] && v[i + 1] != v[r - 1]) {
                    Q.push_back(i + 1);
                    break;
                }
            }
        }
    }
    P.insert(P.end(), Q.begin(), Q.end());
    ranges::sort(P);
    P.erase(unique(begin(P), end(P)), end(P));
    auto color = 0;
    vector<int> B, C;
    for (auto [l, r] : views::pairwise(P)) {
        for (auto i = l; i < r; ++i) {
            (color ? B : C).push_back(v[i]);
        }
        color ^= 1;
    }
    auto ans = size(encode(B)) + size(encode(C));
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
