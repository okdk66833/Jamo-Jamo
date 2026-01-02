<p align="center">
  <img width="80" height="80" alt="icon" src="https://github.com/user-attachments/assets/6e2a05e9-782c-45d3-a60b-8e734bceac3f" />
  <br/>
<a href="./README.en.md">English</a> | <a href="./README.md">Korean</a>
</p>

# Jamo-Jamo
한글 자모 처리를 위한 편리한 C++ 라이브러리.

# 요구 사항
- C++11 이상
- [Boost.Nowide](https://github.com/boostorg/nowide) 라이브러리

# 문서
- [레퍼런스](./docs/REFERENCE.ko.md)

# 예제
```cpp
#include <jamojamo.hpp>
int main(){
    std::string text = "안녕하세요 Hello 123";
    std::cout << jamojamo::count(text, "ㅇ") << std::endl;
    std::cout << jamojamo::count(text, "ㅏ") << std::endl;

    std::cout << jamojamo::disassemble(text) << std::endl;

    std::cout << jamojamo::get_onset(text) << std::endl;
    std::cout << jamojamo::get_nucleus(text) << std::endl;

    std::string word = "사과";
    if(jamojamo::has_coda(word)) std::cout << word << "은";
    else std::cout << word << "는";
    return 0;
}
```
```bash
1
2
ㅇㅏㄴ ㄴㅕㅇ ㅎㅏ ㅅㅔ ㅇㅛ   H e l l o   1 2 3
ㅇㄴㅎㅅㅇ
ㅏㅕㅏㅔㅛ
사과는
```