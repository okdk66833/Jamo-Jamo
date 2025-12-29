#include <iostream>
#include <string>
#include <cwchar>
#include "../include/jamojamo.h"

int main(){
    JamoJamo jamo;

    std::string s="avcdc";
    std::string target="가";

    int count=jamo.count_jamo(s, target);
    std::cout << __cplusplus << std::endl;
    std::cout<<"Text: "<<s<<std::endl;
    std::cout<<"Count: "<<count<<std::endl;

    return 0;
}

