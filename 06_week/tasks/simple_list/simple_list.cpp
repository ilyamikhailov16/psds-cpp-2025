#include <string>
#include <utility>


struct Node {
    std::string data;
    Node* prev;
    Node* next;
};

class SimpleList {
public:
    // Конструктор и Деструкторы
    SimpleList();
    SimpleList(const SimpleList& other);
    SimpleList(SimpleList&& other) noexcept;
    ~SimpleList();

    // Операторы
    SimpleList& operator=(const SimpleList& other);
    SimpleList& operator=(SimpleList&& other) noexcept;

    // Методы 
    void Swap(SimpleList& other) noexcept;
    size_t Size() const noexcept;
    bool Empty() const noexcept;
    void PushBack(const std::string& value);
    void PushFront(const std::string& value);
    void PushBack(std::string&& value);
    void PushFront(std::string&& value);
    void PopBack() noexcept;
    void PopFront() noexcept;
    std::string& Back() noexcept;
    std::string& Front() noexcept;
    const std::string& Front() const noexcept;
    const std::string& Back() const noexcept;
    void Clear() noexcept;

private:
    Node* head_;
    Node* tail_;
    size_t size_;

    // Приватные методы
    void Unlink(Node* ptr_node) noexcept;
    void FrontLink(Node* ptr_new_node, Node* ptr_node) noexcept;
    void BackLink(Node* ptr_new_node, Node* ptr_node) noexcept;
    void CopyList(const SimpleList& other);
    void CreateFirstNode(Node* ptr_new_node) noexcept;
};

// Приватные методы
void SimpleList::CreateFirstNode(Node* ptr_new_node) noexcept {
    head_ = ptr_new_node;
    tail_ = ptr_new_node;
    ++size_;
}

void SimpleList::Unlink(Node* ptr_node) noexcept {
    if (!ptr_node) return;
    
    if (head_ == ptr_node && tail_ == ptr_node) {
        head_ = nullptr;
        tail_ = nullptr;
        delete ptr_node;
    } else if (head_ == ptr_node) {
        delete std::exchange(head_, head_->next);
        head_->prev = nullptr;
    } else if (tail_ == ptr_node) {
        delete std::exchange(tail_, tail_->prev);
        tail_->next = nullptr;
    } else {
        ptr_node->next->prev = ptr_node->prev;
        ptr_node->prev->next = ptr_node->next;
        delete ptr_node;
    }
    --size_;
}

void SimpleList::FrontLink(Node* ptr_new_node, Node* ptr_node) noexcept {
    if (!ptr_new_node) return;

    if (!ptr_node) {
        if (!head_) CreateFirstNode(ptr_new_node); 
        return;
    }

    if (ptr_node->next) { 
        ptr_node->next->prev = ptr_new_node;
        ptr_new_node->next = ptr_node->next; 
    }
    ptr_node->next = ptr_new_node;
    ptr_new_node->prev = ptr_node;

    if (tail_ == ptr_node) { tail_ = ptr_new_node; }
    ++size_;
}

void SimpleList::BackLink(Node* ptr_new_node, Node* ptr_node) noexcept {
    if (!ptr_new_node) return;

    if (!ptr_node) {
        if (!head_) CreateFirstNode(ptr_new_node); 
        return;
    }

    if (ptr_node->prev) { 
        ptr_node->prev->next = ptr_new_node; 
        ptr_new_node->prev = ptr_node->prev;
    }
    ptr_node->prev = ptr_new_node;
    ptr_new_node->next = ptr_node;

    if (head_ == ptr_node) { head_ = ptr_new_node; }
    ++size_;
}

void SimpleList::CopyList(const SimpleList& other) {
    Node* current = other.head_;
    while (current) {
        PushBack(current->data);
        current = current->next;
    }
}

// Конструктор и Деструкторы
SimpleList::SimpleList() : head_(nullptr), tail_(nullptr), size_(0) {}

SimpleList::SimpleList(const SimpleList& other) : SimpleList() {
    CopyList(other);
}

SimpleList::SimpleList(SimpleList&& other) noexcept {
    std::tie(head_, tail_, size_) = std::tie(other.head_, other.tail_, other.size_);
    std::tie(other.head_, other.tail_, other.size_) = std::make_tuple(nullptr, nullptr, 0);
}

SimpleList::~SimpleList(){
    Clear();
}

// Операторы
SimpleList& SimpleList::operator=(const SimpleList& other) {
    if (this != &other) {
        Clear();
        CopyList(other);
    }
    return *this;
}

SimpleList& SimpleList::operator=(SimpleList&& other) noexcept {
    if (this != &other) {
        Clear();
        std::tie(head_, tail_, size_) = std::tie(other.head_, other.tail_, other.size_);
        std::tie(other.head_, other.tail_, other.size_) = std::make_tuple(nullptr, nullptr, 0);
    }
    return *this;
}

// Методы 
void SimpleList::Swap(SimpleList& other) noexcept {
    std::swap(head_, other.head_);
    std::swap(tail_, other.tail_);
    std::swap(size_, other.size_);
}

size_t SimpleList::Size() const noexcept {
    return size_;
}

bool SimpleList::Empty() const noexcept {
    return (size_ == 0);
}

void SimpleList::PushBack(const std::string& value) {
    Node* ptr_new_node = new Node{value, nullptr, nullptr};
    FrontLink(ptr_new_node, tail_);
}

void SimpleList::PushFront(const std::string& value) {
    Node* ptr_new_node = new Node{value, nullptr, nullptr};
    BackLink(ptr_new_node, head_);
}

void SimpleList::PushBack(std::string&& value) {
    Node* ptr_new_node = new Node{std::move(value), nullptr, nullptr};
    FrontLink(ptr_new_node, tail_);
}

void SimpleList::PushFront(std::string&& value) {
    Node* ptr_new_node = new Node{std::move(value), nullptr, nullptr};
    BackLink(ptr_new_node, head_);
}

void SimpleList::PopBack() noexcept {
    Unlink(tail_);
}

void SimpleList::PopFront() noexcept {
    Unlink(head_);
}

std::string& SimpleList::Back() noexcept {
    return tail_->data;
}

std::string& SimpleList::Front() noexcept {
    return head_->data;
}

const std::string& SimpleList::Back() const noexcept {
    return tail_->data;
}

const std::string& SimpleList::Front() const noexcept {
    return head_->data;
}

void SimpleList::Clear() noexcept {
    Node* current = head_;
    while (current) {
        delete std::exchange(current, current->next);
    }
    std::tie(head_, tail_, size_) = std::make_tuple(nullptr, nullptr, 0);
}

// Внешние функции
void Swap(SimpleList& lhs, SimpleList& rhs) noexcept {
    lhs.Swap(rhs);
}