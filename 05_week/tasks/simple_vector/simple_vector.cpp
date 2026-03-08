#include <algorithm>
#include <initializer_list>
#include <tuple>


class SimpleVector {
public:
    // Конструкторы и деструктор
    SimpleVector();
    SimpleVector(size_t size, int el = 0);
    SimpleVector(std::initializer_list<int> init_list);
    SimpleVector(const SimpleVector& other);
    SimpleVector(SimpleVector&& other) noexcept;
    ~SimpleVector();

    // Операторы
    SimpleVector& operator=(const SimpleVector& other);
    SimpleVector& operator=(SimpleVector&& other) noexcept;
    int& operator[](size_t pos) noexcept;
    const int& operator[](size_t pos) const noexcept;
    bool operator==(const SimpleVector& other) const noexcept;
    bool operator!=(const SimpleVector& other) const noexcept;

    // Методы
    void Swap(SimpleVector& other) noexcept;
    size_t Size() const noexcept;
    size_t Capacity() const noexcept;
    bool Empty() const noexcept;
    const int* Data() const noexcept;
    void PushBack(int el);
    void PopBack() noexcept;
    int* Insert(size_t pos, int el);
    int* Insert(const int* pos_ptr, int el);
    int* Erase(size_t pos);
    int* Erase(const int* pos_ptr);
    void Clear() noexcept;
    void Resize(size_t size, int el = 0);
    void Reserve(size_t new_capacity);
    int* Begin() noexcept;
    int* End() noexcept;
    const int* Begin() const noexcept;
    const int* End() const noexcept;

private:
    int* data_;
    size_t size_;
    size_t capacity_;

    // Вспомогательные методы
    void Realloc(size_t new_capacity);
};

// Вспомогательные методы
void SimpleVector::Realloc(size_t new_capacity) {
    int* new_data = new int[new_capacity];
    std::copy(data_, data_ + size_, new_data);

    delete[] std::exchange(data_, new_data);
    capacity_ = new_capacity;
}

// Конструкторы и деструктор
SimpleVector::SimpleVector() : data_(nullptr), size_(0), capacity_(0) {}

SimpleVector::SimpleVector(size_t size, int el) : data_(new int[10]), size_(size), capacity_(size) {
    std::fill(data_, data_ + size, el);
}

SimpleVector::SimpleVector(std::initializer_list<int> init_list) : data_(new int[init_list.size()]), size_(init_list.size()), capacity_(init_list.size()) {
    std::copy(init_list.begin(), init_list.end(), data_);
}

SimpleVector::SimpleVector(const SimpleVector& other) : data_(new int[other.size_]), size_(other.size_), capacity_(other.size_) {
    std::copy(other.data_, other.data_ + other.size_, data_);
}

SimpleVector::SimpleVector(SimpleVector&& other) noexcept : data_(other.data_), size_(other.size_), capacity_(other.capacity_) {
    other.data_ = nullptr;
    other.size_ = 0;
    other.capacity_ = 0;
}

SimpleVector::~SimpleVector() { delete[] data_; }

// Операторы
SimpleVector& SimpleVector::operator=(const SimpleVector& other) {
    if (this != &other) {
        delete[] std::exchange(data_, new int[other.size_]);
        std::copy(other.data_, other.data_ + other.size_, data_);
        size_ = other.size_;
        capacity_ = other.size_;
    }
    return *this;
}

SimpleVector& SimpleVector::operator=(SimpleVector&& other) noexcept {
    if (this != &other) {
        delete[] data_;
        std::tie(data_, size_, capacity_) = std::tie(other.data_, other.size_, other.capacity_);
        std::tie(other.data_, other.size_, other.capacity_) = std::make_tuple(nullptr, 0, 0);
    }
    return *this;
}

int& SimpleVector::operator[](size_t pos) noexcept { return data_[pos]; }

const int& SimpleVector::operator[](size_t pos) const noexcept { return data_[pos]; }

bool SimpleVector::operator==(const SimpleVector& other) const noexcept {
    if (size_ != other.size_) return false;

    for (size_t i = 0; i < size_; ++i) {
        if (data_[i] != other.data_[i]) return false;
    }
    return true;
}

bool SimpleVector::operator!=(const SimpleVector& other) const noexcept {
    return !operator==(other);
}

// Методы
void SimpleVector::Swap(SimpleVector& other) noexcept {
    std::swap(data_, other.data_);
    std::swap(size_, other.size_);
    std::swap(capacity_, other.capacity_);
}

size_t SimpleVector::Size() const noexcept {
    return size_;
}

size_t SimpleVector::Capacity() const noexcept {
    return capacity_;
}

bool SimpleVector::Empty() const noexcept {
    return (size_ == 0);
}

const int* SimpleVector::Data() const noexcept {
    return data_;
}

void SimpleVector::PushBack(int el) {
    if (size_ == capacity_) {
        size_t new_capacity = (capacity_ == 0) ? 1 : capacity_ * 2;
        Realloc(new_capacity);
    }
    data_[size_++] = el;
}

void SimpleVector::PopBack() noexcept {
    if (size_ > 0) { --size_; }
}

int* SimpleVector::Insert(size_t pos, int el) {
    if (pos <= size_) {
        if (size_ == capacity_) {
            size_t new_capacity = (capacity_ == 0) ? 1 : capacity_ * 2;
            Realloc(new_capacity);
        }
        for (size_t i = size_; i > pos; --i) {
            data_[i] = data_[i - 1];
        }
        ++size_;
        data_[pos] = el;
        return &data_[pos];
    }
    return End();
}

int* SimpleVector::Insert(const int* pos_ptr, int el) {
    size_t pos = static_cast<size_t>(pos_ptr - data_);
    return Insert(pos, el);
}

int* SimpleVector::Erase(size_t pos) {
    if (pos < size_) {
        for (size_t i = pos + 1; i < size_; ++i) {
            data_[i - 1] = data_[i];
        }
        --size_;
        return &data_[pos];
    }
    return End();
}   

int* SimpleVector::Erase(const int* pos_ptr) {
    size_t pos = static_cast<size_t>(pos_ptr - data_);
    return Erase(pos);
}

void SimpleVector::Clear() noexcept {
    size_ = 0;
}

void SimpleVector::Resize(size_t size, int el) {
    if (size == size_) {
        return;
    } else if (size > size_) {
        for (size_t i = size_; i < size; ++i) {
            PushBack(el);
        }
    } else if (size < size_) {
        size_ = size;
    } 
}

void SimpleVector::Reserve(size_t new_capacity) {
    if (capacity_ >= new_capacity) return;
    Realloc(new_capacity);
}

int* SimpleVector::Begin() noexcept {
    return data_;
}

int* SimpleVector::End() noexcept {
    return data_ + size_;
}

const int* SimpleVector::Begin() const noexcept {
    return data_;
}

const int* SimpleVector::End() const noexcept {
    return data_ + size_;
}

// Внешние функции для совместимости с STL
int* begin(SimpleVector& vec) noexcept {
    return vec.Begin();
}

int* end(SimpleVector& vec) noexcept {
    return vec.End();
}

const int* begin(const SimpleVector& vec) noexcept {
    return vec.Begin();
}

const int* end(const SimpleVector& vec) noexcept {
    return vec.End();
}

void swap(SimpleVector& lhs, SimpleVector& rhs) noexcept {
    lhs.Swap(rhs);
}