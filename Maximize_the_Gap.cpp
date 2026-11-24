#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using i128 = __int128;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int N, K;
    cin >> N >> K;
    vector<pair<int, int>> A(N);
    for (auto &[L, R] : A) {
        cin >> L >> R;
    }
    auto pred = [&](int x) {
        vector<pair<int, int>> rng;
        for (auto [L, R] : A) {
            rng.emplace_back(R + x, L);
        }
        ranges::sort(rng);
        auto p = -1;
        auto cnt = 0;
        for (auto [R, L] : rng) {
            if (p <= L) {
                p = R;
                cnt += 1;
            }
        }
        return K <= cnt;
    };
    auto ans = *ranges::partition_point(views::iota(1, 1'000'000'734), pred) - 1;
    if (ans <= 0)
        ans = -1;
    cout << ans << "\n";
}
