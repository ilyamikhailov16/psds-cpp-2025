#include <vector>
#include <cmath>

struct DataStats {
    double avg = 0.0;
    double sd = 0.0;
};

DataStats CalculateDataStats(std::vector<int> numArray) {
    double average = 0.0;
    double standardDeviation = 0.0;

    if (!numArray.empty()){
        double delta = 0.0;
        double delta2 = 0.0;
        int count = 0.0;
        
        for (double num : numArray){
            ++count;
            delta = num - average;
            average += delta / count;
            delta2 = num - average;
            standardDeviation += delta * delta2;
        }
        
        standardDeviation = std::sqrt(standardDeviation / count);
    }

    DataStats datastats = {average, standardDeviation};

    return datastats;
}