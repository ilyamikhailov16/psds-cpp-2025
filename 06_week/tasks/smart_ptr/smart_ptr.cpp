#include <string>


struct ControlBlock
{
    unsigned int strong_count = 0;
    unsigned int weak_count = 0;
};

class SharedPtr {
public:
    // Конструкторы и деструктор
    explicit SharedPtr(std::string* data = nullptr);
    SharedPtr(std::string* data, ControlBlock* cb);
    SharedPtr(const SharedPtr& other);
    SharedPtr(SharedPtr&& other) noexcept;
    ~SharedPtr();

    // Операторы
    SharedPtr& operator=(const SharedPtr& other);
    SharedPtr& operator=(SharedPtr&& other) noexcept;
    explicit operator bool() const noexcept;
    std::string& operator*() const noexcept;
    std::string* operator->() const noexcept;

    // Методы
    std::string* Get() noexcept;
    const std::string* Get() const noexcept;
    void Reset(std::string* data = nullptr);
    void Swap(SharedPtr& other) noexcept;
    unsigned int UseCount() const noexcept;

    // Дружественные функции
    friend ControlBlock* GetControlBlock(const SharedPtr& obj) noexcept;

private:
    std::string* data_;
    ControlBlock* cb_;

    // Приватные методы
    void DeleteData() noexcept;
};

class WeakPtr {
public:
    // Конструкторы и деструктор
    WeakPtr() noexcept;
    WeakPtr(const SharedPtr& other) noexcept;
    WeakPtr(const WeakPtr& other) noexcept;
    WeakPtr(WeakPtr&& other) noexcept;
    ~WeakPtr();

    // Операторы
    WeakPtr& operator=(const SharedPtr& other) noexcept;
    WeakPtr& operator=(const WeakPtr& other) noexcept;
    WeakPtr& operator=(WeakPtr&& other) noexcept;
    const std::string& operator*() const noexcept;
    const std::string* operator->() const noexcept;

    // Методы
    const std::string* Get() const noexcept;
    void Reset() noexcept;
    void Swap(WeakPtr& other) noexcept;
    unsigned int UseCount() const noexcept;
    bool Expired() const noexcept;
    SharedPtr Lock() const;

    // Дружественные функции
    friend ControlBlock* GetControlBlock(const WeakPtr& obj) noexcept;

private:
    const std::string* data_;
    ControlBlock* cb_;

    // Приватные методы
    void DeleteData() noexcept;
};

// SharedPtr
// Приватные методы
void SharedPtr::DeleteData() noexcept {
    if (cb_) {
        if (--cb_->strong_count == 0) { 
            delete data_; 
            if (cb_->weak_count == 0) delete cb_;
        }
    }
}

// Конструкторы и деструктор
SharedPtr::SharedPtr(std::string* data) : data_(data), cb_((data) ? new ControlBlock() : nullptr) {
    if (cb_) ++cb_->strong_count;
}

SharedPtr::SharedPtr(std::string* data, ControlBlock* cb) : data_((data && cb) ? data : nullptr), cb_((data && cb) ? cb : nullptr) {
    if (data && cb) ++cb_->strong_count;
}

SharedPtr::SharedPtr(const SharedPtr& other) : data_(other.data_), cb_(other.cb_) {
    if (cb_) ++cb_->strong_count;
}

SharedPtr::SharedPtr(SharedPtr&& other) noexcept : data_(other.data_), cb_(other.cb_) {
    other.data_ = nullptr;
    other.cb_ = nullptr;
}

SharedPtr::~SharedPtr() {
    DeleteData();
}

// Операторы
SharedPtr& SharedPtr::operator=(const SharedPtr& other) {
    if (this != &other) {
        DeleteData();
        std::tie(data_, cb_) = std::tie(other.data_, other.cb_);
        if (cb_) ++cb_->strong_count;
    }
    return *this;
}

SharedPtr& SharedPtr::operator=(SharedPtr&& other) noexcept {
    if (this != &other) {
        DeleteData();
        std::tie(data_, cb_) = std::tie(other.data_, other.cb_);
        std::tie(other.data_, other.cb_) = std::make_tuple(nullptr, nullptr);
    }
    return *this;
}

SharedPtr::operator bool() const noexcept {
    return data_;
}

std::string& SharedPtr::operator*() const noexcept { return *data_; }

