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

    // get_onset: wstring text
    std::wstring get_onset(const std::wstring& text){
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

    // get_onset: string text
    std::string get_onset(const std::string& text){
        std::wstring wtext=to_wstring(text);
        std::wstring wresult=get_onset(wtext);
        return boost::nowide::narrow(wresult);
    }

    // get_nucleus: wstring text
    std::wstring get_nucleus(const std::wstring& text){
        std::wstring result;
        result.reserve(text.length());
        for(const auto& ch:text){
            if(ch>=0xAC00 && ch<=0xD7A3){
                int syllable_index=ch-0xAC00;
                int jung_index=(syllable_index/28)%21;
                result+=JUNGSUNG[jung_index];
            }else{
                result+=ch;
            }
        }
        return result;
    }

    // get_nucleus: string text
    std::string get_nucleus(const std::string& text){
        std::wstring wtext=to_wstring(text);
        std::wstring wresult=get_nucleus(wtext);
        return boost::nowide::narrow(wresult);
    }

    // disassemble: wstring text
    std::wstring disassemble(const std::wstring& text){
        std::wstring result;
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

    // has_coda: wstring text
    bool has_coda(const std::wstring& text){
        if(text.empty()) return false;
        wchar_t last_char=text.back();
        
        if(last_char>=0xAC00 && last_char<=0xD7A3){
            int syllable_index=last_char-0xAC00;
            int jong_index=syllable_index%28;
            return jong_index>0;
        }
        return false;
    }

    // has_coda: string text
    bool has_coda(const std::string& text){
        std::wstring wtext=to_wstring(text);
        return has_coda(wtext);
    }

    // is_hangul: wchar_t ch
    bool is_hangul(wchar_t ch){
        if(ch>=0xAC00 && ch<=0xD7A3) return true;
        if(ch>=0x1100 && ch<=0x11FF) return true;
        if(ch>=0x3130 && ch<=0x318F) return true;
        if(ch>=0xA960 && ch<=0xA97F) return true;
        if(ch>=0xD7B0 && ch<=0xD7FF) return true;
        return false;
    }

    // is_hangul: char ch
    bool is_hangul(char ch){
        return is_hangul((wchar_t)ch);
    }

    // is_complete_hangul: wchar_t ch
    bool is_complete_hangul(wchar_t ch){
        return (ch>=0xAC00 && ch<=0xD7A3);
    }

    // is_complete_hangul: char ch
    bool is_complete_hangul(char ch){
        return is_complete_hangul((wchar_t)ch);
    }

    // get_jamo: wstring text
    wchar_t get_jamo(const std::wstring& text, size_t index, char type){
        if(index>=text.length()) return L'\0';
        
        wchar_t ch=text[index];
        if(ch>=0xAC00 && ch<=0xD7A3){
            int syllable_index=ch-0xAC00;
            int cho_index=(syllable_index/28)/21;
            int jung_index=(syllable_index/28)%21;
            int jong_index=syllable_index%28;
            
            if(type=='o' || type=='O') return CHOSUNG[cho_index];
            else if(type=='n' || type=='N') return JUNGSUNG[jung_index];
            else if(type=='c' || type=='C') return JONGSUNG[jong_index];
        }
        return L'\0';
    }

    // get_jamo: string text
    wchar_t get_jamo(const std::string& text, size_t index, char type){
        std::wstring wtext=to_wstring(text);
        return get_jamo(wtext, index, type);
    }
}
