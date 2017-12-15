#include <iostream>
#include "DataParser.h"

using std::vector;

int main() {
    vector<WindMeasurement> allData = parseFile(R"([TU WSTAW ŚCIEŻKĘ])",
                                            1, ';');

    vector<WindMeasurement> cutData = cut(allData, stringToDate("2015-10-01 00:00"),
                                          stringToDate("2015-10-01 23:00"));

    std::cout << cutData.size() << std::endl;

    std::cout << "Dla 2015-10-01:" << std::endl;
    std::cout << "Srednia z kolumny 'sm_hour_avg': " << avg(cutData, 1) << std::endl;
    std::cout << "Max z kolumny 'sm_hour_avg': " << max(cutData, 1) << std::endl;
    std::cout << "Min z kolumny 'sm_hour_avg': " << min(cutData, 1) << std::endl;

    std::cout << std::endl;
    std::cout << "Pomiar o 08:00: ";
    for (auto &i : getByDate(cutData, stringToDate("2015-10-01 08:00")).values) {
        std::cout << i << ", ";
    }
    std::cout << std::endl;

    return 0;
}