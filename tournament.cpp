#include <atcoder/modint>
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using i128 = __int128;
using Z = atcoder::modint998244353;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int N, K;
    cin >> N >> K;
    vector<int> G(K);
    copy_n(istream_iterator<int>(cin), K, begin(G));
    Z ans = 0;
    Z sum = 0;
    for (auto h = 0; h < N; ++h) {
        sum += Z(2).pow(N - h - 1).inv().pow(2) * Z(2).pow(h) * (Z(2).pow(N - h - 1) / Z(2).pow(N)) *
               (Z(2).pow(N - h - 1) / (Z(2).pow(N) - 1));
    }
    for (auto i = 0; i < K; ++i) {
        ans += Z(G[i]) * Z(G[i] - 1) * sum;
    }
    cout << ans.val() << "\n";
}
