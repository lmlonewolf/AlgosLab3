#include "Header.h"

int main(){
    std::string str;
    std::getline(std::cin, str);

    BracketsTest test1(str);
    test1.test();
    std::cout << "First error: " << test1.first_error << std::endl;
    std::cout << "Type error: " << test1.get_type_error() << std::endl;
    std::cout << "Count pair: " << test1.count_pair << std::endl;
    std::cout << "Max deep: " << test1.max_deep << std::endl;
    std::cout << "Brackets balance: " << test1.get_brackets_balance() << std::endl;
}