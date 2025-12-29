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

    // get_initials: extract initial consonants (chosung) from the text
    std::wstring get_initials(const std::wstring& text);
    std::string get_initials(const std::string& text);

    // disassemble: decompose text into individual jamos
    std::wstring disassemble(const std::wstring& text);
    std::string disassemble(const std::string& text);
}

#endif
