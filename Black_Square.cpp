#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using i128 = __int128;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int P, Q, X, Y;
    cin >> P >> Q >> X >> Y;
    auto ok = (P <= X && X < P + 100) && (Q <= Y && Y < Q + 100);
    cout << (ok ? "Yes\n" : "No\n");
}
