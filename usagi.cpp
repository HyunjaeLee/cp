#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using i128 = __int128;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int N, M;
    cin >> N >> M;
    if (M == 1) {
        if (26 < N) {
            cout << "NO\n";
            return 0;
        }
        cout << "YES\n";
        for (auto i = 0; i < N; ++i) {
            cout << char('A' + i) << "\n";
        }
        return 0;
    }
    if (10 < N) {
        cout << "NO\n";
        return 0;
    }
    string P = "PQRSTAEIOU";
    string Q = "AEIOUPQRST";
    vector<string> A(N, string(M, '*'));
    for (auto i = 0; i < N; ++i) {
        for (auto j = 0; j < M; ++j) {
            if (j & 1) {
                A[i][j] = Q[i];
            } else {
                A[i][j] = P[i];
            }
        }
    }
    cout << "YES\n";
    for (auto s : A) {
        cout << s << "\n";
    }
}
