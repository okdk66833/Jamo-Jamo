#include <iostream>
#include <string>
#include <vector>
#include <jamojamo.h>
#include <boost/nowide/convert.hpp>

int main(){
    // Test data
    std::string text="안녕하세요 Hello 123";
    std::string word1="사과";
    std::string word2="수박";

    std::cout<<"=== JamoJamo Library Test ===\n"<<std::endl;

    // 1. Count Jamo
    std::cout<<"[1. Count Jamo]"<<std::endl;
    std::cout<<"Text: "<<text<<std::endl;
    std::cout<<"Count 'ㅇ': "<<jamojamo::count(text, "ㅇ")<<std::endl;
    std::cout<<"Count 'ㅏ': "<<jamojamo::count(text, "ㅏ")<<std::endl;

    // 2. Disassemble
    std::cout<<"\n[2. Disassemble]"<<std::endl;
    std::cout<<"Original: "<<text<<std::endl;
    std::cout<<"Result:   "<<jamojamo::disassemble(text)<<std::endl;

    // 3. Onset & Nucleus Extraction
    std::cout<<"\n[3. Extraction]"<<std::endl;
    std::cout<<"Onset (chosung):   "<<jamojamo::get_onset(text)<<std::endl;
    std::cout<<"Nucleus (jungsung): "<<jamojamo::get_nucleus(text)<<std::endl;

    // 4. Check Coda (Batchim) for Korean Particles
    std::cout<<"\n[4. Coda Check (Particle Selection)]"<<std::endl;
    std::string p1=jamojamo::has_coda(word1) ? "은" : "는";
    std::string p2=jamojamo::has_coda(word2) ? "을" : "를";
    
    std::cout<<word1<<" -> "<<word1<<p1<<std::endl;
    std::cout<<word2<<" -> "<<word2<<p2<<std::endl;

    // 5. Hangul Detection
    std::cout<<"\n[5. Hangul Detection]"<<std::endl;
    std::string test_chars="가Aㄱ1";
    // Need wstring to iterate char by char correctly for hangul
    std::wstring w_test_chars=boost::nowide::widen(test_chars); 
    
    // Simple helper to print bool
    auto print_bool=[](bool b){ return b ? "true" : "false"; };

    // Note: iterating std::string directly in C++ splits multibyte chars, so we use wstring for correct char iteration
    // For demo purposes, we just check specific wide chars corresponding to the string above
    wchar_t chars[]={L'가', L'A', L'ㄱ', L'1'};
    for(wchar_t ch : chars){
        // Convert wchar_t back to string for printing
        std::cout<<"Char '"<<boost::nowide::narrow(std::wstring(1, ch))<<"': ";
        std::cout<<"IsHangul="<<print_bool(jamojamo::is_hangul(ch))<<", ";
        std::cout<<"IsComplete="<<print_bool(jamojamo::is_complete_hangul(ch))<<std::endl;
    }

    return 0;
}
