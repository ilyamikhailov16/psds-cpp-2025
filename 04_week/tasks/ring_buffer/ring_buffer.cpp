#include <vector>
#include <iostream>


class RingBuffer {
    std::vector<int> buffer;
    size_t capacity = 0;
    size_t size = 0;

    
public: 
    size_t begin = 0;
    size_t end = 0;

    RingBuffer(size_t size);
    RingBuffer(size_t size, const int& value);
    RingBuffer(const std::initializer_list<int>& list);

    void Push(const int& value);
    bool TryPush(const int& value);

    void Pop();
    bool TryPop(int& value);
    
    int& operator[](const size_t& idx);
    const int& operator[](const size_t& idx) const;

    int& Front();
    const int& Front() const;

    int& Back();
    const int& Back() const;
    
    int Size() const;

    int Capacity() const;

    bool Empty() const;
 
    bool Full() const;

    void Clear();

    void Resize(size_t new_size);

    std::vector<int> Vector() const;
};


RingBuffer::RingBuffer(size_t size){
    if (size == 0){
        size = 1;
    }

    buffer.resize(size);
    capacity = size;
}

RingBuffer::RingBuffer(size_t size, const int& value){
    if (size == 0){
        size = 1;
    }
    
    buffer.resize(size, value);
    capacity = size;
    this->size = size;
    end = size-1;
}

RingBuffer::RingBuffer(const std::initializer_list<int>& list) : RingBuffer(list.size() > 0 ? list.size() : 1)
{
    if (list.size() > 0) {
        size = list.size();
        end = list.size() - 1;
        begin = 0;
        buffer = list;
    }
}

bool RingBuffer::TryPush(const int& value) {
    if (Full()) return false;
    
    if (!Empty()) {
        end = (end + 1) % capacity;
    }
    buffer[end] = value;
    ++size;
    return true;
}

void RingBuffer::Push(const int& value) {
    if (Full()) {
        Pop();
    }
    TryPush(value);
}

bool RingBuffer::TryPop(int& value) {
    if (Empty()) return false;
    value = buffer[begin];
    begin = (begin + 1) % capacity;
    --size;
    return true;
}

void RingBuffer::Pop() {
    int trash;
    TryPop(trash);
}

int& RingBuffer::operator[](const size_t& idx) {
    return buffer[(begin + idx) % capacity];
}

const int& RingBuffer::operator[](const size_t& idx) const {
    return buffer[(begin + idx) % capacity];
}

int& RingBuffer::Front() { return buffer[end]; }
const int& RingBuffer::Front() const { return buffer[end]; }

int& RingBuffer::Back() { return buffer[begin]; }
const int& RingBuffer::Back() const { return buffer[begin]; }

int RingBuffer::Size() const { return size; }

int RingBuffer::Capacity() const { return capacity; }

bool RingBuffer::Empty() const { return size == 0; }

bool RingBuffer::Full() const { return size == capacity; }

void RingBuffer::Clear() {
    end = 0;
    begin = 0;
    size = 0;
}

void RingBuffer::Resize(size_t new_size) {
    if (new_size == capacity) {
        return;
    }

    if (new_size == 0){
        new_size = 1;
    }

    std::vector<int> new_buffer(new_size);
    size_t new_current_size;

    if (new_size >= size){
        for (size_t i = 0; i < size; ++i) {
            new_buffer[i] = buffer[i];
            new_current_size = size;
        }
    } else {
        size_t j = (begin + (size - new_size)) % capacity;
        for (size_t i = 0; i < new_size; ++i) {
            new_buffer[i] = buffer[j];
            new_current_size = new_size;

            if (j + 1 < capacity){
                ++j;
            } else {
                j = 0;
            }
        }
    }

    buffer = std::move(new_buffer);
    capacity = new_size;
    size = new_current_size;
    begin = 0;
    end = (size == 0) ? 0 : size - 1;
}

std::vector<int> RingBuffer::Vector() const {
    std::vector<int> result_vector;
    result_vector.reserve(size);
    for (size_t i = 0; i < size; ++i) {
        result_vector.push_back(buffer[(begin + i) % capacity]);
    }
    return result_vector;
}