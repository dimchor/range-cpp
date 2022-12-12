#include <iostream>

#include "range.h"

void printRange(Range const&);

int main() {
    Range range(4);
    std::cout << range[2] << '\n';
    printRange(range);
    printRange(Range(7, 7));
    printRange(Range(-16, 7, 3));
    printRange(Range(7, -4, -2));

    // std::cout << range[5] << '\n'; // no bounds checking
    try {
        std::cout << range.at(5) << '\n'; // throws std::out_of_range!
    } catch(std::exception const& e) {
        std::cerr << e.what() << '\n';
    }
    printRange(Range(0, 5, 0)); // step should be non-zero!
    printRange(Range(0, 5, -1)); // range mustn't be infinite!
    
    return 0;
}

void printRange(Range const& range) {
    std::cout << "[ ";
    for (auto& i : range) {
        std::cout << i << ' ';
    }
    std::cout << "]\n";
}
