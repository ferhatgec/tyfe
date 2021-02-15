#include <iostream>
#include "Tyfe.hpp"

int main() {
    Tyfe check;
    
    std::string data;
    
    std::cout << "File: ";
    
    std::cin >> data;
     
    std::cout << "File type: " << check.type(data) + "\n";

    
    return 0;
}
