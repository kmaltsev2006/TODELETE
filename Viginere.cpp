#include <print>
#include <string>
#include <array>
#include <cassert>
#include <type_traits>

static constexpr size_t kMaxAlphSize {2 << ((sizeof(uint8_t) * 8) - 1)};

template<typename T>
static T mod(const T& a, const T& b) {
  return ((a % b) + b) % b;
}

template<size_t N>
static constexpr auto genOrder(const std::array<uint8_t, N>& alph) {
  std::array<size_t, kMaxAlphSize> ret;
  ret.fill(alph.size());
  for (size_t i = 0; i < alph.size(); ++i) { 
    ret[alph[i]] = i;
  }
  return ret;
}

template<size_t l=0, size_t r=kMaxAlphSize>
static constexpr auto genAlph() {
  static_assert(l < r);
  static_assert(r <= kMaxAlphSize);
  
  std::array<uint8_t, r - l> ret;

  for (size_t i = 0; i < ret.size(); ++i) {
    ret[i] = l + static_cast<uint8_t>(i);
  }

  return ret;
}

template<size_t N>
static constexpr auto genAlph(const char (&alph)[N]) {
  std::array<uint8_t, N - 1> ret;

  for (size_t i = 0; i < ret.size(); ++i) {
    ret[i] = static_cast<uint8_t>(alph[i]);
  }

  return ret;
}

class Viginere {
public:
  static std::string encrypt(const std::string& s, const std::string& key) {
    assert(checkIsInAlpha(s));
    assert(checkIsInAlpha(key));

    std::string enc;

    size_t i = 0;
    for (const auto& c : s) {
      enc += _kAlph[mod(_kOrder[c] + _kOrder[key[i]], _kAlph.size())];
      i = mod(i + 1, key.size());
    }

    return enc;
  }

  static std::string decrypt(const std::string& s, const std::string& key) {
    assert(checkIsInAlpha(s));
    assert(checkIsInAlpha(key));
    std::string dec;

    size_t i = 0;
    for (const auto& c : s) {
      dec += _kAlph[mod(static_cast<int64_t>(_kOrder[c]) -
        static_cast<int64_t>(_kOrder[key[i]]), static_cast<int64_t>(_kAlph.size()))];
      i = mod(i + 1, key.size());
    }

    return dec;
  }

private:
  static constexpr auto _kAlph {genAlph("abcdefghijklmnopqrstuvwxyz ")};
  static constexpr std::array<size_t, kMaxAlphSize> _kOrder {genOrder(_kAlph)};

private:
  static bool checkIsInAlpha(const std::string& s) {
    for (const auto& c : s) {
      if (_kOrder[c] == _kAlph.size()) {
        return false;
      }
    }
    return true;
  }
};

int main() {
  std::string str = "text to encode";
  std::string key = "key";
  std::string enc = Viginere::encrypt(str, key);
  std::string dec = Viginere::decrypt(enc, key);
  
  std::print("enc: {}\n", enc);
  std::print("dec: {}\n", dec);

  assert(enc != dec);
  assert(str == dec);
}