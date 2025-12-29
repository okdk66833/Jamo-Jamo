#ifndef JAMOJAMO_H
#define JAMOJAMO_H

#include <string>

namespace jamojamo {
    // count: count the number of jamo in the text
    // wstring text, wchar_t jamo
    int count(const std::wstring& text, wchar_t jamo);
    // wstring text, string jamo
    int count(const std::wstring& text, const std::string& jamo);
    // wstring text, char jamo
    int count(const std::wstring& text, char jamo);
    // string text, wchar_t jamo
    int count(const std::string& text, wchar_t jamo);
    // string text, string jamo
    int count(const std::string& text, const std::string& jamo);
    // string text, char jamo
    int count(const std::string& text, char jamo);

    // get_onset: extract onsets (chosung) from the text
    std::wstring get_onset(const std::wstring& text);
    std::string get_onset(const std::string& text);

    // disassemble: decompose text into individual jamos
    std::wstring disassemble(const std::wstring& text);
    std::string disassemble(const std::string& text);

    // get_nucleus: extract nuclei (jungsung) from the text
    std::wstring get_nucleus(const std::wstring& text);
    std::string get_nucleus(const std::string& text);

    // has_coda: check if the last character has a coda (batchim)
    bool has_coda(const std::wstring& text);
    bool has_coda(const std::string& text);
}

#endif
