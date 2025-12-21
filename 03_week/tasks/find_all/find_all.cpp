#include <vector>
#include <type_traits> // Для std::is_same_v

template <typename Predicat, typename T>
std::vector<size_t> FindAll(const std::vector<T>& array, Predicat func) {
    if constexpr (!std::is_same_v<Predicat, std::nullptr_t>) {
        if (array.empty()){
            return {};
        }

        std::vector<size_t> result;
        for (size_t i = 0; i < array.size(); ++i) {
            if (func(array[i])) {
                result.push_back(i);
            }
        }
        result.shrink_to_fit();
        return result;
    }
    
    return {};
}