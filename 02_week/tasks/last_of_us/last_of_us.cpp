#include <cstddef>

using funcPtr = bool (*)(int);

const int* FindLastElement(const int* begin, const int* end, funcPtr predicate) {
    if (begin == nullptr || end == nullptr || predicate == nullptr){
        return end;
    }

    if (begin >= end){
        return end;
    }

    const int* last_element = nullptr;

    while (begin < end)
    {
        if (predicate(*begin)){
            last_element = begin;
        }

        ++begin;
    }

    if (last_element == nullptr){
        return end;
    }
    
    return last_element;
}