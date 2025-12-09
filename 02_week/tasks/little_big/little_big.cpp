#include <iostream>
#include <iomanip>
#include <cstring>
#include <algorithm>

void PrintMemory(int number, bool inversion = false) {
    unsigned char bytes[sizeof(int)];
    std::memcpy(bytes, &number, sizeof(int));
    
    if (inversion) {
        std::reverse(bytes, bytes + sizeof(int));
    }
    
    std::cout << "0x";
    for (size_t i = 0; i < sizeof(int); ++i) {
        std::cout << std::hex << std::uppercase 
                  << std::setfill('0') << std::setw(2) 
                  << static_cast<unsigned int>(bytes[i]);
    }
    std::cout << std::dec << std::endl;
}

void PrintMemory(double number, bool inversion = false) {
    unsigned char bytes[sizeof(double)];
    std::memcpy(bytes, &number, sizeof(double));
    
    if (inversion) {
        std::reverse(bytes, bytes + sizeof(double));
    }
    
    std::cout << "0x";
    for (size_t i = 0; i < sizeof(double); ++i) {
        std::cout << std::hex << std::uppercase 
                  << std::setfill('0') << std::setw(2) 
                  << static_cast<unsigned int>(bytes[i]);
    }
    std::cout << std::dec << std::endl;
}