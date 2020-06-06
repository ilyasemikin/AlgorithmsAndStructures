#pragma once

#include <string_view>

namespace learn::find_substr {
    const auto not_found = std::string_view::npos;
    // Алгоритм Кнута-Морриса-Прата
    size_t KMP(std::string_view string, std::string_view substr);
    // Алгоритм Бойера-Мура-Хорспула
    size_t BMH(std::string_view string, std::string_view substr);
}