#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using i128 = __int128;

void solve() {
    int N;
    string S;
    cin >> N >> S;
    if (ranges::count(S, '0') != ranges::count(S, '1')) {
        cout << "-1\n";
        return;
    }
    vector<int> ans;
    for (auto i = 0; i < int(S.size()) / 2; ++i) {
        auto j = int(S.size()) - 1 - i;
        if (S[i] == '0' && S[j] == '0') {
            S.insert(j + 1, "01");
            ans.push_back(j + 1);
        } else if (S[i] == '1' && S[j] == '1') {
            S.insert(i, "01");
            ans.push_back(i);
        }
    }
    cout << size(ans) << "\n";
    ranges::copy(ans, ostream_iterator<int>(cout, " "));
    cout << "\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}
