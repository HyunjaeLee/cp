#include <atcoder/fenwicktree>
#include <bits/stdc++.h>
using namespace std;

// clang-format off
using i8 = signed char; using u8 = unsigned char;
using i32 = int;        using u32 = unsigned;
using i64 = long long;  using u64 = unsigned long long;
using i128 = __int128;  using u128 = unsigned __int128;
template <typename T> T ceil_div(T a, T b) { return a / b + static_cast<T>((a ^ b) > 0 && a % b != 0); }
template <typename T> T floor_div(T a, T b) { return a / b - static_cast<T>((a ^ b) < 0 && a % b != 0); }
template <int I = 0> void read(auto &a) { for (auto &x : a) { cin >> x; if constexpr (I) { x -= I; } } }
template <int I = 0> void show(const auto &a, string_view sep = " ", string_view end = "\n") {
    for (auto it = a.begin(); it != a.end(); ++it) { if (it != a.begin()) { cout << sep; }
    auto x = *it; if constexpr (I) { x += I; } cout << x; } cout << end;
}
// clang-format on

#ifndef INTERVAL_HEAP_HPP
#define INTERVAL_HEAP_HPP

#include <cassert>
#include <utility>
#include <vector>

// source: https://natsugiri.hatenablog.com/entry/2016/10/10/035445
template <typename T> struct interval_heap {
    interval_heap() = default;
    void push(const T &x) {
        auto k = int(data_.size());
        data_.push_back(x);
        up(k);
    }
    void pop_min() {
        assert(!data_.empty());
        if (int(data_.size()) < 3) {
            data_.pop_back();
        } else {
            std::swap(data_[1], data_.back());
            data_.pop_back();
            auto k = down(1);
            up(k);
        }
    }
    void pop_max() {
        assert(!data_.empty());
        if (int(data_.size()) < 2) {
            data_.pop_back();
        } else {
            std::swap(data_[0], data_.back());
            data_.pop_back();
            auto k = down(0);
            up(k);
        }
    }
    const T &min() const {
        assert(!data_.empty());
        return int(data_.size()) < 2 ? data_[0] : data_[1];
    }
    const T &max() const {
        assert(!data_.empty());
        return data_[0];
    }
    int size() const { return int(data_.size()); }
    bool empty() const { return data_.empty(); }

private:
    int parent(int k) const { return (((k >> 1) - 1) & ~1); }
    int down(int k) {
        auto n = int(data_.size());
        if (k & 1) { // min heap
            while (2 * k + 1 < n) {
                auto c = 2 * k + 3;
                if (n <= c || data_[c - 2] < data_[c]) {
                    c -= 2;
                }
                if (c < n && data_[c] < data_[k]) {
                    std::swap(data_[k], data_[c]);
                    k = c;
                } else {
                    break;
                }
            }
        } else { // max heap
            while (2 * k + 2 < n) {
                auto c = 2 * k + 4;
                if (n <= c || data_[c] < data_[c - 2]) {
                    c -= 2;
                }
                if (c < n && data_[k] < data_[c]) {
                    std::swap(data_[k], data_[c]);
                    k = c;
                } else {
                    break;
                }
            }
        }
        return k;
    }
    int up(int k, int root = 1) {
        if ((k | 1) < int(data_.size()) && data_[k & ~1] < data_[k | 1]) {
            std::swap(data_[k & ~1], data_[k | 1]);
            k ^= 1;
        }
        int p;
        while (root < k && data_[p = parent(k)] < data_[k]) { // max heap
            std::swap(data_[p], data_[k]);
            k = p;
        }
        while (root < k && data_[k] < data_[p = parent(k) | 1]) { // min heap
            std::swap(data_[p], data_[k]);
            k = p;
        }
        return k;
    }
    std::vector<T> data_;
};

#endif // INTERVAL_HEAP_HPP

#define TC
void solve() {
    int N, K;
    cin >> N >> K;
    vector<i64> A(N);
    read(A);
    interval_heap<i64> heap;
    for (auto i = 0; i < N; ++i) {
        heap.push(A[i]);
    }
    vector<i64> B;
    for (auto i = 0; i < K; ++i) {
        B.push_back(heap.max());
        heap.pop_max();
    }
    ranges::reverse(B);
    for (auto i = 0; i < N - K; ++i) {
        B.push_back(heap.max());
        heap.pop_max();
    }
    assert(ssize(B) == N);
    atcoder::fenwick_tree<i64> ft(N);
    for (auto i = 0; i < N; ++i) {
        ft.add(i, B[i]);
    }
    auto cnt = 0;
    for (auto i = 0; i < N; ++i) {
        if (ft.sum(0, i) <= i * B[i]) {
            cnt++;
        }
    }
    if (cnt == K) {
        cout << "YES\n";
        show(B);
    } else {
        cout << "NO\n";
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int t = 1;
#ifdef TC
    cin >> t;
#endif
    for (auto i = 0; i < t; ++i) {
        solve();
    }
}
