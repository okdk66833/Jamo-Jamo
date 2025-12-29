#include <jamojamo.h>
#include <boost/nowide/convert.hpp>

const wchar_t JamoJamo::CHOSUNG[]={
    L'ㄱ',L'ㄲ',L'ㄴ',L'ㄷ',L'ㄸ',L'ㄹ',L'ㅁ',L'ㅂ',L'ㅃ',L'ㅅ',
    L'ㅆ',L'ㅇ',L'ㅈ',L'ㅉ',L'ㅊ',L'ㅋ',L'ㅌ',L'ㅍ',L'ㅎ'
};

const wchar_t JamoJamo::JUNGSUNG[]={
    L'ㅏ',L'ㅐ',L'ㅑ',L'ㅒ',L'ㅓ',L'ㅔ',L'ㅕ',L'ㅖ',L'ㅗ',L'ㅘ',
    L'ㅙ',L'ㅚ',L'ㅛ',L'ㅜ',L'ㅝ',L'ㅞ',L'ㅟ',L'ㅠ',L'ㅡ',L'ㅢ',L'ㅣ'
};

const wchar_t JamoJamo::JONGSUNG[]={
    L'\0',L'ㄱ',L'ㄲ',L'ㄳ',L'ㄴ',L'ㄵ',L'ㄶ',L'ㄷ',L'ㄹ',L'ㄺ',
    L'ㄻ',L'ㄼ',L'ㄽ',L'ㄾ',L'ㄿ',L'ㅀ',L'ㅁ',L'ㅂ',L'ㅄ',L'ㅅ',
    L'ㅆ',L'ㅇ',L'ㅈ',L'ㅊ',L'ㅋ',L'ㅌ',L'ㅍ',L'ㅎ'
};

JamoJamo::JamoJamo(){}

std::wstring JamoJamo::to_wstring(const std::string& str){
    if(str.empty()) return std::wstring();
    return boost::nowide::widen(str);
}

// count_jamo: wstring text, wchar_t jamo
int JamoJamo::count_jamo(const std::wstring& text, wchar_t jamo){
    int count=0;
    for(const auto& ch:text){
        if(ch==jamo){
            count++;
            continue;
        }
        if(ch>=0xAC00 && ch<=0xD7A3){
            int syllable_index=ch-0xAC00;
            int cho_index=(syllable_index/28)/21;
            int jung_index=(syllable_index/28)%21;
            int jong_index=syllable_index%28;
            if(CHOSUNG[cho_index]==jamo || JUNGSUNG[jung_index]==jamo || (jong_index>0 && JONGSUNG[jong_index]==jamo)) count++;
        }
    }
    return count;
}

// count_jamo: wstring text, string jamo
int JamoJamo::count_jamo(const std::wstring& text, std::string jamo){
    std::wstring w_jamo_str=to_wstring(jamo);
    if(w_jamo_str.empty()) return 0;
    return count_jamo(text, w_jamo_str[0]);
}

// count_jamo: wstring text, char jamo
int JamoJamo::count_jamo(const std::wstring& text, char jamo){
    return count_jamo(text, (wchar_t)jamo);
}

// count_jamo: string text, wchar_t jamo
int JamoJamo::count_jamo(const std::string& text, wchar_t jamo){
    std::wstring converted_text=to_wstring(text);
    return count_jamo(converted_text, jamo);
}

// count_jamo: string text, string jamo
int JamoJamo::count_jamo(const std::string& text, std::string jamo){
    std::wstring w_jamo_str=to_wstring(jamo);
    if(w_jamo_str.empty()) return 0;
    wchar_t w_jamo=w_jamo_str[0];
    
    std::wstring converted_text=to_wstring(text);
    return count_jamo(converted_text, w_jamo);
}

// count_jamo: string text, char jamo
int JamoJamo::count_jamo(const std::string& text, char jamo){
    return count_jamo(text, (wchar_t)jamo);

}

