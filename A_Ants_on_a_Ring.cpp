#include <bits/stdc++.h>
using namespace std;

constexpr auto inf = numeric_limits<int>::max();

int solve(int N, int L, vector<int> A, vector<int> B) {
    vector<pair<int, int>> v;
    for (auto i = 0; i < N; ++i) {
        auto x = (L + A[i] - A[0]) % L;
        auto y = (L + B[i] - A[0]) % L;
        v.emplace_back(x, y);
    }
    vector<int> I(N);
    iota(begin(I), end(I), 0);
    ranges::sort(I, {}, [&](int i) { return v[i]; });
    auto f = v[0].second;
    auto val = v[0].second;
    for (auto i : I | views::drop(1)) {
        auto [s, t] = v[i];
        if (f < t) {
            f = t;
        } else if (f < t + L) {
            f = t + L;
        } else {
            return inf;
        }
        val = max(val, abs(f - s));
    }
    if (v[0].second + L <= f)
        return inf;
    return val;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int N, L;
    cin >> N >> L;
    vector<int> A(N), B(N);
    for (auto &x : A) {
        cin >> x;
        --x;
    }
    for (auto &x : B) {
        cin >> x;
        --x;
    }
    auto ans = solve(N, L, A, B);
    for (auto &x : A) {
        x = (L - x) % L;
    }
    for (auto &x : B) {
        x = (L - x) % L;
    }
    ans = min(ans, solve(N, L, A, B));
    if (ans < inf)
        cout << ans << "\n";
    else
        cout << "*\n";
}
