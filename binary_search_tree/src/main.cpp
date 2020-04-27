#include <iostream>

#include "binary_search_tree.hpp"

#include <vector>

int main() {
    learn::binary_search_tree<int> tree;

    tree.insert(45);
    tree.insert(2);
    tree.insert(5);
    tree.insert(6);
    tree.insert(10);

    auto it = tree.find(5);

    return 0;
}