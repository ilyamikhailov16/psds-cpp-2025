#include <cstddef>

using funcPtr = double (*)(double, double);

double ApplyOperations(const double a, const double b, funcPtr* arr, size_t funcArraySize) {
    if (arr == nullptr || funcArraySize <= 0){
        return 0.0;
    }

    double cumulative_result = 0;
    for (unsigned int i=0; i < funcArraySize; ++i){
        if (arr[i] == nullptr){
            continue;
        }
        cumulative_result+=arr[i](a, b);
    }

    return cumulative_result;
}