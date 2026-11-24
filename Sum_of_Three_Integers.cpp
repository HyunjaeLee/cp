#include <atcoder/convolution>
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using i128 = __int128;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int N, X;
    cin >> N >> X;
    vector<int> A(N);
    for (auto i = 0; i < N; ++i) {
        cin >> A[i];
    }
    vector<i64> F(X + 1);
    for (auto i = 0; i < N; ++i) {
        F[A[i]] += 1;
    }
    auto G = atcoder::convolution_ll(F, F);
    for (auto i = 0; i < X; ++i) {
        if (i % 2 == 0) {
            G[i] = (G[i] - F[i / 2]) / 2;
        } else {
            G[i] = G[i] / 2;
        }
    }
    auto k = -1;
    for (auto i = 0; i < N; ++i) {
        auto cnt = G[X - A[i]];
        if (3 * A[i] == X) {
            cnt -= F[A[i]] - 1;
        } else if (2 * A[i] < X) {
            cnt -= F[X - 2 * A[i]];
        }
        if (0 < cnt) {
            k = i;
            break;
        }
    }
    if (k == -1) {
        cout << "-1\n";
        return 0;
    }
    map<int, int> mp;
    vector<int> ans{k};
    for (auto i = 0; i < N; ++i) {
        if (i == k) {
            continue;
        }
        if (mp.contains(X - A[k] - A[i])) {
            auto j = mp[X - A[k] - A[i]];
            ans.push_back(i);
            ans.push_back(j);
            break;
        }
        mp[A[i]] = i;
    }
    assert(ans.size() == 3);
    ranges::sort(ans);
    for (auto i = 0; i < 3; ++i) {
        cout << ans[i] + 1 << " ";
    }
}
