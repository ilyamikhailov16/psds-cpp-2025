#include <vector>
#include <type_traits> // Для std::is_same_v

template <typename Predicat>
void Filter(std::vector<int>& array, Predicat func) {
    if constexpr (!std::is_same_v<Predicat, std::nullptr_t>) {
        if (array.empty()){
            return;
        }
        
        int lagging = 0;
        for (size_t i=0; i < array.size(); ++i){
            if (func(array[i])){
                array[lagging] = array[i];
                ++lagging;
            }
        }
        array.resize(lagging);
    }
}
