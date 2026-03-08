#include <cstring>
#include <string>


struct CowStringData
{
    size_t str_length;
    unsigned int ref_count;
    char str_data[1]; 
};

class CowString {
public:
    // Константа
    static constexpr size_t npos = static_cast<size_t>(-1);

    // Конструкторы и деструктор
    CowString();
    CowString(const char* str);
    CowString(const std::string& str);
    CowString(const CowString& other) noexcept;
    CowString(CowString&& other);
    ~CowString();

    // Операторы присваивания
    CowString& operator=(const CowString& other) noexcept;
    CowString& operator=(CowString&& other);

    // Методы НЕ вызывающие копирования
    size_t Size() const noexcept;
    const char* ToCstr() const noexcept;
    std::string ToString() const;
    const char& operator[](size_t pos) const noexcept;
    operator const char*() const noexcept;
    bool Empty() const noexcept;  
    size_t Find(const char* str) const noexcept;  
    size_t Find(char ch) const noexcept;
    CowString Substr(size_t begin_pos = 0, size_t length = npos) const;

    // Методы, обеспечивающие модификацию на собственной копии данных
    char& operator[](size_t pos) noexcept;
    CowString& Append(const char* str);
    CowString& Append(const std::string& str);
    void Clear();

private:
    CowStringData* data_;

    // Статические методы
    static CowStringData* CreateCowStringData(size_t length);
    static CowStringData* CreateCopy(CowStringData* data);
};

// Статические методы
CowStringData* CowString::CreateCowStringData(size_t length) {
    size_t total_size = sizeof(CowStringData) + length;
    CowStringData* data = reinterpret_cast<CowStringData*>(new char[total_size]);
    data->str_length = length;
    data->ref_count = 1;
    if (length == 0) { data->str_data[0] = '\0'; }
    return data;
}

CowStringData* CowString::CreateCopy(CowStringData* data) {
    if (data->ref_count > 1) { 
        --data->ref_count;
        CowStringData* new_data = CreateCowStringData(data->str_length);
        std::memcpy(new_data->str_data, data->str_data, data->str_length + 1);
        return new_data;
    }
    return data;
}

// Конструкторы и деструктор
CowString::CowString() : data_(CreateCowStringData(0)) {}

CowString::CowString(const char* str) : data_(CreateCowStringData(str ? strlen(str) : 0)) {
    if (str) {
        std::strcpy(data_->str_data, str);
    }
}

CowString::CowString(const std::string& str) : CowString(str.c_str()) {}

CowString::CowString(const CowString& other) noexcept : data_(other.data_) {
    ++data_->ref_count;
}

CowString::CowString(CowString&& other) : data_(other.data_) {
    other.data_ = CreateCowStringData(0);
}

CowString::~CowString() {
    if (--data_->ref_count == 0) {
        delete[] data_;
    }
}

// Операторы присваивания
CowString& CowString::operator=(const CowString& other) noexcept {
    if (this != &other) {
        if (--data_->ref_count == 0) {
            delete[] data_;
        }
        data_ = other.data_;
        ++data_->ref_count;
    }
    return *this;
}

CowString& CowString::operator=(CowString&& other) {
    if (this != &other) {
        if (--data_->ref_count == 0) {
            delete[] data_;
        }
        data_ = other.data_;
        other.data_ = CreateCowStringData(0);
    }
    return *this;
}

// Методы НЕ вызывающие копирования
size_t CowString::Size() const noexcept {
    return data_->str_length;
}

const char* CowString::ToCstr() const noexcept {
    return data_->str_data;
}

std::string CowString::ToString() const {
    return std::string(data_->str_data, data_->str_length);
}

const char& CowString::operator[](size_t pos) const noexcept {
    return data_->str_data[pos];
}

CowString::operator const char*() const noexcept {
    return data_->str_data;
}

bool CowString::Empty() const noexcept {
    return (data_->str_length == 0);
}  

size_t CowString::Find(const char* str) const noexcept {
    if (!str) return 0;

    if (data_->str_length == 0) {
        return npos;
    }
    for (size_t i = 0; i <= data_->str_length - strlen(str) ; ++i) {
        bool found = true;
        for (size_t j = 0; j < strlen(str); ++j) {
            if (data_->str_data[i + j] != str[j]) {
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

size_t CowString::Find(char ch) const noexcept {
    for (size_t i = 0; i < data_->str_length; ++i) {
        if (data_->str_data[i] == ch) {
            return i;
        }
    }
    return npos;
}

CowString CowString::Substr(size_t begin_pos, size_t length) const {
    if (begin_pos >= data_->str_length) {
        return CowString();
    }
    size_t available_len = data_->str_length - begin_pos;
    size_t actual_len = std::min(length, available_len);
    return CowString(std::string(data_->str_data + begin_pos, actual_len));
}

// Методы, обеспечивающие модификацию на собственной копии данных
char& CowString::operator[](size_t pos) noexcept {
    data_ = CreateCopy(data_); 
    return data_->str_data[pos];
}

CowString& CowString::Append(const char* str) {
    if (!str || *str == '\0') return *this;

    size_t append_len = std::strlen(str);
    size_t new_len = data_->str_length + append_len;
    CowStringData* new_data = CreateCowStringData(new_len);
    // Копируем старое содержимое
    std::memcpy(new_data->str_data, data_->str_data, data_->str_length);
    // Копируем новое содержимое
    std::memcpy(new_data->str_data + data_->str_length, str, append_len + 1);
    // Освобождаем старый блок
    if (--data_->ref_count == 0) {
        delete[] data_;
    }
    data_ = new_data;
    return *this;
}

CowString& CowString::Append(const std::string& str) {
    return Append(str.c_str());
}

void CowString::Clear() {
    if (data_->str_length == 0) return; // Уже пустая
    
    if (--data_->ref_count == 0) {
        delete[] data_;
    }
    data_ = CreateCowStringData(0);
}

