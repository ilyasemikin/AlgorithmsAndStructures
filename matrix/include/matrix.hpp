#pragma once

#include <algorithm>
#include <ostream>
#include <stdexcept>
#include <vector>

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
                m(m), n(n), data(m * n, value) 
            {
                if (!m || !n)
                    throw std::invalid_argument("size must be non zero");
            }

            matrix(const std::initializer_list<T> &list) {
                if (!list.size())
                    throw std::invalid_argument("size must be non zero");

                m = 1;
                n = list.size();
                data.resize(m * n);

                std::copy(list.begin(), list.end(), data.begin());
            }

            matrix(const std::initializer_list<std::vector<T>> &list) {
                if (!list.size())
                    throw std::invalid_argument("count lines must be non zero");
                
                if (!list.begin()->size())
                    throw std::invalid_argument("count columns must be non zero");

                m = list.size();
                n = list.begin()->size();

                // Возможно, в дальнейшем переделаю
                for (auto line : list) {
                    if (line.size() != n)
                        throw std::invalid_argument("count items in lines must be equal");
                    // Через back_inserter - так себе идея
                    std::copy(line.begin(), line.end(), std::back_inserter(data));
                }
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
                if (i >= m || j >= n)
                    throw std::invalid_argument("invalid index");
                return data[get_index(i, j)];
            }

            inline bool is_square() const {
                return m == n;
            }

            matrix<T> transpose() const {
                matrix<T> ret(n, m);
                for (size_t i = 0; i < m; i++)
                    for (size_t j = 0; j < n; j++)
                        ret.data[ret.get_index(j, i)] = data[get_index(i, j)];
                return ret;
            }

            template <typename Tdet = T>
            Tdet determinant() const {
                if (!is_square())
                    throw std::logic_error("");

                auto mx = *this;
                for (size_t i = 0; i < m; i++) {
                    
                }

                return 0;
            }

            // Выглядит хреново, но пока сделал так, как знал
            // TODO: переделать
            // Как идея, изменить представление data
            class line {
                public:
                    line(T *first) : items(first) {
                        
                    }

                    T &operator[](size_t j) {
                        return items[j]; 
                    }
                private:
                    T *items;
            };

            class const_line {
                public:
                    const_line(const T *first) : items(first) {
                        
                    }

                    const T &operator[](size_t j) const {
                        return items[j]; 
                    }
                private:
                    const T *items;
            };

            // Не проверяет границы
            // Для индексации с проверкой использовать функцию at
            line operator[](size_t i) {
                return line(&data[i * n]);
            }

            const_line operator[](size_t i) const {
                return const_line(&data[i * n]);
            }

            template <typename Titem>
            friend bool operator==(const matrix<Titem> &, const matrix<Titem> &);
            template <typename Titem>
            friend bool operator!=(const matrix<Titem> &, const matrix<Titem> &);
            template <typename Titem>
            friend std::ostream &operator<<(std::ostream &, const matrix<Titem> &);

            friend class line;

        private:
            size_t m;
            size_t n;

            std::vector<T> data;

            inline size_t get_index(size_t i, size_t j) const {
                return i * n + j;
            }
    };
    
    template <typename Titem>
    bool operator==(const matrix<Titem> &lvl, const matrix<Titem> &rvl) {
        if (lvl.m != rvl.m || lvl.n != rvl.n)
            return false;
        auto [m, n] = rvl.get_size();
        for (size_t i = 0; i < m; i++)
            for (size_t j = 0; j < n; j++)
                if (lvl.data[i * n + j] != rvl.data[i * n + j])
                    return false;
        return true;
    }

    template <typename T>
    bool operator!=(const matrix<T> &lvl, const matrix<T> &rvl) {
        return !(lvl == rvl);
    }

    template <typename T>
    std::ostream &operator<<(std::ostream &os, const matrix<T> &mx) {
        for (size_t i = 0; i < mx.m; i++) {
            for(size_t j = 0; j < mx.n; j++)
                os << mx[i][j] << ' ';
            os << std::endl;
        }
        return os;
    }
}