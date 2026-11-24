#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/4003"

#include <bits/stdc++.h>

// https://en.wikipedia.org/wiki/Havel–Hakimi_algorithm
// O(N + M log N)
std::optional<std::vector<std::pair<int, int>>> havel_hakimi(std::vector<int> deg) {
    auto n = int(deg.size());
    std::priority_queue<std::pair<int, int>> pq;
    for (auto i = 0; i < n; ++i) {
        assert(0 <= deg[i]);
        if (0 < deg[i]) {
            pq.emplace(deg[i], i);
        }
    }
    std::vector<std::pair<int, int>> edges;
    while (!pq.empty()) {
        auto [k, u] = pq.top();
        pq.pop();
        if (int(pq.size()) < k) {
            return std::nullopt;
        }
        for (auto i = 0; i < k; ++i) {
            auto [d, v] = pq.top();
            pq.pop();
            --deg[v];
            edges.emplace_back(u, v);
        }
        for (auto [_, v] : edges | std::views::reverse | std::views::take(k)) {
            if (0 < deg[v]) {
                pq.emplace(deg[v], v);
            }
        }
    }
    return edges;
}

// https://en.wikipedia.org/wiki/Erdős–Gallai_theorem
// O(N)
bool erdos_gallai(const std::vector<int> &deg) {
    auto n = int(deg.size());
    auto pref = deg;
    std::ranges::sort(pref, std::greater());
    std::inclusive_scan(pref.begin(), pref.end(), pref.begin());
    if (pref.back() & 1) {
        return false;
    }
    
}

int main() {
    std::cin.tie(0)->sync_with_stdio(0);
    int N;
    std::cin >> N;
    std::vector<int> deg(N);
    for (auto &d : deg) {
        std::cin >> d;
    }
    std::cout << (havel_hakimi(deg) ? "Yes\n" : "No\n");
}
