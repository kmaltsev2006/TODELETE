#include <print>
#include <string>
#include <cassert>

class Scytale {
public:
  static std::string encrypt(const std::string& s, const size_t key) {
    assert(s.size() > key);
 
    std::string enc;
    size_t koef = static_cast<size_t>(s.size() % key != 0);
    for (size_t i = 0; i < key; ++i) {
      for (size_t j = i; j < s.size(); j += key) {
        enc += s[j];
      }
    }
    return enc;
  }

  static std::string decrypt(const std::string& s, const size_t key) {
    std::string dec(s.size(), '\0');
    size_t cols = (s.size() + key - 1) / key;
    size_t rem = s.size() % key;
    size_t pos = 0;

    for (size_t i = 0; i < key; ++i) {
      size_t actual_cols = (rem && i >= rem) ? cols - 1 : cols;
      for (size_t j = 0; j < actual_cols; ++j) {
        dec[i + j * key] = s[pos++];
      }
    }
    return dec;
  }

};


int main() {
  std::string str = "texttoencode!!";
  size_t key = 3;
  
  std::string enc = Scytale::encrypt(str, key);
  std::string dec = Scytale::decrypt(enc, key);
  
  std::print("enc: {}\n", enc);
  std::print("dec: {}\n", dec);

  assert(enc != dec);
  assert(str == dec);
}