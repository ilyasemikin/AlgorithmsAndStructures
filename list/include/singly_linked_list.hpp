#pragma once

#include <algorithm>
#include <memory>
#include <initializer_list>
#include "list.hpp"

namespace learn {
    template <typename T>
    class singly_linked_list_node {
        public:
            using pointer = std::shared_ptr<singly_linked_list_node<T>>;

            T data;
            pointer next;

            singly_linked_list_node(const T &data) :
                data(data), 
                next(nullptr)
            {

            }
    };

    // Линейный однонаправленный список
    template <typename T>
    class singly_linked_list : public list<T> {
        public:
            using pointer = typename singly_linked_list_node<T>::pointer;

            singly_linked_list() : 
                head(nullptr),
                tail(nullptr)
            {

            }

            singly_linked_list(const std::initializer_list<T> &list) :
                head(nullptr),
                tail(nullptr)
            {
                std::for_each(list.begin(), list.end(), [this](const auto &x) { push_back(x); } );
            }

            T front() const override {
                if (empty())
                    throw list_empty("invalid operation - list empty");
                return head->data;
            }

            T back() const override {
                if (empty())
                    throw list_empty("invalid operation - list empty");
                return tail->data;
            }

            void pop_front() override {
                if (empty())
                    throw list_empty("list empty");
                
                head = head->next;
                
                if (!head)
                    tail.reset();
            }

            void pop_back() override {
                if (empty())
                    throw list_empty("list empty");

                if (head == tail) {
                    head.reset();
                    tail.reset();
                }
                else {
                    pointer ptr = head;
                    while (ptr->next != tail)
                        ptr = ptr->next;
                    ptr->next = nullptr;
                    tail = ptr;
                }
            }

            void push_front(const T &item) {
                if (head) {
                    pointer new_head(new singly_linked_list_node(item));
                    new_head->next = head;
                    head = new_head;
                }
                else {
                    head.reset(new singly_linked_list_node(item));
                    tail = head;
                }
            }

            void push_back(const T &item) override {
                if (head) {
                    pointer new_tail(new singly_linked_list_node(item));
                    tail->next = new_tail;
                    tail = tail->next;
                }
                else {
                    head.reset(new singly_linked_list_node(item));
                    tail = head;
                }
            }

            void insert(size_t position, const T &item) override {
                auto count_items = count();
                if (position > count_items)
                    throw std::invalid_argument("invalid insert position");
                
                if (position == 0)
                    push_front(item);
                else if (position == count())
                    push_back(item);
                else {
                    auto ptr = head;
                    size_t index = 0;
                    while (index != position - 1) {
                        ptr = ptr->next;
                        index++;
                    }

                    pointer new_node(new singly_linked_list_node(item));

                    new_node->next = ptr->next;
                    ptr->next = new_node;
                }
            }

            T at(size_t position) const override {
                auto ptr = head;
                size_t index = 0;
                while (ptr != nullptr) {
                    if (index == position)
                        break;
                    ptr = ptr->next;
                    index++;
                }

                if (!ptr || index != position)
                    throw std::invalid_argument("icorrect position");

                return ptr->data;
            }

            size_t count() const override {
                size_t ret = 0;
                pointer ptr = head;
                while (ptr != nullptr) {
                    ptr = ptr->next;
                    ret++;
                }
                return ret;
            }
            
            bool empty() const override {
                return head == nullptr;
            } 

        protected:
            pointer head;
            pointer tail;
    };
}
