#include <print>
#include <string>
#include <array>
#include <cassert>

class DoublePermutationCypher {
public:
  template<size_t N, size_t M>
  static std::string encrypt(const std::string& s,
                             const std::array<size_t, N>& rows,
                             const std::array<size_t, M>& cols) {
    assert(s.size() <= N * M);
    assert(isPermutation(rows));
    assert(isPermutation(cols));

    std::string enc;
    enc.reserve(s.size());

    for (size_t i = 0; i < N; ++i) {
      for (size_t j = 0; j < M; ++j) {
        const size_t k = rows[i] * M + cols[j];
        if (k < s.size()) {
          enc += s[k];
        }
      }
    }

    return enc;
  }

  template<size_t N, size_t M>
  static std::string decrypt(const std::string& s,
                             const std::array<size_t, N>& rows,
                             const std::array<size_t, M>& cols) {
    assert(s.size() <= N * M);
    assert(isPermutation(rows));
    assert(isPermutation(cols));
  
    std::string dec(s.size(), '\0');
    size_t pos = 0;

    for (size_t i = 0; i < N; ++i) {
      for (size_t j = 0; j < M; ++j) {
        const size_t k = rows[i] * M + cols[j];
        if (k < s.size()) {
          dec[k] = s[pos++];
        }
      }
    }

    return dec;
  }

private:
  template<size_t N>
  static bool isPermutation(const std::array<size_t, N>& p) {
    std::array<bool, N> seen {};
    for (size_t i = 0; i < N; ++i) {
      if (p[i] >= N || seen[p[i]]) {
        return false;
      }
      seen[p[i]] = true;
    }
    return true;
  }

};

int main() {
  std::string str = "text to encode";

  std::array<size_t, 4> rows {3, 2, 1, 0};
  std::array<size_t, 4> cols {2, 0, 3, 1};

  std::string enc = DoublePermutationCypher::encrypt(str, rows, cols);
  std::string dec = DoublePermutationCypher::decrypt(enc, rows, cols);

  std::print("enc: {}\n", enc);
  std::print("dec: {}\n", dec);

  assert(enc != dec);
  assert(str == dec);
}