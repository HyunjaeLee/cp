#include <bits/stdc++.h>
using namespace std;

vector<int> cartesian_tree(vector<int> a) {
    auto n = ssize(a);
    vector<int> parent(n, -1), st;
    for (auto i = 0; i < n; ++i) {
        auto v = -1;
        while (!empty(st) && a[i] < a[st.back()]) v = st.back(), st.pop_back();
        if (!empty(st)) parent[i] = st.back();
        if (~v) parent[v] = i;
        st.push_back(i);
    }
    return parent;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int N;
    cin >> N;
    vector<int> A(N);
    for (auto &x : A)
        cin >> x;
    auto parent = cartesian_tree(A);
    for (auto i = 0; i < N; ++i) {
        cout << (~parent[i] ? parent[i] : i) << " ";
    }
}
