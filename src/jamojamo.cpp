#include <jamojamo.h>
#include <boost/nowide/convert.hpp>

namespace {
    const wchar_t CHOSUNG[]={
        L'ㄱ',L'ㄲ',L'ㄴ',L'ㄷ',L'ㄸ',L'ㄹ',L'ㅁ',L'ㅂ',L'ㅃ',L'ㅅ',
        L'ㅆ',L'ㅇ',L'ㅈ',L'ㅉ',L'ㅊ',L'ㅋ',L'ㅌ',L'ㅍ',L'ㅎ'
    };

    const wchar_t JUNGSUNG[]={
        L'ㅏ',L'ㅐ',L'ㅑ',L'ㅒ',L'ㅓ',L'ㅔ',L'ㅕ',L'ㅖ',L'ㅗ',L'ㅘ',
        L'ㅙ',L'ㅚ',L'ㅛ',L'ㅜ',L'ㅝ',L'ㅞ',L'ㅟ',L'ㅠ',L'ㅡ',L'ㅢ',L'ㅣ'
    };

    const wchar_t JONGSUNG[]={
        L'\0',L'ㄱ',L'ㄲ',L'ㄳ',L'ㄴ',L'ㄵ',L'ㄶ',L'ㄷ',L'ㄹ',L'ㄺ',
        L'ㄻ',L'ㄼ',L'ㄽ',L'ㄾ',L'ㄿ',L'ㅀ',L'ㅁ',L'ㅂ',L'ㅄ',L'ㅅ',
        L'ㅆ',L'ㅇ',L'ㅈ',L'ㅊ',L'ㅋ',L'ㅌ',L'ㅍ',L'ㅎ'
    };

    std::wstring to_wstring(const std::string& str){
        if(str.empty()) return std::wstring();
        return boost::nowide::widen(str);
    }
}

namespace jamojamo {
    // count: wstring text, wchar_t jamo
    int count(const std::wstring& text, wchar_t jamo){
        int cnt=0;
        for(const auto& ch:text){
            if(ch==jamo){
                cnt++;
                continue;
            }
            if(ch>=0xAC00 && ch<=0xD7A3){
                int syllable_index=ch-0xAC00;
                int cho_index=(syllable_index/28)/21;
                int jung_index=(syllable_index/28)%21;
                int jong_index=syllable_index%28;
                if(CHOSUNG[cho_index]==jamo || JUNGSUNG[jung_index]==jamo || (jong_index>0 && JONGSUNG[jong_index]==jamo)) cnt++;
            }
        }
        return cnt;
    }

    // count: wstring text, string jamo
    int count(const std::wstring& text, const std::string& jamo){
        std::wstring w_jamo_str=to_wstring(jamo);
        if(w_jamo_str.empty()) return 0;
        return count(text, w_jamo_str[0]);
    }

    // count: wstring text, char jamo
    int count(const std::wstring& text, char jamo){
        return count(text, (wchar_t)jamo);
    }

    // count: string text, wchar_t jamo
    int count(const std::string& text, wchar_t jamo){
        std::wstring converted_text=to_wstring(text);
        return count(converted_text, jamo);
    }

    // count: string text, string jamo
    int count(const std::string& text, const std::string& jamo){
        std::wstring w_jamo_str=to_wstring(jamo);
        if(w_jamo_str.empty()) return 0;
        wchar_t w_jamo=w_jamo_str[0];
        
        std::wstring converted_text=to_wstring(text);
        return count(converted_text, w_jamo);
    }

    // count: string text, char jamo
    int count(const std::string& text, char jamo){
        return count(text, (wchar_t)jamo);
    }

    // get_initials: wstring text
    std::wstring get_initials(const std::wstring& text){
        std::wstring result;
        result.reserve(text.length());
        for(const auto& ch:text){
            if(ch>=0xAC00 && ch<=0xD7A3){
                int syllable_index=ch-0xAC00;
                int cho_index=(syllable_index/28)/21;
                result+=CHOSUNG[cho_index];
            }else{
                result+=ch;
            }
        }
        return result;
    }

    // get_initials: string text
    std::string get_initials(const std::string& text){
        std::wstring wtext=to_wstring(text);
        std::wstring wresult=get_initials(wtext);
        return boost::nowide::narrow(wresult);
    }

    // disassemble: wstring text
    std::wstring disassemble(const std::wstring& text){
        std::wstring result;
        // Reserve enough space (assuming average 2.5 jamos per hangul char)
        result.reserve(text.length()*3);
        
        for(const auto& ch:text){
            if(ch>=0xAC00 && ch<=0xD7A3){
                int syllable_index=ch-0xAC00;
                int cho_index=(syllable_index/28)/21;
                int jung_index=(syllable_index/28)%21;
                int jong_index=syllable_index%28;
                
                result+=CHOSUNG[cho_index];
                result+=JUNGSUNG[jung_index];
                if(jong_index>0){
                    result+=JONGSUNG[jong_index];
                }
            }else{
                result+=ch;
            }
        }
        return result;
    }

    // disassemble: string text
    std::string disassemble(const std::string& text){
        std::wstring wtext=to_wstring(text);
        std::wstring wresult=disassemble(wtext);
        return boost::nowide::narrow(wresult);
    }
}
