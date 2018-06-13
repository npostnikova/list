#ifndef LIST_MY_ITERATOR_H
#define LIST_MY_ITERATOR_H

#include "nodes.h"
#include <iterator>
#include <cstddef>

template <typename T>
struct list;

template <typename V>
struct my_iterator : std::iterator<std::bidirectional_iterator_tag, V, std::ptrdiff_t, V*, V&> {
    my_iterator(const my_iterator &it) : cur_pos(it.cur_pos) {}

    template <typename C, typename = typename std::enable_if<std::is_same<V, const C>::value>::type>
    my_iterator(const my_iterator<C> &data) : cur_pos(data.cur_pos) {}

    my_iterator& operator++() {
        cur_pos = cur_pos->right;
        return *this;
    }

    my_iterator operator++(int) {
        my_iterator result = *this;
        ++(*this);
        return result;
    }

    my_iterator& operator--() {
        cur_pos = cur_pos->left;
        return *this;
    }

    my_iterator operator--(int) {
        my_iterator result = *this;
        --(*this);
        return result;
    }

    template <typename Z>
    bool operator==(my_iterator<Z> const &other) const {
        return cur_pos == other.cur_pos;
    }
    template <typename Z>
    bool operator!=(my_iterator<Z> const &other) const {
        return !(*this == other);
    }

    V& operator*() const {
        return static_cast<node<V>*>(cur_pos)->data;
    }

private:
    node_without_data *cur_pos;

    explicit my_iterator(node_without_data *cur_pos) : cur_pos(cur_pos) {}

    template <typename T>
    friend struct list;

    friend struct node_without_data;

    template <typename T>
    friend struct node;

    template <typename T>
    friend struct my_iterator;
};


#endif //LIST_MY_ITERATOR_H
