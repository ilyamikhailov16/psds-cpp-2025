#include <cstring>
#include <string>


class StringView {
public:
    // Константа
    static constexpr size_t npos = static_cast<size_t>(-1);
    
    // Конструкторы
    StringView() noexcept;
    StringView(const std::string& str, size_t begin_pos = 0, size_t length = npos);
    StringView(const char* str) noexcept;
    StringView(const char* str, size_t length) noexcept;

    // Методы 
    const char& operator[](size_t pos) const noexcept;
    const char* Data() const noexcept;
    const char& Front() const noexcept;
    const char& Back() const noexcept;

    size_t Size() const noexcept;
    size_t Length() const noexcept;
    bool Empty() const noexcept;
    
    void RemovePrefix(size_t prefix_length) noexcept;
    void RemoveSuffix(size_t suffix_length) noexcept;
    StringView Substr(size_t begin_pos, size_t length = npos) const noexcept;
    size_t Find(char ch, size_t begin_pos = 0) const noexcept;
    size_t Find(const StringView& str, size_t begin_pos = 0) const noexcept;
    std::string ToString() const;  // std::string — аллокация, не noexcept

private:
    const char* ptr_begin_; 
    size_t length_;
};

// Конструкторы
StringView::StringView() noexcept : ptr_begin_(nullptr), length_(0) {}

StringView::StringView(const std::string& str, size_t begin_pos, size_t length)
    : ptr_begin_((begin_pos >= str.length()) ? nullptr : &str[begin_pos]), 
        length_((begin_pos >= str.length()) ? 0 : 
        (length > str.length() - begin_pos) ? str.length() - begin_pos : length) {}

StringView::StringView(const char* str) noexcept : ptr_begin_(str), length_((!str) ? 0 : strlen(str)) {}

StringView::StringView(const char* str, size_t length) noexcept
    : ptr_begin_(str), length_((!str) ? 0 : 
        (length > strlen(str)) ? strlen(str) : length) {}

// Методы 
const char& StringView::operator[](size_t pos) const noexcept {
    return ptr_begin_[pos];
}

const char* StringView::Data() const noexcept {
    return ptr_begin_;
}

const char& StringView::Front() const noexcept {
    return *ptr_begin_;
}

const char& StringView::Back() const noexcept {
    return *(ptr_begin_ + length_ - 1);
}

size_t StringView::Size() const noexcept {
    return length_;
}

size_t StringView::Length() const noexcept {
    return length_;
}

bool StringView::Empty() const noexcept {
    return (length_ == 0);
}

void StringView::RemovePrefix(size_t prefix_length) noexcept {
    if (prefix_length >= length_) {
        length_ = 0;
    } else {
        ptr_begin_ += prefix_length;
        length_ -= prefix_length;   
    }
}

void StringView::RemoveSuffix(size_t suffix_length) noexcept {
    if (suffix_length >= length_) {
        length_ = 0;
    } else {
        length_ -= suffix_length;
    }
}

StringView StringView::Substr(size_t begin_pos, size_t length) const noexcept {
    if (begin_pos >= length_) {
        return StringView();
    }
    if (length == npos) {
        length = length_ - begin_pos;
    }
    return StringView(ptr_begin_ + begin_pos, length);
}

size_t StringView::Find(char ch, size_t begin_pos) const noexcept {
    if (begin_pos >= length_) {
        return npos;
    }
    for (size_t i = begin_pos; i < length_; ++i) {
        if (ptr_begin_[i] == ch) {
            return i;
        }
    }
    return npos;
}

size_t StringView::Find(const StringView& str, size_t begin_pos) const noexcept {
    if (str.Empty()) {
        return 0;
    }
    if (length_ == 0 || begin_pos >= length_ || str.Length() > length_ - begin_pos) {
        return npos;
    }
    for (size_t i = begin_pos; i <= length_ - str.Length(); ++i) {
        bool found = true;
        for (size_t j = 0; j < str.Length(); ++j) {
            if (ptr_begin_[i + j] != str[j]) {
                found = false;
                break;
            }
        }
        if (found) {
            return i;
        }
    }
    return npos;
}

std::string StringView::ToString() const {
    return std::string(ptr_begin_, length_);
}