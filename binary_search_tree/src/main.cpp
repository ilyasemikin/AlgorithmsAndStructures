#include <iostream>

#include "binary_search_tree.hpp"

int main() {
    learn::binary_search_tree<int> tree;

    tree.insert(45);
    tree.insert(2);
    tree.insert(5);
    tree.insert(6);
    tree.insert(10);

    auto it = tree.begin();

    for (const auto &item : tree)
        std::cout << item << std::endl;

    return 0;
}