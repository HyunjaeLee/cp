#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using i128 = __int128;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int N, X;
    char x_;
    cin >> N >> x_;
    X = x_ - 'A';
    vector<string> A(N);
    for (auto i = 0; i < N; ++i) {
        cin >> A[i];
    }
    for (auto i = 0; i < N; ++i) {
        if (A[i][X] == 'o') {
            cout << "Yes\n";
            return 0;
        }
    }
    cout << "No\n";
}
