#pragma once

#include <memory>
#include <vector>

namespace learn {
    template <typename T>
    class binary_search_tree_node {
        public:
            using node_t = std::shared_ptr<binary_search_tree_node<T>>;
            
            T value;
            node_t left;
            node_t right;
            node_t parent;

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
        public:
            using node_t = typename binary_search_tree_node<T>::node_t;

            binary_search_tree() :
                count(0), head(nullptr)
            {

            }

            void insert(const T &item) {
                insert_nrec(item);
            }

            bool empty() const {
                return head == nullptr;
            }

            size_t size() const {
                return count;
            }

            class const_iterator {
                public:
                    const_iterator(node_t _node = nullptr)
                    {
                        if (_node)
                            init(_node);
                    }

                    const_iterator operator++() {
                        auto ret = *this;
                        next();
                        return ret;
                    }

                    const_iterator operator++(int) {
                        next();
                        return *this;
                    }

                    bool operator==(const const_iterator &rhs) {
                        return node == rhs.node;
                    }

                    bool operator!=(const const_iterator &rhs) {
                        return node != rhs.node;
                    }

                    const T& operator*() {
                        return node->value;
                    }
                private:
                    node_t node;

                    void init(node_t n) {
                        while (n->left)
                            n = n->left;

                        node = n;                     
                    }

                    void next() {
                        
                    }
            };

            const_iterator begin() const {
                return const_iterator(head);
            }

            const_iterator end() const {
                return const_iterator();
            }
        private:
            size_t count;
            node_t head;

            void insert_nrec(const T &item) {
                node_t p = head;
                node_t last_p = p;
                while (p) {
                    last_p = p;
                    if (item < p->value) 
                        p = p->left;
                    else
                        p = p->right;
                }

                p = std::make_shared<binary_search_tree_node<T>>(item);
                if (!head)
                    head = p;
                else if (p->value < last_p->value)
                    last_p->left = p;
                else
                    last_p->right = p;
                
                if (p != head)
                    p->parent = last_p;

                count++;
            }
    };
}