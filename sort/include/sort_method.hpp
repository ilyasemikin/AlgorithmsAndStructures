#pragma once

#include <functional>

namespace learn {
    enum class sort_order : int {
        ascending,
        descending
    };

    // Так как C++20 еще не введен окончательно 
    // создаем самописные штука
    enum class comparsion_result : int {
        less, 
        more, 
        equal
    };

    // Сортировка пишется ориентируясь на порядок по возрастанию
    template <typename T>
    using compare_method_sign = comparsion_result (const T &, const T &);
    
    template <typename T>
    using compare_func = std::function<compare_method_sign<T>>;

    template <typename T>
    comparsion_result compare_for_ascending(const T &a, const T&b) {
        if (a < b)
            return comparsion_result::less;
        else if (a > b)
            return comparsion_result::more;
        return comparsion_result::equal;
    }

    template <typename T>
    comparsion_result compare_for_descending(const T &a, const T&b) {
        if (a > b)
            return comparsion_result::less;
        else if (a < b)
            return comparsion_result::more;
        return comparsion_result::equal;
    }
}