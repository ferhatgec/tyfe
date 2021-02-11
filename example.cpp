#include <iostream>
#include "Tyfe.hpp"

int main() {
    Tyfe check;
    
    std::string data;
    
    std::cout << "File: ";
    
    std::cin >> data;
     
    std::cout << "File type: ";
    
    switch(check.check(data)) {
        case JPEG:
            std::cout << "JPEG\n";
            break;
            
        case FLASCRIPT:
            std::cout << "FlaScript\n";
            break;
            
        case BASH:
            std::cout << "BASH\n";
            break;
            
        case SH:
            std::cout << "SH\n";
            break;
            
        case PNG:
            std::cout << "PNG\n";
            break;
            
        case GIF:
            std::cout << "GIF\n";
            break;
            
        case BMP:
            std::cout << "BMP\n";
            break;
            
        case WEBP:
            std::cout << "WEBP\n";
            break;
            
        case PDF:
            std::cout << "PDF\n";
            break;
    }
    
    return 0;
}
