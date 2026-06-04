#include "Header.h"

int main(){
    std::string str;
    std::cout << "Input string: ";
    std::getline(std::cin, str);

    BracketsTest test1(str);
    test1.print_full_test();
    return 0;
}