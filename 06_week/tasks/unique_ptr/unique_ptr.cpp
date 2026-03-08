#include <string>


class UniquePtr {
public:
    // Запрещённые конструкторы и операторы
    UniquePtr(const UniquePtr&) = delete;
    UniquePtr& operator=(const UniquePtr&) = delete;

    // Конструкторы и деструктор
    explicit UniquePtr(std::string* ptr = nullptr) noexcept;
    UniquePtr(UniquePtr&& other) noexcept;
    ~UniquePtr();

    // Операторы 
    UniquePtr& operator=(UniquePtr&& other) noexcept;
    explicit operator bool() const noexcept;
    std::string& operator*() const noexcept;
    std::string* operator->() const noexcept;

    // Методы 
    std::string* Get() noexcept;
    const std::string* Get() const noexcept;
    std::string* Release() noexcept;
    void Reset(std::string* ptr = nullptr) noexcept;
    void Swap(UniquePtr& other) noexcept;

private:
    std::string* ptr_;
};

// Конструкторы и деструктор
UniquePtr::UniquePtr(std::string* ptr) noexcept : ptr_(ptr) {}

UniquePtr::UniquePtr(UniquePtr&& other) noexcept : ptr_(other.ptr_) {
    other.ptr_ = nullptr;
}

UniquePtr::~UniquePtr() { delete ptr_; }

// Операторы 
UniquePtr& UniquePtr::operator=(UniquePtr&& other) noexcept {
    if (this != &other) {
        delete std::exchange(ptr_, other.ptr_);
        other.ptr_ = nullptr;
    }
    return *this;
}

UniquePtr::operator bool() const noexcept {
    return ptr_ != nullptr;
}

std::string& UniquePtr::operator*() const noexcept { return *ptr_; }

std::string* UniquePtr::operator->() const noexcept { return ptr_; }

// Методы 
std::string* UniquePtr::Get() noexcept { return ptr_; }

const std::string* UniquePtr::Get() const noexcept { return ptr_; }

std::string* UniquePtr::Release() noexcept {
    return std::exchange(ptr_, nullptr);
}

void UniquePtr::Reset(std::string* ptr) noexcept {
    if (ptr_ != ptr) {
        delete std::exchange(ptr_, ptr);
    }
}

void UniquePtr::Swap(UniquePtr& other) noexcept {
    std::swap(ptr_, other.ptr_);
}

// Внешние функции
UniquePtr MakeUnique(const std::string& str) {
    return UniquePtr(new std::string(str));
}

UniquePtr MakeUnique(std::string&& str) {
    return UniquePtr(new std::string(std::move(str)));
}

void Swap(UniquePtr& ptr_1, UniquePtr& ptr_2) noexcept {
    ptr_1.Swap(ptr_2);
}