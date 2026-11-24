#include <atcoder/modint>
#include <bits/stdc++.h>
using namespace std;
using Z = atcoder::modint998244353;

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

struct node {
    explicit node(int val = 0) : x(val) {}
    ~node() {
        for (auto i = 0; i < 26; ++i) {
            delete ch[i];
        }
    }
    int x;
    array<node *, 26> ch{};
};

void solve() {
    int N;
    cin >> N;
    vector<string> A(N);
    read(A);
    node *root0 = new node();
    auto insert0 = [&](const string &s) {
        auto u = root0;
        for (auto c : s) {
            auto &v = u->ch[c - 'a'];
            if (!v) {
                v = new node();
            }
            v->x++;
            u = v;
        }
    };
    auto query0 = [&](const string &s) {
        auto u = root0;
        for (auto c : s) {
            auto v = u->ch[c - 'a'];
            assert(v);
            u = v;
        }
        return u->x - 1;
    };
    node *root1 = new node();
    auto insert1 = [&](const string &s) {
        auto u = root1;
        for (auto c : s) {
            auto &v = u->ch[c - 'a'];
            if (!v) {
                v = new node();
            }
            u = v;
        }
        u->x++;
    };
    auto query1 = [&](const string &s) {
        auto u = root1;
        auto sum = 0;
        for (auto c : s) {
            auto v = u->ch[c - 'a'];
            assert(v);
            sum += v->x;
            u = v;
        }
        return sum - 1;
    };
    for (const auto &s : A) {
        insert0(s);
        insert1(s);
    }
    for (const auto &s : A) {
        auto a = query0(s);
        auto b = query1(s);
        auto ans = 1 + b + Z(N - 1 - a - b) / 2;
        cout << ans.val() << "\n";
    }
    delete root0;
    delete root1;
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
