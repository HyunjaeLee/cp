#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using i128 = __int128;

i64 F(i64 a, i64 b, i64 r) {
    assert(a > b);
    auto fit = true;
    if (__lg(a) <= __lg(r)) {
        auto x = 1LL << __lg(a);
        auto y = x ^ (a ^ b);
        return x - y;
    }
    for (auto i = __lg(r); 0 <= i; --i) {
        if (fit) {
            if ((r >> i) & 1) {
                if ((a >> i) & 1) {
                    a ^= 1LL << i;
                    b ^= 1LL << i;
                } else {
                    fit = false;
                }
            }
        } else {
            if ((a >> i) & 1) {
                a ^= 1LL << i;
                b ^= 1LL << i;
            }
        }
    }
    return a - b;
}

i64 G(i64 a, i64 b, i64 r) {
    assert(a > b);
    if (__lg(a) > __lg(r)) {
        return numeric_limits<i64>::max();
    }
    if (__lg(a) < __lg(r)) {
        auto x = 1LL << __lg(a);
        auto y = x ^ (a ^ b);
        return x - y;
    }
    swap(a, b);
    auto m = 1LL << __lg(b);
    a ^= m;
    b ^= m;
    auto fit = true;
    for (auto i = __lg(r) - 1; 0 <= i; --i) {
        if (fit) {
            if ((r >> i) & 1) {
                if ((a >> i) & 1) {
                    a ^= 1LL << i;
                    b ^= 1LL << i;
                } else {
                    fit = false;
                }
            }
        } else {
            if ((a >> i) & 1) {
                a ^= 1LL << i;
                b ^= 1LL << i;
            }
        }
    }
    return a - b;
}

void solve() {
    i64 a, b, r;
    cin >> a >> b >> r;
    auto m = a ^ b;
    a &= m;
    b &= m;
    if (a < b) {
        swap(a, b);
    }
    if (a == b || r == 0) {
        cout << a - b << "\n";
        return;
    }
    auto ans = min(F(a, b, r), G(a, b, r));
    cout << ans << "\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}
