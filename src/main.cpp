#include "skip_list.hpp"
#include <iostream>

int main() {
    stl::SkipList<int> list;

    list.insert(10);
    list.insert(5);
    list.insert(7);
    list.insert(3);

    std::cout << "Contents of SkipList: ";
    for (int val : list) {
        std::cout << val << " ";
    }
    std::cout << "\n";

    list.erase(5);

    std::cout << "After erasing 5: ";
    for (int val : list) {
        std::cout << val << " ";
    }
    std::cout << "\n";

    std::cout << "Contains 10? " << (list.contains(10) ? "Yes" : "No") << "\n";
    std::cout << "Contains 5? " << (list.contains(5) ? "Yes" : "No") << "\n";

    std::cout << "Size: " << list.size() << "\n";

    return 0;
}
