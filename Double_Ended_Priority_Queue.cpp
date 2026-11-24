#include <bits/stdc++.h>

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
            int k = down(1);
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
            int k = down(0);
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

int main() {
    std::cin.tie(0)->sync_with_stdio(0);
    int N, Q;
    std::cin >> N >> Q;
    interval_heap<int> pq;
    for (auto i = 0; i < N; ++i) {
        int x;
        std::cin >> x;
        pq.push(x);
    }
    for (auto i = 0; i < Q; ++i) {
        int t;
        std::cin >> t;
        if (t == 0) {
            int x;
            std::cin >> x;
            pq.push(x);
        } else if (t == 1) {
            std::cout << pq.min() << "\n";
            pq.pop_min();
        } else {
            std::cout << pq.max() << "\n";
            pq.pop_max();
        }
    }
}
