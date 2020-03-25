#pragma once

#include <algorithm>
#include <initializer_list>
#include <type_traits>
#include "stack_base.hpp"
#include "doubly_linked_list.hpp"

namespace learn {
    template <typename T, typename Tlist = doubly_linked_list<T>>
    class stack : public stack_base<T> {
        public:
            stack() {

            }

            stack(const std::initializer_list<T> init_list) {
                std::for_each(init_list.begin(), init_list.end(), [this](const auto &x) { list.push_back(x); } );
            }

            T front() const override {
                return list.front();
            }

            void push(const T &item) override {
                list.push_front(item);
            }

            T pop() override {
                auto ret = list.front();
                list.pop_front();
                return ret;
            }
                
            bool empty() const override {
                return list.empty();
            }

            size_t count() const override {
                return list.count();
            }
        private:
            Tlist list;
    };
}