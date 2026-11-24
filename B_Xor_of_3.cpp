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
    vector<int> A(N);
    read(A);
    if (ranges::fold_left(A, 0, bit_xor()) != 0) {
        cout << "NO\n";
        return;
    }
    vector<int> ans;
    auto Act = [&](int i) {
        assert(0 <= i && i + 2 < N);
        auto sum = A[i] ^ A[i + 1] ^ A[i + 2];
        A[i] = A[i + 1] = A[i + 2] = sum;
        ans.push_back(i);
    };
    vector<pair<int, int>> comp;
    {
        auto l = -1, r = -1;
        for (auto i = 0; i < N; ++i) {
            if (A[i] == 1) {
                if (l == -1 && r == -1) {
                    l = i, r = i + 1;
                } else {
                    r++;
                }
            }
            if ((A[i] == 0 || i == N - 1) && (l != -1 || r != -1)) {
                if ((r - l) % 2 == 0) {
                    assert(2 <= r - l);
                    comp.emplace_back(l, r - 1);
                    comp.emplace_back(r - 1, r);
                } else {
                    comp.emplace_back(l, r);
                }
                l = -1, r = -1;
            }
        }
    }
    auto F = [&](int l, int r) {
        assert(0 <= l && l <= r && r <= N);
        if (l == r)
            return true;
        if (0 <= l - 1 && A[l - 1] == 0) {
            for (auto i = l - 1; i + 2 < r; i += 2) {
                Act(i);
            }
            return true;
        } else if (r < N && A[r] == 0) {
            for (auto i = r; l <= i - 2; i -= 2) {
                Act(i - 2);
            }
            return true;
        } else {
            return false;
        }
    };
    vector<int> fails;
    auto recovery = [&] {
        for (auto i : fails | views::reverse) {
            auto ok = F(comp[i].first, comp[i + 1].second);
            if (!ok) {
                return false;
            }
        }
        fails.clear();
        return true;
    };
    assert(comp.size() % 2 == 0);
    for (auto g = 0; g < int(comp.size()); g += 2) {
        auto [l1, r1] = comp[g];
        auto [l2, r2] = comp[g + 1];
        while (r1 + 2 <= l2) {
            Act(r1 - 1);
            r1 += 2;
        }
        if (r1 == l2) { // 1 1 1 1
            if (!F(l1, r2)) {
                fails.push_back(g);
            }
        } else { // 1 1 1 0 1
            Act(r1 - 1);
            F(l1, r1 - 1);
            F(l2 + 1, r2);
            auto ok = recovery();
            assert(ok);
        }
    }
    recovery();
    if (!fails.empty()) {
        cout << "NO\n";
        return;
    }
    for (auto i = 0; i < N; ++i) {
        assert(A[i] == 0);
    }
    cout << "YES\n";
    cout << size(ans) << "\n";
    assert(ssize(ans) <= N);
    show<1>(ans);
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
