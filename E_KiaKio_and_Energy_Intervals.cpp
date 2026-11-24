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

#ifndef CARTESIAN_TREE_HPP
#define CARTESIAN_TREE_HPP

#include <vector>

std::vector<int> cartesian_tree(const std::vector<int> &a) {
    const auto n = int(a.size());
    std::vector<int> parent(n, -1), st;
    for (auto i = 0; i < n; ++i) {
        auto v = -1;
        while (!st.empty() && a[i] > a[st.back()]) {
            v = st.back();
            st.pop_back();
        }
        if (!st.empty()) {
            parent[i] = st.back();
        }
        if (~v) {
            parent[v] = i;
        }
        st.push_back(i);
    }
    return parent;
}

#endif // CARTESIAN_TREE_HPP

vector<int> freq(1 << 18);

#define TC
void solve() {
    int N;
    cin >> N;
    vector<int> A(N);
    read(A);
    auto parent = cartesian_tree(A);
    vector<array<int, 2>> children(N, {{-1, -1}});
    auto root = -1;
    for (auto i = 0; i < N; ++i) {
        if (parent[i] == -1) {
            root = i;
        } else if (i < parent[i]) {
            children[parent[i]][0] = i;
        } else {
            children[parent[i]][1] = i;
        }
    }
    vector<int> sz(N, 1);
    [&](this auto &&self, int u) -> void {
        for (auto v : children[u]) {
            if (v != -1) {
                self(v);
                sz[u] += sz[v];
            }
        }
    }(root);
    auto Size = [&](int u) { return u == -1 ? 0 : sz[u]; };
    auto Check = [&](int mask) {
        auto found = false;
        vector<int> pref(N);
        for (auto i = 0; i < N; ++i) {
            pref[i] = A[i] & mask;
        }
        for (auto i = 1; i < N; ++i) {
            pref[i] ^= pref[i - 1];
        }
        auto V = [&](this auto &&self, int u) -> vector<int> {
            if (u == -1)
                return {};
            if (Size(children[u][0]) < Size(children[u][1])) {
                auto S = self(children[u][0]);
                for (auto x : S) {
                    freq[x]--;
                }
                auto T = self(children[u][1]);
                auto l = u - Size(children[u][0]);
                S.push_back(l ? pref[l - 1] : 0);
                T.push_back(pref[u]);
                freq[pref[u]]++;
                if ((A[u] & mask) == mask) {
                    i64 cnt = 0;
                    for (auto x : S) {
                        cnt += freq[x ^ mask];
                    }
                    if (1 < cnt) {
                        found = true;
                    }
                }
                S.pop_back();
                for (auto x : S) {
                    freq[x]++;
                    T.push_back(x);
                }
                return T;
            } else {
                auto T = self(children[u][1]);
                for (auto x : T) {
                    freq[x]--;
                }
                auto S = self(children[u][0]);
                auto l = u - Size(children[u][0]);
                S.push_back(l ? pref[l - 1] : 0);
                freq[l ? pref[l - 1] : 0]++;
                T.push_back(pref[u]);
                if ((A[u] & mask) == mask) {
                    i64 cnt = 0;
                    for (auto x : T) {
                        cnt += freq[x ^ mask];
                    }
                    if (1 < cnt) {
                        found = true;
                    }
                }
                S.pop_back();
                freq[l ? pref[l - 1] : 0]--;
                for (auto x : T) {
                    freq[x]++;
                    S.push_back(x);
                }
                return S;
            }
        }(root);
        for (auto x : V) {
            freq[x]--;
        }
        return found;
    };
    auto ans = 0;
    for (auto i = 17; 0 <= i; --i) {
        if (Check(ans | (1 << i))) {
            ans |= 1 << i;
        }
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