std::string* SharedPtr::operator->() const noexcept { return data_; }

// Методы
std::string* SharedPtr::Get() noexcept { return data_; }

const std::string* SharedPtr::Get() const noexcept { return data_; }

void SharedPtr::Reset(std::string* data) {
    if (data_ != data) {
        DeleteData();
        data_ = data;
        cb_ = (data) ? new ControlBlock() : nullptr;
        if (cb_) ++cb_->strong_count;
    }
}

void SharedPtr::Swap(SharedPtr& other) noexcept {
    std::swap(data_, other.data_);
    std::swap(cb_, other.cb_);
}

unsigned int SharedPtr::UseCount() const noexcept {
    return (cb_) ? cb_->strong_count : 0;
}

// WeakPtr
// Приватные методы
void WeakPtr::DeleteData() noexcept {
    if (cb_) {
        if (--cb_->weak_count == 0 && cb_->strong_count == 0) {
            delete cb_;
        }
    }
}

// Конструкторы и деструктор
WeakPtr::WeakPtr() noexcept : data_(nullptr), cb_(nullptr) {}

WeakPtr::WeakPtr(const SharedPtr& other) noexcept : data_(other.Get()), cb_(GetControlBlock(other)) {
    if (cb_) ++cb_->weak_count;
}

WeakPtr::WeakPtr(const WeakPtr& other) noexcept : data_(other.data_), cb_(other.cb_) {
    if (cb_) ++cb_->weak_count;
}

WeakPtr::WeakPtr(WeakPtr&& other) noexcept : data_(other.data_), cb_(other.cb_) {
    other.data_ = nullptr;
    other.cb_ = nullptr;
}

WeakPtr::~WeakPtr() {
    DeleteData();
}

// Операторы
WeakPtr& WeakPtr::operator=(const SharedPtr& other) noexcept {
    DeleteData();
    data_ = other.Get(); 
    cb_ = GetControlBlock(other);
    if (cb_) ++cb_->weak_count;
    return *this;
}

WeakPtr& WeakPtr::operator=(const WeakPtr& other) noexcept {
    if (this != &other) {
        DeleteData();
        std::tie(data_, cb_) = std::tie(other.data_, other.cb_);
        if (cb_) ++cb_->weak_count;
    }
    return *this;
}

WeakPtr& WeakPtr::operator=(WeakPtr&& other) noexcept {
    if (this != &other) {
        DeleteData();
        std::tie(data_, cb_) = std::tie(other.data_, other.cb_);
        std::tie(other.data_, other.cb_) = std::make_tuple(nullptr, nullptr);
    }
    return *this;
}

const std::string& WeakPtr::operator*() const noexcept {
    return *data_;
}

const std::string* WeakPtr::operator->() const noexcept {
    return data_;
}

// Методы
const std::string* WeakPtr::Get() const noexcept {
    return data_;
}

void WeakPtr::Reset() noexcept {
    DeleteData();
    data_ = nullptr;
    cb_ = nullptr;
}

void WeakPtr::Swap(WeakPtr& other) noexcept {
    std::swap(data_, other.data_);
    std::swap(cb_, other.cb_);
}

unsigned int WeakPtr::UseCount() const noexcept {
    return (cb_) ? cb_->strong_count : 0;
}

bool WeakPtr::Expired() const noexcept {
    return !cb_ || cb_->strong_count == 0;
}

SharedPtr WeakPtr::Lock() const {
    if (Expired()) {
        return SharedPtr();
    }
    return SharedPtr(const_cast<std::string*>(data_), cb_);
}

// Внешние функции
SharedPtr MakeShared(const std::string& str) {
    return SharedPtr(new std::string(str));
}

SharedPtr MakeShared(std::string&& str) {
    return SharedPtr(new std::string(std::move(str)));
}

void Swap(SharedPtr& ptr_1, SharedPtr& ptr_2) noexcept {
    ptr_1.Swap(ptr_2);
}

void Swap(WeakPtr& ptr_1, WeakPtr& ptr_2) noexcept {
    ptr_1.Swap(ptr_2);
}

// Дружественные функции
ControlBlock* GetControlBlock(const SharedPtr& obj) noexcept {
    return obj.cb_;
}

ControlBlock* GetControlBlock(const WeakPtr& obj) noexcept {
    return obj.cb_;
}
