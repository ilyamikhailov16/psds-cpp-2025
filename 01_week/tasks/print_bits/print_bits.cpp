#include <cstddef>
#include <iostream>
#include <vector>


void PrintBits(long long value, size_t bytes) {
    if (bytes <= 0 || bytes > 8) {
        return;
    }

    std::cout << "0b";

    // Выводим биты, начиная со старшего
    for (int i = bytes * 8 - 1; i >= 0; --i) {
        // "Выталкиваем" все биты, кроме i-ого, так чтобы i-ый был последним и выводим этот бит
        if ((value >> i) & 1) {
            std::cout << 1;
        } else {
            std::cout << 0;
        }

        if (i != 0 && i % 4 == 0) {
            std::cout << "'";
        }
    }
    std::cout << '\n';
}