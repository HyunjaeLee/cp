#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using i128 = __int128;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int N, M;
    cin >> N >> M;
    string S, T;
    cin >> S >> T;
    auto X = 0;
    for (auto i = 0; i < N; ++i) {
        X |= 1 << (S[i] - 'a');
    }
    auto Y = 0;
    for (auto i = 0; i < M; ++i) {
        Y |= 1 << (T[i] - 'a');
    }
    int Q;
    cin >> Q;
    while (Q--) {
        string W;
        cin >> W;
        auto Z = 0;
        for (auto i = 0; i < int(W.size()); ++i) {
            Z |= 1 << (W[i] - 'a');
        }
        auto a = (Z | X) == X;
        auto b = (Z | Y) == Y;
        if (a and not b) {
            cout << "Takahashi\n";
        } else if (not a and b) {
            cout << "Aoki\n";
        } else {
            cout << "Unknown\n";
        }
    }
}
