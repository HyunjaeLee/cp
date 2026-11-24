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
template <typename T> void read(vector<T> &a) { for (auto &x : a) cin >> x; }
template <typename T> void show(const vector<T> &a, string_view sep = " ", string_view end = "\n") {
    for (auto i = 0; i < int(a.size()); ++i) {
        if (i) cout << sep;
        cout << a[i];
    }
    cout << end;
}
// clang-format on

#define TC
void solve() {
    int N, Q;
    cin >> N >> Q;
    vector<i64> A(N);
    read(A);
    vector<pair<i64, int>> events;
    for (auto p = 0; p < 30; ++p) {
        vector<int> pref(1 + N + N);
        for (auto i = 0; i < N; ++i) {
            pref[i + 1] = pref[i + 1 + N] = (A[i] >> p) & 1;
        }
        for (auto i = 0; i < N + N; ++i) {
            pref[i + 1] += pref[i];
        }
        if (pref.back() == 0) {
            continue;
        }
        for (auto i = 0; i < N; ++i) {
            auto pred = [&](int t) {
                auto l = i;
                auto r = i + t + 1;
                if (N - t <= i) {
                    r++;
                }
                auto sum = pref[r] - pref[l];
                return sum == 0;
            };
            auto it = ranges::partition_point(views::iota(0, N), pred);
            auto t = *it;
            events.push_back({1LL * t * N + i, p});
        }
    }
    ranges::sort(events);
    vector<int> X(N);
    vector<pair<i64, int>> V;
    for (auto [t, p] : events) {
        auto i = t % N;
        X[i] ^= (1 << p);
        V.push_back({t, X[i]});
    }
    for (auto i = 0; i < int(V.size()) - 1; ++i) {
        V[i + 1].second = max(V[i + 1].second, V[i].second);
    }
    while (Q--) {
        int v;
        cin >> v;
        auto it = ranges::upper_bound(V, v, {}, [](auto a) { return a.second; });
        if (it == V.end()) {
            cout << "-1\n";
        } else {
            cout << it->first + 1 << "\n";
        }
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