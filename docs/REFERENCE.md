<p align="center">
  <img width="80" height="80" alt="icon" src="https://github.com/user-attachments/assets/6e2a05e9-782c-45d3-a60b-8e734bceac3f" />
  <br/>
  <a href="./REFERENCE.en.md">English</a> | <a href="./REFERENCE.md">Korean</a>
</p>

# JamoJamo API 레퍼런스

JamoJamo는 한글 자모 처리를 위한 C++ 라이브러리입니다. 모든 함수는 `jamojamo` 네임스페이스에 정의되어 있습니다.

## 목차

- [함수](#함수)
  - [count](#count)
  - [get_onset](#get_onset)
  - [get_nucleus](#get_nucleus)
  - [disassemble](#disassemble)
  - [has_coda](#has_coda)
  - [is_hangul](#is_hangul)
  - [is_complete_hangul](#is_complete_hangul)
  - [get_jamo](#get_jamo)
- [사용 예시](#사용-예시)
- [참고사항](#참고사항)

---

## 함수

<a id="count"></a>
### count

텍스트에서 특정 자모의 개수를 세는 함수입니다.

#### 시그니처

| 반환 타입 | 함수 시그니처 |
|----------|--------------|
| `int` | `count(const std::wstring& text, wchar_t jamo)` |
| `int` | `count(const std::wstring& text, const std::string& jamo)` |
| `int` | `count(const std::wstring& text, char jamo)` |
| `int` | `count(const std::string& text, wchar_t jamo)` |
| `int` | `count(const std::string& text, const std::string& jamo)` |
| `int` | `count(const std::string& text, char jamo)` |

#### 파라미터

| 파라미터 | 타입 | 설명 |
|---------|------|------|
| `text` | `const std::wstring&` / `const std::string&` | 검색할 텍스트 |
| `jamo` | `wchar_t` / `const std::string&` / `char` | 찾을 자모 (초성, 중성, 종성 모두 가능) |

#### 반환값

텍스트에서 해당 자모가 나타나는 총 개수 (완성형 한글 내부의 자모도 포함)

#### 예시

```cpp
std::string text = "안녕하세요";
int cnt = jamojamo::count(text, "ㅇ");  // 2
int cnt2 = jamojamo::count(text, "ㅏ"); // 1
```

---

<a id="get_onset"></a>
### get_onset

텍스트에서 초성(onset)만 추출하는 함수입니다.

#### 시그니처

| 반환 타입 | 함수 시그니처 |
|----------|--------------|
| `std::wstring` | `get_onset(const std::wstring& text)` |
| `std::string` | `get_onset(const std::string& text)` |

#### 파라미터

| 파라미터 | 타입 | 설명 |
|---------|------|------|
| `text` | `const std::wstring&` / `const std::string&` | 추출할 텍스트 |

#### 반환값

각 글자의 초성만 추출한 문자열. 한글이 아닌 문자는 그대로 유지됩니다.

#### 예시

```cpp
std::string text = "안녕하세요";
std::string result = jamojamo::get_onset(text);  // "ㅇㄴㅎㅅㅇ"
```

---

<a id="get_nucleus"></a>
### get_nucleus

텍스트에서 중성(nucleus)만 추출하는 함수입니다.

#### 시그니처

| 반환 타입 | 함수 시그니처 |
|----------|--------------|
| `std::wstring` | `get_nucleus(const std::wstring& text)` |
| `std::string` | `get_nucleus(const std::string& text)` |

#### 파라미터

| 파라미터 | 타입 | 설명 |
|---------|------|------|
| `text` | `const std::wstring&` / `const std::string&` | 추출할 텍스트 |

#### 반환값

각 글자의 중성만 추출한 문자열. 한글이 아닌 문자는 그대로 유지됩니다.

#### 예시

```cpp
std::string text = "안녕하세요";
std::string result = jamojamo::get_nucleus(text);  // "ㅏㅕㅏㅔㅛ"
```

---

<a id="disassemble"></a>
### disassemble

완성형 한글을 개별 자모로 완전히 분해하는 함수입니다.

#### 시그니처

| 반환 타입 | 함수 시그니처 |
|----------|--------------|
| `std::wstring` | `disassemble(const std::wstring& text)` |
| `std::string` | `disassemble(const std::string& text)` |

#### 파라미터

| 파라미터 | 타입 | 설명 |
|---------|------|------|
| `text` | `const std::wstring&` / `const std::string&` | 분해할 텍스트 |

#### 반환값

각 완성형 한글을 초성+중성+종성으로 분해한 문자열. 종성이 없는 경우 초성+중성만 반환됩니다.

#### 예시

```cpp
std::string text = "한글";
std::string result = jamojamo::disassemble(text);  // "ㅎㅏㄴㄱㅡㄹ"
```

---

<a id="has_coda"></a>
### has_coda

문자열의 마지막 글자에 받침(종성/coda)이 있는지 확인하는 함수입니다.

#### 시그니처

| 반환 타입 | 함수 시그니처 |
|----------|--------------|
| `bool` | `has_coda(const std::wstring& text)` |
| `bool` | `has_coda(const std::string& text)` |

#### 파라미터

| 파라미터 | 타입 | 설명 |
|---------|------|------|
| `text` | `const std::wstring&` / `const std::string&` | 확인할 텍스트 |

#### 반환값

마지막 글자에 받침이 있으면 `true`, 없으면 `false`

#### 예시

```cpp
std::string word1 = "사과";
std::string word2 = "수박";
bool has1 = jamojamo::has_coda(word1);  // false
bool has2 = jamojamo::has_coda(word2);  // true

// 조사 선택에 활용
std::string particle = jamojamo::has_coda(word1) ? "은" : "는";  // "는"
```

---

<a id="is_hangul"></a>
### is_hangul

문자가 한글인지 확인하는 함수입니다. 완성형 한글과 자모 모두 포함합니다.

#### 시그니처

| 반환 타입 | 함수 시그니처 |
|----------|--------------|
| `bool` | `is_hangul(wchar_t ch)` |
| `bool` | `is_hangul(char ch)` |

#### 파라미터

| 파라미터 | 타입 | 설명 |
|---------|------|------|
| `ch` | `wchar_t` / `char` | 확인할 문자 |

#### 반환값

한글이면 `true`, 아니면 `false`

#### 예시

```cpp
bool result1 = jamojamo::is_hangul(L'가');  // true
bool result2 = jamojamo::is_hangul(L'ㄱ');  // true (자모)
bool result3 = jamojamo::is_hangul(L'A');   // false
```

---

<a id="is_complete_hangul"></a>
### is_complete_hangul

문자가 완성형 한글(가~힣)인지 확인하는 함수입니다. 자모는 제외합니다.

#### 시그니처

| 반환 타입 | 함수 시그니처 |
|----------|--------------|
| `bool` | `is_complete_hangul(wchar_t ch)` |
| `bool` | `is_complete_hangul(char ch)` |

#### 파라미터

| 파라미터 | 타입 | 설명 |
|---------|------|------|
| `ch` | `wchar_t` / `char` | 확인할 문자 |

#### 반환값

완성형 한글이면 `true`, 아니면 `false`

#### 예시

```cpp
bool result1 = jamojamo::is_complete_hangul(L'가');  // true
bool result2 = jamojamo::is_complete_hangul(L'ㄱ');   // false (자모)
bool result3 = jamojamo::is_complete_hangul(L'A');   // false
```

---

<a id="get_jamo"></a>
### get_jamo

특정 위치의 글자에서 초성, 중성, 또는 종성을 개별적으로 추출하는 함수입니다.

#### 시그니처

| 반환 타입 | 함수 시그니처 |
|----------|--------------|
| `wchar_t` | `get_jamo(const std::wstring& text, size_t index, char type)` |
| `wchar_t` | `get_jamo(const std::string& text, size_t index, char type)` |

#### 파라미터

| 파라미터 | 타입 | 설명 |
|---------|------|------|
| `text` | `const std::wstring&` / `const std::string&` | 추출할 텍스트 |
| `index` | `size_t` | 글자의 위치 (0부터 시작) |
| `type` | `char` | 추출할 자모 타입: `'o'`/`'O'` (초성), `'n'`/`'N'` (중성), `'c'`/`'C'` (종성) |

#### 반환값

추출된 자모. 한글이 아니거나 인덱스가 범위를 벗어나면 `'\0'`을 반환합니다.

#### 예시

```cpp
std::wstring text = L"한글";
wchar_t cho = jamojamo::get_jamo(text, 0, 'o');  // L'ㅎ' (초성)
wchar_t jung = jamojamo::get_jamo(text, 0, 'n'); // L'ㅏ' (중성)
wchar_t jong = jamojamo::get_jamo(text, 0, 'c'); // L'ㄴ' (종성)
```

---

## 사용 예시

<details>
<summary><b>조사 자동 선택</b></summary>

`has_coda`를 사용하여 올바른 조사를 자동으로 선택합니다.

```cpp
std::string word = "사과";
std::string particle = jamojamo::has_coda(word) ? "은" : "는";
std::cout << word << particle << std::endl;  // "사과는"
```

</details>

<details>
<summary><b>초성 검색</b></summary>

검색 기능을 위한 초성을 추출합니다.

```cpp
std::string text = "안녕하세요";
std::string initials = jamojamo::get_onset(text);  // "ㅇㄴㅎㅅㅇ"
```

</details>

<details>
<summary><b>자모 분석</b></summary>

자세한 자모 수준 분석을 위해 텍스트를 분해합니다.

```cpp
std::string text = "한글";
std::string decomposed = jamojamo::disassemble(text);  // "ㅎㅏㄴㄱㅡㄹ"
```

</details>

---

## 참고사항

<dl>
<dt><strong>문자열 오버로딩</strong></dt>
<dd>모든 함수는 <code>std::wstring</code>과 <code>std::string</code> 오버로딩을 지원합니다.</dd>

<dt><strong>UTF-8 변환</strong></dt>
<dd>UTF-8 인코딩의 <code>std::string</code>을 사용할 때는 내부적으로 <code>boost::nowide</code>를 사용하여 변환합니다.</dd>

<dt><strong>한글 범위</strong></dt>
<dd>완성형 한글 범위: <code>0xAC00</code> (가) ~ <code>0xD7A3</code> (힣)</dd>

<dt><strong>자모 개수</strong></dt>
<dd>자모: 초성 19개, 중성 21개, 종성 28개(없음 포함)</dd>
</dl>
