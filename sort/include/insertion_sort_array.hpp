
namespace learn::sort_array {
    template <typename T, typename Compare>
    void insertion_sort(T *array, size_t size, Compare comp) {
        size_t j;
        for (size_t i = 1; i < size; i++) {
            auto key = array[i];
            j = i;
            while (j > 0 && comp(key, array[j - 1])) {
                array[j] = array[j - 1];
                j--;
            }

            array[j] = key;
        }
    }

    template <typename T>
    void insertion_sort(T *array, size_t size) {
        insertion_sort(array, size, [](const auto &x, const auto &y) { return x < y; });
    }
}