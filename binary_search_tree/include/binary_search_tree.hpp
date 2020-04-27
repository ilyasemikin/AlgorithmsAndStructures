#pragma once

#include <memory>

namespace learn {
    template <typename T>
    struct binary_search_tree_node {
        using node_ptr = std::shared_ptr<binary_search_tree_node<T>>;

        T value;
        node_ptr left;
        node_ptr right;
        node_ptr parent;

        binary_search_tree_node(const T &value) :
            value(value),
            left(nullptr),
            right(nullptr),
            parent(nullptr)
        {

        }
    };
    
    template <typename T>
    class binary_search_tree {
        protected:
            using node_ptr = typename binary_search_tree_node<T>::node_ptr;
        public:
            binary_search_tree() :
                count(0), head(nullptr)
            {

            }

            class iterator;

            iterator insert(const T &value) {
                node_ptr p = head;
                node_ptr last_p = p;
                while (p) {
                    last_p = p;
                    if (value < p->value) 
                        p = p->left;
                    else
                        p = p->right;
                }

                p = std::make_shared<binary_search_tree_node<T>>(value);
                if (!head)
                    head = p;
                else if (p->value < last_p->value)
                    last_p->left = p;
                else
                    last_p->right = p;
                
                if (p != head)
                    p->parent = last_p;

                count++;
                return iterator(p);
            }

            iterator find(const T& value) {
                auto node = head;
                while (node != nullptr && node->value != value)
                    if (value < node->value) 
                        node = node->left;
                    else
                        node = node->right;
                return iterator(node);
            }

            const T& min() const {
                if (!head)
                    throw;

                auto node = head;
                while (node->left)
                    node = node->left;
                return node->value;
            }

            const T& max() const {
                if (!head)
                    throw;

                auto node = head;
                while (node->right)
                    node = node->right;
                return node->value;
            }

            bool empty() const {
                return head == nullptr;
            }

            size_t size() const {
                return count;
            }

            template <typename UnaryFunction>
            void inorder_walk(UnaryFunction f) {
                inorder_walk(head, f);
            }
        protected:
            size_t count;
            node_ptr head;

            template <typename UnaryFunction>
            void inorder_walk(const node_ptr &node, const UnaryFunction &f) {
                if (node) {
                    inorder_walk(node->left, f);
                    f(node->value);
                    inorder_walk(node->right, f);
                }
            }
    };
    
    template <typename T>
    class binary_search_tree<T>::iterator {
        protected:
            using node_ptr = typename binary_search_tree_node<T>::node_ptr;
        public:
            explicit iterator(const node_ptr &_node) :
                node(_node)
            {

            }

            iterator operator++() {
                auto ret = *this;
                next();
                return ret;
            }

            iterator operator++(int) {
                next();
                return *this;
            }

            bool operator==(const iterator &rhs) {
                return node == rhs.node;
            }

            bool operator!=(const iterator &rhs) {
                return node != rhs.node;
            }

            const T& operator*() {
                return node->value;
            }
        protected:
            node_ptr node;

            void next() {
                node = nullptr;
            }

            friend class binary_search_tree<T>;
    };
}