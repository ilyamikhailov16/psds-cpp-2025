#include <cstdint>
#include <vector>
#include <iostream>
#include <string>
#include <sstream>

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

CheckFlags operator|(CheckFlags a, CheckFlags b) {
    uint8_t a_val = static_cast<uint8_t>(a);
    uint8_t b_val = static_cast<uint8_t>(b);
    uint8_t result = a_val | b_val;
    
    uint8_t valid_result = result & static_cast<uint8_t>(CheckFlags::ALL);
    return static_cast<CheckFlags>(valid_result);
}

bool operator&(CheckFlags a, CheckFlags b) {
    uint8_t a_val = static_cast<uint8_t>(a);
    uint8_t b_val = static_cast<uint8_t>(b);
    
    uint8_t a_valid = a_val & static_cast<uint8_t>(CheckFlags::ALL);
    uint8_t b_valid = b_val & static_cast<uint8_t>(CheckFlags::ALL);
    
    if (a_valid == 0 || b_valid == 0) {
        return false;
    }
    
    return (a_valid & b_valid) == a_valid || (a_valid & b_valid) == b_valid;
}

CheckFlags operator^(CheckFlags a, CheckFlags b) {
    uint8_t a_val = static_cast<uint8_t>(a);
    uint8_t b_val = static_cast<uint8_t>(b);
    
    uint8_t a_valid = a_val & static_cast<uint8_t>(CheckFlags::ALL);
    uint8_t b_valid = b_val & static_cast<uint8_t>(CheckFlags::ALL);
    
    uint8_t result = a_valid ^ b_valid;
    return static_cast<CheckFlags>(result);
}

CheckFlags operator~(CheckFlags a) {
    uint8_t a_val = static_cast<uint8_t>(a);
    uint8_t a_valid = a_val & static_cast<uint8_t>(CheckFlags::ALL);
    
    uint8_t result = ~a_valid & static_cast<uint8_t>(CheckFlags::ALL);
    
    return static_cast<CheckFlags>(result);
}

std::ostream& operator<<(std::ostream& os, CheckFlags flags) {
    uint8_t flags_val = static_cast<uint8_t>(flags);
    
    uint8_t valid_flags = flags_val & static_cast<uint8_t>(CheckFlags::ALL);
    
    if (valid_flags == 0) {
        os << "NONE";
        return os;
    }

    std::vector<std::string> flag_names;
    
    if ((valid_flags & static_cast<uint8_t>(CheckFlags::TIME)) != 0) {
        flag_names.push_back("TIME");
    }
    if ((valid_flags & static_cast<uint8_t>(CheckFlags::DATE)) != 0) {
        flag_names.push_back("DATE");
    }
    if ((valid_flags & static_cast<uint8_t>(CheckFlags::USER)) != 0) {
        flag_names.push_back("USER");
    }
    if ((valid_flags & static_cast<uint8_t>(CheckFlags::CERT)) != 0) {
        flag_names.push_back("CERT");
    }
    if ((valid_flags & static_cast<uint8_t>(CheckFlags::KEYS)) != 0) {
        flag_names.push_back("KEYS");
    }
    if ((valid_flags & static_cast<uint8_t>(CheckFlags::DEST)) != 0) {
        flag_names.push_back("DEST");
    }
    
    for (size_t i = 0; i < flag_names.size(); ++i) {
        os << flag_names[i];
        if (i < flag_names.size() - 1) {
            os << ", ";
        }
    }
    
    return os;
}