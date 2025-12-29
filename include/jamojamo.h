#ifndef JAMOJAMO_H
#define JAMOJAMO_H

#include <string>

class JamoJamo{
public:
    JamoJamo();
    // count_jamo: count the number of jamo in the text
    // wstring text, wchar_t jamo
    int count_jamo(const std::wstring& text, wchar_t jamo);
    // wstring text, string jamo
    int count_jamo(const std::wstring& text, std::string jamo);
    // wstring text, char jamo
    int count_jamo(const std::wstring& text, char jamo);
    // string text, wchar_t jamo
    int count_jamo(const std::string& text, wchar_t jamo);
    // string text, string jamo
    int count_jamo(const std::string& text, std::string jamo);
    // string text, char jamo
    int count_jamo(const std::string& text, char jamo);
    
private:
    std::wstring to_wstring(const std::string& str);
    static const wchar_t CHOSUNG[];
    static const wchar_t JUNGSUNG[];
    static const wchar_t JONGSUNG[];
};

#endif
