#include <bits/stdc++.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

#ifdef __x86_64__
#define USE_AVX2
#endif

#ifdef USE_AVX2
#include <immintrin.h>
#endif

using namespace std;

struct Matrix {
    const int rows, cols, stride;
    unsigned long long *data;
    Matrix(int r, int c) : rows(r), cols(c), stride((c + 63) / 64) {
        size_t total_bytes = (size_t)rows * stride * sizeof(unsigned long long);
        data = new unsigned long long[rows * stride];
        memset(data, 0, total_bytes);
    }
    ~Matrix() { delete[] data; }
    void set(int r, int c) { data[r * stride + (c / 64)] |= (1ULL << (c % 64)); }
    bool get(int r, int c) { return (data[r * stride + (c / 64)] >> (c % 64)) & 1; }
#ifdef USE_AVX2
    __attribute__((target("avx2"))) void xor_rows(unsigned long long *d,
                                                  const unsigned long long *s, int start_idx) {
        int i = start_idx;
        for (; i + 4 <= stride; i += 4) {
            auto dst = reinterpret_cast<__m256i *>(&d[i]);
            auto src = reinterpret_cast<const __m256i *>(&s[i]);
            auto sum = _mm256_xor_si256(_mm256_loadu_si256(dst), _mm256_loadu_si256(src));
            _mm256_storeu_si256(dst, sum);
        }
        for (; i < stride; ++i) {
            d[i] ^= s[i];
        }
    }
#else
    void xor_rows(unsigned long long *d, const unsigned long long *s, int start_idx) {
        for (int i = start_idx; i < stride; ++i) {
            d[i] ^= s[i];
        }
    }
#endif
#ifdef USE_AVX2
    __attribute__((target("avx2"))) void set_row(int row, string_view s) {
        auto n = (int)s.size();
        auto one = _mm256_set1_epi8('1');
        auto str = s.data();
        auto dst = (uint32_t *)data;
        auto i = 0;
        for (; i + 32 <= n; i += 32) {
            auto src = reinterpret_cast<const __m256i *>(&str[i]);
            dst[row * stride * 2 + i / 32] =
                (uint32_t)_mm256_movemask_epi8(_mm256_cmpeq_epi8(_mm256_loadu_si256(src), one));
        }
        for (; i < n; i++) {
            if (s[i] == '1') {
                set(row, i);
            }
        }
    }
#endif
    int gaussian_elimination() { // O(min(N, M) * N * M / 64)
        int pivot_row = 0;
        for (int col = 0; col < cols && pivot_row < rows; ++col) {
            int chunk_idx = col / 64;
            unsigned long long bit_mask = (1ULL << (col % 64));
            int sel = -1;
            for (int i = pivot_row; i < rows; ++i) {
                if (data[i * stride + chunk_idx] & bit_mask) {
                    sel = i;
                    break;
                }
            }
            if (sel == -1) {
                continue;
            }
            if (pivot_row != sel) {
                xor_rows(data + pivot_row * stride, data + sel * stride, chunk_idx);
            }
            for (int i = pivot_row + 1; i < rows; ++i) {
                if (data[i * stride + chunk_idx] & bit_mask) {
                    xor_rows(data + i * stride, data + pivot_row * stride, chunk_idx);
                }
            }
            ++pivot_row;
        }
        return pivot_row;
    }
    int gauss_jordan() {
        int pivot_row = 0;
        for (int col = 0; col < cols && pivot_row < rows; ++col) {
            int chunk_idx = col / 64;
            unsigned long long bit_mask = (1ULL << (col % 64));
            int target = -1;
            for (int i = pivot_row; i < rows; ++i) {
                if (data[i * stride + chunk_idx] & bit_mask) {
                    target = i;
                    break;
                }
            }
            if (target == -1) {
                continue;
            }
            if (pivot_row != target) {
                xor_rows(data + pivot_row * stride, data + target * stride, chunk_idx);
            }
            for (int i = 0; i < rows; ++i) {
                if (i != pivot_row && (data[i * stride + chunk_idx] & bit_mask)) {
                    xor_rows(data + i * stride, data + pivot_row * stride, chunk_idx);
                }
            }
            ++pivot_row;
        }
        return pivot_row;
    }
    template <typename T = vector<bool>> vector<T> solve() {
        auto rank = gauss_jordan();
        vector<int> pivot(rank);
        vector<char> is_pivot_col(cols);
        for (auto i = 0, j = 0; i < rank;) {
            if (data[i * stride + j]) {
                pivot[i] = 64 * j + countr_zero(data[i * stride + j]);
                is_pivot_col[pivot[i]] = true;
                ++i;
            } else {
                ++j;
            }
        }
        if (is_pivot_col[cols - 1]) {
            return {};
        }
        T ans(cols - 1);
        for (auto i = 0; i < rank; ++i) {
            ans[pivot[i]] = get(i, cols - 1);
        }
        vector<T> ret = {ans};
        ret.reserve(cols - rank);
        for (auto j = 0; j < cols - 1; ++j) {
            if (is_pivot_col[j]) {
                continue;
            }
            T basis(cols - 1);
            basis[j] = true;
            for (auto i = 0; i < rank; ++i) {
                basis[pivot[i]] = get(i, j);
            }
            ret.push_back(basis);
        }
        return ret;
    }
};

struct scanner {
    scanner() {
        struct stat st;
        fstat(0, &st);
        if (S_ISREG(st.st_mode)) {
            data_ = p_ = (char *)mmap(nullptr, st.st_size + 65536, PROT_READ,
                                      MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
            if (st.st_size) {
                mmap(data_, st.st_size, PROT_READ, MAP_PRIVATE | MAP_FIXED, 0, 0);
            }
        } else {
            auto *s = new std::string(std::istreambuf_iterator<char>(std::cin), {});
            data_ = p_ = s->data();
        }
    }
    template <typename... Args> void operator()(Args &...args) { (scan(args), ...); }
    std::string_view getline() {
        skip();
        auto first = p_;
        while (*p_ >= ' ') {
            ++p_;
        }
        return std::string_view(first, p_ - first);
    }

private:
    void scan(std::integral auto &x) {
        skip();
        x = 0;
        auto is_negative = false;
        if (*p_ == '-') {
            ++p_;
            is_negative = true;
        }
        for (; *p_ > ' '; ++p_) {
            x = (x << 1) + (x << 3) + (*p_ & 15);
        }
        if (is_negative) {
            x = -x;
        }
    }
    void scan(std::floating_point auto &x) {
        skip();
        auto first = p_;
        while (*p_ > ' ') {
            ++p_;
        }
        std::from_chars(first, p_, x);
    }
    void scan(char &x) {
        skip();
        x = *p_++;
    }
    void skip() {
        while (*p_ <= ' ') {
            ++p_;
        }
    }
    char *data_;
    char *p_;
};

scanner scan;

int main() {
    int n, m;
    scan(n, m);
    Matrix mat(n, m + 1);
    for (auto i = 0; i < n; ++i) {
        mat.set_row(i, scan.getline());
    }
    for (auto i = 0; i < n; ++i) {
        char c;
        scan(c);
        if (c == '1') {
            mat.set(i, m);
        }
    }
    auto ans = mat.solve();
    if (ans.empty()) {
        cout << "-1\n";
    } else {
        cout << ans.size() - 1 << "\n";
        for (const auto &v : ans) {
            for (auto i = 0; i < m; ++i) {
                cout << v[i];
            }
            cout << "\n";
        }
    }
}
