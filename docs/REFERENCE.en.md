<p align="center">
  <img width="80" height="80" alt="icon" src="https://github.com/user-attachments/assets/6e2a05e9-782c-45d3-a60b-8e734bceac3f" />
  <br/>
  <a href="./REFERENCE.en.md">English</a> | <a href="./REFERENCE.md">Korean</a>
</p>

# JamoJamo API Reference

JamoJamo is a C++ library for processing Korean Jamo (Hangul characters). All functions are defined in the `jamojamo` namespace.

## Table of Contents

- [Functions](#functions)
  - [count](#count)
  - [get_onset](#get_onset)
  - [get_nucleus](#get_nucleus)
  - [disassemble](#disassemble)
  - [has_coda](#has_coda)
  - [is_hangul](#is_hangul)
  - [is_complete_hangul](#is_complete_hangul)
  - [get_jamo](#get_jamo)
- [Usage Examples](#usage-examples)
- [Notes](#notes)

---

## Functions

<a id="count"></a>
### count

Counts the number of occurrences of a specific jamo in the text.

#### Signature

| Return Type | Function Signature |
|------------|-------------------|
| `int` | `count(const std::wstring& text, wchar_t jamo)` |
| `int` | `count(const std::wstring& text, const std::string& jamo)` |
| `int` | `count(const std::wstring& text, char jamo)` |
| `int` | `count(const std::string& text, wchar_t jamo)` |
| `int` | `count(const std::string& text, const std::string& jamo)` |
| `int` | `count(const std::string& text, char jamo)` |

#### Parameters

| Parameter | Type | Description |
|-----------|------|------------|
| `text` | `const std::wstring&` / `const std::string&` | Text to search |
| `jamo` | `wchar_t` / `const std::string&` / `char` | Jamo to find (onset, nucleus, or coda) |

#### Return Value

Total number of occurrences of the jamo in the text (including jamos inside complete Hangul syllables)

#### Example

```cpp
std::string text = "안녕하세요";
int cnt = jamojamo::count(text, "ㅇ");  // 2
int cnt2 = jamojamo::count(text, "ㅏ"); // 1
```

---

<a id="get_onset"></a>
### get_onset

Extracts only the onsets (initial consonants) from the text.

#### Signature

| Return Type | Function Signature |
|------------|-------------------|
| `std::wstring` | `get_onset(const std::wstring& text)` |
| `std::string` | `get_onset(const std::string& text)` |

#### Parameters

| Parameter | Type | Description |
|-----------|------|------------|
| `text` | `const std::wstring&` / `const std::string&` | Text to extract from |

#### Return Value

String containing only the onset of each character. Non-Hangul characters are preserved as-is.

#### Example

```cpp
std::string text = "안녕하세요";
std::string result = jamojamo::get_onset(text);  // "ㅇㄴㅎㅅㅇ"
```

---

<a id="get_nucleus"></a>
### get_nucleus

Extracts only the nuclei (vowels) from the text.

#### Signature

| Return Type | Function Signature |
|------------|-------------------|
| `std::wstring` | `get_nucleus(const std::wstring& text)` |
| `std::string` | `get_nucleus(const std::string& text)` |

#### Parameters

| Parameter | Type | Description |
|-----------|------|------------|
| `text` | `const std::wstring&` / `const std::string&` | Text to extract from |

#### Return Value

String containing only the nucleus of each character. Non-Hangul characters are preserved as-is.

#### Example

```cpp
std::string text = "안녕하세요";
std::string result = jamojamo::get_nucleus(text);  // "ㅏㅕㅏㅔㅛ"
```

---

<a id="disassemble"></a>
### disassemble

Decomposes complete Hangul syllables into individual jamos.

#### Signature

| Return Type | Function Signature |
|------------|-------------------|
| `std::wstring` | `disassemble(const std::wstring& text)` |
| `std::string` | `disassemble(const std::string& text)` |

#### Parameters

| Parameter | Type | Description |
|-----------|------|------------|
| `text` | `const std::wstring&` / `const std::string&` | Text to disassemble |

#### Return Value

String with each complete Hangul syllable decomposed into onset+nucleus+coda. If there is no coda, only onset+nucleus is returned.

#### Example

```cpp
std::string text = "한글";
std::string result = jamojamo::disassemble(text);  // "ㅎㅏㄴㄱㅡㄹ"
```

---

<a id="has_coda"></a>
### has_coda

Checks if the last character of the string has a coda (final consonant).

#### Signature

| Return Type | Function Signature |
|------------|-------------------|
| `bool` | `has_coda(const std::wstring& text)` |
| `bool` | `has_coda(const std::string& text)` |

#### Parameters

| Parameter | Type | Description |
|-----------|------|------------|
| `text` | `const std::wstring&` / `const std::string&` | Text to check |

#### Return Value

Returns `true` if the last character has a coda, `false` otherwise.

#### Example

```cpp
std::string word1 = "사과";
std::string word2 = "수박";
bool has1 = jamojamo::has_coda(word1);  // false
bool has2 = jamojamo::has_coda(word2);  // true

// Useful for particle selection
std::string particle = jamojamo::has_coda(word1) ? "은" : "는";  // "는"
```

---

<a id="is_hangul"></a>
### is_hangul

Checks if a character is Hangul (including both complete syllables and jamos).

#### Signature

| Return Type | Function Signature |
|------------|-------------------|
| `bool` | `is_hangul(wchar_t ch)` |
| `bool` | `is_hangul(char ch)` |

#### Parameters

| Parameter | Type | Description |
|-----------|------|------------|
| `ch` | `wchar_t` / `char` | Character to check |

#### Return Value

Returns `true` if the character is Hangul, `false` otherwise.

#### Example

```cpp
bool result1 = jamojamo::is_hangul(L'가');  // true
bool result2 = jamojamo::is_hangul(L'ㄱ');  // true (jamo)
bool result3 = jamojamo::is_hangul(L'A');   // false
```

---

<a id="is_complete_hangul"></a>
### is_complete_hangul

Checks if a character is a complete Hangul syllable (Ga-Hih range). Excludes jamos.

#### Signature

| Return Type | Function Signature |
|------------|-------------------|
| `bool` | `is_complete_hangul(wchar_t ch)` |
| `bool` | `is_complete_hangul(char ch)` |

#### Parameters

| Parameter | Type | Description |
|-----------|------|------------|
| `ch` | `wchar_t` / `char` | Character to check |

#### Return Value

Returns `true` if the character is a complete Hangul syllable, `false` otherwise.

#### Example

```cpp
bool result1 = jamojamo::is_complete_hangul(L'가');  // true
bool result2 = jamojamo::is_complete_hangul(L'ㄱ');   // false (jamo)
bool result3 = jamojamo::is_complete_hangul(L'A');   // false
```

---

<a id="get_jamo"></a>
### get_jamo

Extracts a specific jamo (onset, nucleus, or coda) from a character at a given index.

#### Signature

| Return Type | Function Signature |
|------------|-------------------|
| `wchar_t` | `get_jamo(const std::wstring& text, size_t index, char type)` |
| `wchar_t` | `get_jamo(const std::string& text, size_t index, char type)` |

#### Parameters

| Parameter | Type | Description |
|-----------|------|------------|
| `text` | `const std::wstring&` / `const std::string&` | Text to extract from |
| `index` | `size_t` | Character position (0-based) |
| `type` | `char` | Jamo type to extract: `'o'`/`'O'` (onset), `'n'`/`'N'` (nucleus), `'c'`/`'C'` (coda) |

#### Return Value

Extracted jamo. Returns `'\0'` if the character is not Hangul or the index is out of range.

#### Example

```cpp
std::wstring text = L"한글";
wchar_t cho = jamojamo::get_jamo(text, 0, 'o');  // L'ㅎ' (onset)
wchar_t jung = jamojamo::get_jamo(text, 0, 'n'); // L'ㅏ' (nucleus)
wchar_t jong = jamojamo::get_jamo(text, 0, 'c'); // L'ㄴ' (coda)
```

---

## Usage Examples

<details>
<summary><b>Automatic Particle Selection</b></summary>

Use `has_coda` to automatically select the correct Korean particle.

```cpp
std::string word = "사과";
std::string particle = jamojamo::has_coda(word) ? "은" : "는";
std::cout << word << particle << std::endl;  // "사과는"
```

</details>

<details>
<summary><b>Initial Consonant Search</b></summary>

Extract initials for search functionality.

```cpp
std::string text = "안녕하세요";
std::string initials = jamojamo::get_onset(text);  // "ㅇㄴㅎㅅㅇ"
```

</details>

<details>
<summary><b>Jamo Analysis</b></summary>

Decompose text for detailed jamo-level analysis.

```cpp
std::string text = "한글";
std::string decomposed = jamojamo::disassemble(text);  // "ㅎㅏㄴㄱㅡㄹ"
```

</details>

---

## Notes

<dl>
<dt><strong>String Overloading</strong></dt>
<dd>All functions support both <code>std::wstring</code> and <code>std::string</code> overloads.</dd>

<dt><strong>UTF-8 Conversion</strong></dt>
<dd>When using UTF-8 encoded <code>std::string</code>, internal conversion uses <code>boost::nowide</code>.</dd>

<dt><strong>Hangul Range</strong></dt>
<dd>Complete Hangul range: <code>0xAC00</code> (가) ~ <code>0xD7A3</code> (힣)</dd>

<dt><strong>Jamo Count</strong></dt>
<dd>Jamos: 19 onsets, 21 nuclei, 28 codas (including none).</dd>
</dl>
