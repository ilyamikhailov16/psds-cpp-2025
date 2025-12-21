#include <vector>

std::vector<int> Range(int from, int to, int step = 1) {
    if (step == 0) {
        return {};
    }

    if ((step > 0 && from >= to) || (step < 0 && from <= to)) {
        return {};
    }

    int count = (to - from + step - (step > 0 ? 1 : -1)) / step;
    std::vector<int> result;
    result.reserve(count);

    for (int i = 0; i < count; ++i) {
        result.push_back(from + i * step);
    }

    return result;
}
