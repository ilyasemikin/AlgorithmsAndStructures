#pragma once

#include <stdexcept>
#include <string>
#include <initializer_list>

namespace learn {
    class stack_empty : public std::logic_error {
        public:
            stack_empty(const char *what) : 
                std::logic_error(what) 
            {

            }
    };

    class stack_overflow : public std::logic_error {
        public:
            stack_overflow(const char *what) : 
                std::logic_error(what) 
            {

            }
    };

    // Базовый класс стека
    template <typename T>
    class stack_base {
        public:
            virtual T front() const = 0;

            virtual void push(const T &) = 0;
            virtual T pop() = 0;
            
            virtual bool empty() const = 0;
            virtual size_t count() const = 0; 
    };
}