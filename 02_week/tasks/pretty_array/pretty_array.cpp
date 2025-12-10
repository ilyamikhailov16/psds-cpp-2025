#include <iostream>

void PrintArray(const int* begin, const int* end, const int count = 0) {
    if (begin == nullptr || end == nullptr || count < 0) {
        std::cout << "[]\n";
        return;
    }

    std::cout << "[";
    if (begin < end) {
        for (const int* ptr = begin; ptr < end; ++ptr) {
            if (count > 0 && static_cast<int>(ptr - begin) % count == 0 && ptr != begin){
                std::cout << "...\n ";
            }

            std::cout << *ptr;
            if (ptr != end - 1) {
                std::cout << ", ";
            }
        }
    }
    else if (begin > end) {
        for (const int* ptr = begin; ptr > end; --ptr) {
            if (count > 0 && static_cast<int>(begin - ptr) % count == 0 && ptr != begin) {
                std::cout << "...\n ";
            }

            std::cout << *ptr;
            if (ptr != end + 1) {
                std::cout << ", ";
            }
        }
    }
    std::cout << "]\n";
}