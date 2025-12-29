#ifndef JAMOJAMO_H
#define JAMOJAMO_H

#include <string>

namespace jamojamo {
    // count: count the number of jamo in the text
    int count(const std::wstring& text, wchar_t jamo);
    int count(const std::wstring& text, const std::string& jamo);
    int count(const std::wstring& text, char jamo);
    int count(const std::string& text, wchar_t jamo);
    int count(const std::string& text, const std::string& jamo);
    int count(const std::string& text, char jamo);

    // get_onset: extract onsets (chosung) from the text
    std::wstring get_onset(const std::wstring& text);
    std::string get_onset(const std::string& text);

    // get_nucleus: extract nuclei (jungsung) from the text
    std::wstring get_nucleus(const std::wstring& text);
    std::string get_nucleus(const std::string& text);

    // disassemble: decompose text into individual jamos
    std::wstring disassemble(const std::wstring& text);
    std::string disassemble(const std::string& text);

    // has_coda: check if the last character has a coda (batchim)
    bool has_coda(const std::wstring& text);
    bool has_coda(const std::string& text);

    // is_hangul: check if the character is hangul (including jamo)
    bool is_hangul(wchar_t ch);
    bool is_hangul(char ch);

    // is_complete_hangul: check if the character is a complete hangul syllable (Ga-Hih)
    bool is_complete_hangul(wchar_t ch);
    bool is_complete_hangul(char ch);
}

#endif
