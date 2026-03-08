#include <algorithm>
#include <initializer_list>
#include <utility>


template<typename T, size_t N>
class Array {
public:
    // Конструкторы и деструктор
    Array() {}
    Array(std::initializer_list<T> init_list) {
        std::copy(init_list.begin(), init_list.end(), data_);
    }
    Array(const Array& other) {
        std::copy(std::begin(other.data_), std::end(other.data_), data_);
    }
    Array(Array&& other) {
        std::move(std::begin(other.data_), std::end(other.data_), data_);
    }
    ~Array() {}

    // Операторы
    Array& operator=(const Array& other) {
        if (this != &other) {
            std::copy(std::begin(other.data_), std::end(other.data_), data_);
        }
        return *this;
    }
    Array& operator=(Array&& other) {
        if (this != &other) {
            std::move(std::begin(other.data_), std::end(other.data_), data_);
        }
        return *this;
    }
    T& operator[](size_t pos) noexcept {
        return data_[pos];
    }
    const T& operator[](size_t pos) const noexcept {
        return data_[pos];
    }

    // Методы
    T& Front() noexcept {
        return data_[0];
    }
    T& Back() noexcept {
        return data_[N - 1];
    }
    const T& Front() const noexcept {
        return data_[0];
    }
    const T& Back() const noexcept {
        return data_[N - 1];
    }
    T* Data() noexcept {
        return data_;
    }
    const T* Data() const noexcept {
        return data_;
    }
    static constexpr size_t Size() noexcept {
        return N;
    }
    static constexpr size_t Capacity() noexcept {
        return N;
    }
    static constexpr bool Empty() noexcept {
        return N == 0;
    }
    void Fill(const T& value) {
        std::fill(std::begin(data_), std::end(data_), value);
    }
    void Swap(Array& other) {
        std::swap_ranges(std::begin(data_), std::end(data_), std::begin(other.data_));
    }
    T* begin() noexcept {
        return data_;
    }
    T* end() noexcept {
        return data_ + N;
    }
    const T* cbegin() const noexcept {
        return data_;
    }
    const T* cend() const noexcept {
        return data_ + N;
    }
    const T* Cbegin() const noexcept {
        return data_;
    }
    const T* Cend() const noexcept {
        return data_ + N;
    }

private:
    T data_[N];
};

// Операторы сравнения на равенство и неравенство
template<typename T, size_t N>
bool operator==(const Array<T, N>& lhs, const Array<T, N>& rhs) {
    return std::equal(lhs.Cbegin(), lhs.Cend(), rhs.Cbegin());
}

template<typename T, size_t N>
bool operator!=(const Array<T, N>& lhs, const Array<T, N>& rhs) {
    return !(lhs == rhs);
}

// Лексикографическое сравнение
template<typename T, size_t N>
bool operator<(const Array<T, N>& lhs, const Array<T, N>& rhs) {
    return std::lexicographical_compare(lhs.Cbegin(), lhs.Cend(), rhs.Cbegin(), rhs.Cend());
}

template<typename T, size_t N>
bool operator>(const Array<T, N>& lhs, const Array<T, N>& rhs) {
    return rhs < lhs;
}

template<typename T, size_t N>
bool operator<=(const Array<T, N>& lhs, const Array<T, N>& rhs) {
    return !(rhs < lhs);
}

template<typename T, size_t N>
bool operator>=(const Array<T, N>& lhs, const Array<T, N>& rhs) {
    return !(lhs < rhs);
}

template<typename T, size_t N>
void swap(Array<T, N>& lhs, Array<T, N>& rhs) {
    lhs.Swap(rhs);
}

template<size_t I, typename T, size_t N>
T& get(Array<T, N>& arr) noexcept {
    return arr[I];
}

template<size_t I, typename T, size_t N>
const T& get(const Array<T, N>& arr) noexcept {
    return arr[I];
}

template<size_t I, typename T, size_t N>
T&& get(Array<T, N>&& arr) noexcept {
    return std::move(arr[I]);
}