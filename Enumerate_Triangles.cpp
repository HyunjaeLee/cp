#include <bits/stdc++.h>

// O(n + m * sqrt(m))
void enumerate_triangles(int n, const std::vector<std::pair<int, int>> &edges, auto f) {
    std::vector<int> deg(n);
    for (auto [u, v] : edges) {
        ++deg[u];
        ++deg[v];
    }
    std::vector<std::vector<int>> g(n);
    for (auto [u, v] : edges) {
        if (std::pair(deg[u], u) < std::pair(deg[v], v)) {
            std::swap(u, v);
        }
        g[u].push_back(v);
    }
    std::vector<int> color(n, -1);
    for (auto i = 0; i < n; ++i) {
        for (auto j : g[i]) {
            color[j] = i;
        }
        for (auto j : g[i]) {
            for (auto k : g[j]) {
                if (color[k] == i) {
                    f(i, j, k);
                }
            }
        }
    }
}

int main() {
    std::cin.tie(0)->sync_with_stdio(0);
    int N, M;
    std::cin >> N >> M;
    std::vector<int> A(N);
    for (auto &x : A) {
        std::cin >> x;
    }
    std::vector<std::pair<int, int>> E(M);
    for (auto &[u, v] : E) {
        std::cin >> u >> v;
    }
    __int128 sum = 0;
    auto f = [&](int i, int j, int k) { sum += __int128(A[i]) * A[j] * A[k]; };
    enumerate_triangles(N, E, f);
    auto ans = int(sum % 998244353);
    std::cout << ans << "\n";
}
