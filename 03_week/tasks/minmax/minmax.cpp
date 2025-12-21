#include <vector>
#include <utility> // Для std::pair и std::make_pair

std::pair<std::vector<int>::const_iterator, std::vector<int>::const_iterator> MinMax(const std::vector<int>& vec) {
    if (vec.empty()) {
        return std::make_pair(vec.end(), vec.end());
    }

    auto min_it = vec.begin();
    auto max_it = vec.begin();

    for (auto it = vec.begin() + 1; it != vec.end(); ++it) {
        if (*it < *min_it) {
            min_it = it;
        }
        if (*it >= *max_it) {
            max_it = it;
        }
    }

    return std::make_pair(min_it, max_it);
}
