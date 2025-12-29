#include <iostream>
#include <string>
#include <cwchar>
#include <jamojamo.h>

int main(){
    std::string s="avcdc";
    std::string target="가";

    int count=jamojamo::count(s, target);
    std::cout << __cplusplus << std::endl;
    std::cout<<"Text: "<<s<<std::endl;
    std::cout<<"Count: "<<count<<std::endl;

    return 0;
}
