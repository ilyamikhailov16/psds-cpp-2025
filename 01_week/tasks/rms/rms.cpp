#include <cstddef>
#include <cmath>


double CalculateRMS(double values[], size_t size) {
    if (size <= 0 || values == nullptr){ return 0.0; }

    double sum = 0;
    for (int i=0; i < size; i++){
        sum+=std::pow(values[i], 2);
    }

    return std::sqrt(sum / size);
}