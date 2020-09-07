#pragma once

#include <memory>
#include <initializer_list>
#include <algorithm>
#include <iterator>
#include "list.hpp"

namespace learn {
    template <typename T>
    class doubly_linked_list_node {
        public:
            using pointer_t = std::shared_ptr<doubly_linked_list_node<T>>;
            
            T data;
            pointer_t next;
            pointer_t prev;

            doubly_linked_list_node(const T &data) : 
                data(data), 
                next(nullptr), 
                prev(nullptr) 
            {
                
            }
    };

    // Двусвязный список (двунаправленный связный список)
    template <typename T>
    class doubly_linked_list : public list<T> {
        public:
            doubly_linked_list() : 
                head(nullptr), tail(nullptr) 
            {

            }

            doubly_linked_list(const std::initializer_list<T> &list) :
                head(nullptr), tail(nullptr)
            {
                std::for_each(list.begin(), list.end(), [this](const auto &x) { push_back(x); } );
            }

            class iterator;
            class const_iterator;

            iterator begin() {
                return iterator(*this);
            }

            iterator end() {
                return iterator();
            }

            const_iterator begin() const {
                return const_iterator(*this);
            }

            const_iterator end() const {
                return const_iterator();
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

            void pop_front() {
                if (empty())
                    throw list_empty("invalid operation - list empty");

                if (head->next) {
                    head = head->next;
                    head->prev.reset();
                }
                else
                    head.reset();
                

                if (!head)
                    tail.reset();
            }

            void pop_back() {
                if (empty())
                    throw list_empty("invalid operation - list empty");

                if (tail->prev) {
                    tail = tail->prev;
                    tail->next.reset();
                }
                else
                    tail.reset();

                if (!tail)
                    head.reset();
            }

            void push_front(const T &item) override {
                if (head) {
                    pointer_t new_head(new doubly_linked_list_node(item));
                    new_head->next = head;
                    head->prev = new_head;
                    head = new_head;
                }
                else {
                    head.reset(new doubly_linked_list_node(item));
                    tail = head;
                }
            }

            void push_back(const T &item) override {
                if (tail) {
                    pointer_t new_tail(new doubly_linked_list_node(item));
                    new_tail->prev = tail;
                    tail->next = new_tail;
                    tail = new_tail;
                }
                else {
                    head.reset(new doubly_linked_list_node(item));
                    tail = head;
                }
            }

            void insert(size_t position, const T &item) override {
                auto count_items = count();
                if (position > count_items)
                    throw std::invalid_argument("invalid operation - incorrect position");
                
                if (!position)
                    push_front(item);
                else if (position == count_items)
                    push_back(item);
                else {
                    auto ptr = head;
                    size_t index = 0;
                    while (index != position - 1) {
                        ptr = ptr->next;
                        index++;
                    }
                    
                    pointer_t new_node(new doubly_linked_list_node(item));

                    new_node->next = ptr->next;
                    new_node->prev = ptr;
                    ptr->next->prev = new_node;
                    ptr->next = new_node;
                }
            }

            void insert(iterator it, const T &item) {
                auto ptr = it.ptr;

                if (ptr == head)
                    push_front(item);
                else if (ptr == nullptr)
                    push_back(item);
                else {
                    pointer_t new_node(new doubly_linked_list_node(item));

                    new_node->next = ptr;
                    new_node->prev = ptr->prev;
                    ptr->prev->next = new_node;
                    ptr->prev = new_node;
                }
            }

            void reverse() override {
                if (empty())
                    return;
                
                auto ptr = head;
                auto next_ptr = ptr->next;
                while (true) {
                    std::swap(ptr->prev, ptr->next);
                    ptr = next_ptr;
                    if (!ptr)
                        break;
                    next_ptr = ptr->next;
                }
                std::swap(head, tail);
            }

            iterator at(size_t index) {
                iterator ret(*this);
                
                if (index >= count())
                    throw std::invalid_argument("invalid index");
                
                for (size_t i = 0; i < index; i++)
                    ret++;

                return ret;
            }

            T get_at(size_t position) const override {
                auto ptr = head;
                size_t index = 0;
                while (ptr != nullptr) {
                    if (index == position)
                        break;
                    ptr = ptr->next;
                    index++;
                }

                if (!ptr || index != position)
                    throw std::invalid_argument("invalid operation - incorrect position");

                return ptr->data;
            }

            size_t count() const override {
                auto ptr = head;
                size_t count = 0;
                while (ptr) {
                    count++;
                    ptr = ptr->next;
                }
                return count;
            }

            bool empty() const override {
                return head == nullptr;
            }
        protected:
            using pointer_t = typename doubly_linked_list_node<T>::pointer_t;

            pointer_t head;
            pointer_t tail;
    };

    template <typename T>
    class doubly_linked_list<T>::iterator : public std::iterator<std::forward_iterator_tag, T> {
        public:
            iterator(doubly_linked_list &list) : 
                ptr(list.head)
            {

            }
            
            iterator() :
                ptr(nullptr)
            {
                
            }

            iterator operator++() {
                auto ret = *this;
                move_to_next();
                return ret;
            }

            iterator operator++(int) {
                move_to_next();
                return *this;
            }

            iterator operator--() {
                auto ret = *this;
                move_to_prev();
                return ret;
            }

            iterator operator--(int) {
                move_to_prev();
                return *this;
            }

            T& operator*() {
                return ptr->data;
            }

            T& operator->() {
                return ptr->adta;
            }

            bool operator==(const iterator &rhs) const {
                return ptr == rhs.ptr;
            }

            bool operator!=(const iterator &rhs) const {
                return ptr != rhs.ptr;
            }
        protected:
            using pointer_t = typename doubly_linked_list<T>::pointer_t;

            pointer_t ptr;

            void move_to_prev() {
                if (ptr != nullptr)
                    ptr = ptr->prev;
            }

            void move_to_next() {
                if (ptr != nullptr)
                    ptr = ptr->next;
            }

            friend class doubly_linked_list<T>;
    };

    template <typename T>
    class doubly_linked_list<T>::const_iterator : public std::iterator<std::forward_iterator_tag, T> {
        public:
            const_iterator(const doubly_linked_list &list) : 
                ptr(list.head)
            {

            }
            
            const_iterator() :
                ptr(nullptr)
            {
                
            }

            const_iterator operator++() {
                auto ret = *this;
                move_to_next();
                return ret;
            }

            iterator operator++(int) {
                move_to_next();
                return ptr;
            }

            const T& operator*() const {
                return ptr->data;
            }

            const T& operator->() const {
                return ptr->adta;
            }

            bool operator==(const const_iterator &rhs) const {
                return ptr == rhs.ptr;
            }

            bool operator!=(const const_iterator &rhs) const {
                return ptr != rhs.ptr;
            }
        protected:
            using pointer_t = typename doubly_linked_list<T>::pointer_t;

            pointer_t ptr;

            void move_to_next() {
                if (ptr != nullptr)
                    ptr = ptr->next;
            }

            friend class doubly_linked_list<T>;
    };
}