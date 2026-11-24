#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using i128 = __int128;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int x, y;
    cin >> x >> y;
    auto g = gcd(x, y);
    auto ok = x / g == 16 && y / g == 9;
    cout << (ok ? "Yes" : "No");
}
