#pragma once

#include <stdexcept>

namespace learn {
    class list_empty : public std::logic_error {
        public:
            list_empty(const char *what) : 
                std::logic_error(what) 
            {

            }
    };

    class list_overflow : public std::logic_error {
        public:
            list_overflow(const char *what) :
                std::logic_error(what)
            {

            }
    };

    // Базовый класс для всех списков
    template <typename T>
    class list {
        public:
            virtual T front() const = 0;
            virtual T back() const = 0;

            virtual void pop_front() = 0;
            virtual void pop_back() = 0;

            virtual void push_front(const T &) = 0;
            virtual void push_back(const T &) = 0;

            virtual void insert(size_t, const T &) = 0;

            virtual T at(size_t) const = 0;

            virtual size_t count() const = 0;
            virtual bool empty() const = 0; 
    };
}
