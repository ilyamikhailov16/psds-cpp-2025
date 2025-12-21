#include <vector>

std::vector<int> Unique(const std::vector<int>& input_vector) {
    if (input_vector.empty()) {
        return {};
    }
    
    std::vector<int> result;
    result.push_back(input_vector[0]);
    for (size_t i = 1; i < input_vector.size(); ++i) {
        if (input_vector[i] != input_vector[i-1]) {
            result.push_back(input_vector[i]);
        }
    }
    result.shrink_to_fit();
    return result;
}
