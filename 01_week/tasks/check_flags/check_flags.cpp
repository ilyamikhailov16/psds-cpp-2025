#include <cstdint>
#include <iostream>
#include <vector>
#include <string>


enum class CheckFlags : uint8_t {
    NONE = 0,
    TIME = (1 << 0),
    DATE = (1 << 1),
    USER = (1 << 2),
    CERT = (1 << 3),
    KEYS = (1 << 4),
    DEST = (1 << 5),
    ALL = TIME | DATE | USER | CERT | KEYS | DEST
};

void PrintCheckFlags(CheckFlags flags) {
    if (flags == CheckFlags::NONE) {
        std::cout << "[]";
        return;
    }

    if ((static_cast<uint8_t>(flags) & ~static_cast<uint8_t>(CheckFlags::ALL)) != 0) {
        std::cout << "";
        return;
    }

    std::vector<std::string> set_flags;
    if ((static_cast<uint8_t>(flags) & static_cast<uint8_t>(CheckFlags::TIME)) != 0) {
        set_flags.push_back("TIME");
    }
    if ((static_cast<uint8_t>(flags) & static_cast<uint8_t>(CheckFlags::DATE)) != 0) {
        set_flags.push_back("DATE");
    }
    if ((static_cast<uint8_t>(flags) & static_cast<uint8_t>(CheckFlags::USER)) != 0) {
        set_flags.push_back("USER");
    }
    if ((static_cast<uint8_t>(flags) & static_cast<uint8_t>(CheckFlags::CERT)) != 0) {
        set_flags.push_back("CERT");
    }
    if ((static_cast<uint8_t>(flags) & static_cast<uint8_t>(CheckFlags::KEYS)) != 0) {
        set_flags.push_back("KEYS");
    }
    if ((static_cast<uint8_t>(flags) & static_cast<uint8_t>(CheckFlags::DEST)) != 0) {
        set_flags.push_back("DEST");
    }

    std::cout << "[";
    for (int i = 0; i < set_flags.size(); i++) {
        std::cout << set_flags[i];
        if (i < set_flags.size() - 1) {
            std::cout << ",";
        }
    }
    std::cout << "]";
}