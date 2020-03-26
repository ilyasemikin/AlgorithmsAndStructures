#pragma once

#include <algorithm>
#include <ostream>
#include <stdexcept>
#include <vector>

#include <iostream>

namespace learn {
    class matrix_not_exist : public std::logic_error {
        public:
            matrix_not_exist(const char *what) : 
                std::logic_error(what) 
            {
                
            }
        };

    template <typename T>
    class matrix {
        public:
            explicit matrix(size_t m, size_t n, T value = T()) : 
                m(m), n(n), data(m, std::vector<T>(n, value))
            {
                if (!m || !n)
                    throw std::invalid_argument("size must be non zero");
            }

            matrix(const std::initializer_list<T> &list) {
                if (!list.size())
                    throw std::invalid_argument("size must be non zero");

                m = 1;
                n = list.size();
                data.resize(m);
                data[0].resize(n);

                std::copy(list.begin(), list.end(), data[0].begin());
            }

            matrix(const std::initializer_list<std::vector<T>> &list) {
                if (!list.size())
                    throw std::invalid_argument("count lines must be non zero");
                
                if (!list.begin()->size())
                    throw std::invalid_argument("count columns must be non zero");

                m = list.size();
                n = list.begin()->size();

                data.resize(m);
                std::copy(list.begin(), list.end(), data.begin());
            }

            inline size_t get_m() const {
                return m; 
            }
            
            inline size_t get_n() const {
                return n;
            }

            inline std::pair<size_t, size_t> get_size() const {
                return std::pair(m, n);
            }

            T at(size_t i, size_t j) const {
                return data[i][j];
            }

            inline bool is_square() const {
                return m == n;
            }

            matrix<T> minor(size_t line, size_t column) const {
                if (m == 1 || n == 1)
                    throw matrix_not_exist("");

                matrix<T> ret(m - 1, n - 1);
                size_t ret_i, ret_j;
                ret_i = 0;

                for (size_t i = 0; i < m; i++) {
                    if (i == line)
                        continue;
                    ret_j = 0;
                    for (size_t j = 0; j < n; j++) {
                        if (j == column)
                            continue;
                        ret[ret_i][ret_j] = data[i][j];
                        ret_j++;
                    }
                    ret_i++;
                }

                return ret;
            }

            matrix<T> transpose() const {
                matrix<T> ret(n, m);
                for (size_t i = 0; i < m; i++)
                    for (size_t j = 0; j < n; j++)
                        ret.data[j][i] = data[i][j];
                return ret;
            }

            template <typename Tdet = T>
            Tdet determinant() const {
                if (!is_square())
                    throw std::logic_error("");

                if (m == 1)
                    return data[0][0];
                if (m == 2)
                    return data[0][0] * data[1][1] - data[0][1] * data[1][0];
                
                Tdet ret = Tdet();
                for (size_t j = 0; j < n; j++)
                    ret += (!(j % 2) ? 1 : -1) * data[0][j] * minor(0, j).determinant();
                return ret;
            }

            // Не проверяет границы
            // Для индексации с проверкой использовать функцию at
            std::vector<T> &operator[](size_t i) {
                return data[i];
            }

            const std::vector<T> &operator[](size_t i) const {
                return data[i];
            }
        private:
            size_t m;
            size_t n;

            // В дальнейшем подробнее изучить вопрос и рассмотреть альтернативы к предсталению матрицы
            std::vector<std::vector<T>> data;
    };
    
    template <typename Titem>
    bool operator==(const matrix<Titem> &lvl, const matrix<Titem> &rvl) {
        if (lvl.get_m() != rvl.get_m() || lvl.get_n() != rvl.get_n())
            return false;
        auto [m, n] = rvl.get_size();
        for (size_t i = 0; i < m; i++)
            for (size_t j = 0; j < n; j++)
                if (lvl[i][j] != rvl[i][j])
                    return false;
        return true;
    }

    template <typename T>
    bool operator!=(const matrix<T> &lvl, const matrix<T> &rvl) {
        return !(lvl == rvl);
    }

    template <typename T>
    std::ostream &operator<<(std::ostream &os, const matrix<T> &mx) {
        for (size_t i = 0; i < mx.get_m(); i++) {
            for(size_t j = 0; j < mx.get_n(); j++)
                os << mx[i][j] << ' ';
            os << std::endl;
        }
        return os;
    }

    // Вычисление произведения матриц по определнию
    template <typename T>
    matrix<T> math_multiplication(const matrix<T> &lvl, const matrix<T> &rvl) {
        if (lvl.get_n() == rvl.get_m())
            throw matrix_not_exist("");

        auto ret_m = lvl.get_n();
        auto ret_n = rvl.get_m();

        matrix<T> ret(ret_m, ret_n);

        T item;

        for (size_t i = 0; i < ret_m; i++)
            for (size_t j = 0; j < ret_n; j++) {
                item = 0;
                for (size_t k = 0; k < ret_m; k++) 
                    item += lvl[i, k] * rvl[k * j];
                ret[i, j] = item;
            }
        
        return ret;
    }
}