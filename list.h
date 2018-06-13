#ifndef LIST_MY_LIST_H
#define LIST_MY_LIST_H

#include <memory>
#include <list>
#include <cstddef>
#include <iostream>

#include "nodes.h"
#include "my_iterator.h"

template <typename T>
struct list {
    list();

    list(const list &other);

    list& operator=(const list &other);

    ~list();

    bool empty() const;

    void clear();

    void push_back(const T& value);

    T pop_back();

    T& back();

    const T& back() const;

    void push_front(const T& value);

    T pop_front();

    T& front();

    const T& front() const;

    template <typename TT>
    friend void swap(list<TT> &first, list<TT> &second);

    typedef my_iterator<T> iterator;

    typedef std::reverse_iterator<iterator> reverse_iterator;

    typedef my_iterator<const T> const_iterator;

    typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

    iterator begin() {
        return iterator(fake_node.right);
    }

    const_iterator begin() const {
        return const_iterator(fake_node.right);
    }

    reverse_iterator rbegin() {
        return reverse_iterator(end());
    }

    iterator end() {
        return iterator(&fake_node);
    }

    const_iterator end() const {
        return iterator(fake_node.right->left); // const_cast<node_without_data*>(&fake_node)
    }

    reverse_iterator rend() {
        return reverse_iterator(begin());
    }

    const_reverse_iterator rbegin() const {
        return const_reverse_iterator(end());
    }

    const_reverse_iterator rend() const {
        return const_reverse_iterator(begin());
    }

    // before pos
    iterator insert(iterator pos, T const &value) {
        node<T> *new_node = new node<T>(value, pos.cur_pos->left, pos.cur_pos);
        pos.cur_pos->left->right = new_node;
        pos.cur_pos->left = new_node;
        return iterator(new_node);
    }

    iterator erase(const_iterator pos) {
        node<T> *cur_node = static_cast<node<T>*>(pos.cur_pos);
        cur_node->left->right = cur_node->right;
        cur_node->right->left = cur_node->left;

        iterator result(cur_node->right);
        delete cur_node;
        return result;
    }

    iterator erase(const_iterator beg_pos, const_iterator end_pos) {
        while (beg_pos != end_pos) {
            erase(beg_pos++);
        }
        return iterator(end_pos.cur_pos);
    }

    void splice(const_iterator pos, list &other, const_iterator beg_pos, const_iterator end_pos) {
        if (beg_pos == end_pos)
            return;
        const_iterator end_p(end_pos);
        node_without_data *tmp = end_pos.cur_pos->left;
        beg_pos.cur_pos->left->right = end_pos.cur_pos;
        end_p.cur_pos->left->right = pos.cur_pos;
        end_pos.cur_pos->left = beg_pos.cur_pos->left;
        beg_pos.cur_pos->left = pos.cur_pos->left;

        pos.cur_pos->left->right = beg_pos.cur_pos;
        pos.cur_pos->left = tmp;
    }

private:
    node_without_data fake_node;
};

template <typename T>
list<T>::list() : fake_node() {
    fake_node.left = fake_node.right = &fake_node;
}
template <typename T>
list<T>::list(const list &other) : list() {
    for (auto i = other.begin(); i != other.end(); i++) {
        push_back(*i);
    }
}

template <typename T>
list<T>& list<T>::operator=(const list<T> &other) {
    list<T> tmp(other);
    swap(*this, tmp);
    return *this;
}

template <typename T>
list<T>::~list() {
    clear();
}

template <typename T>
void list<T>::clear() {
    while (!empty()) {
        pop_back();
    }
}

template <typename T>
bool list<T>::empty() const {
    return &fake_node == fake_node.left;
}

template <typename T>
void list<T>::push_back(const T &value) {
    node<T> *new_node = new node<T>(value, fake_node.left, &fake_node);
    fake_node.left->right = new_node;
    fake_node.left = new_node;
}

template <typename T>
T& list<T>::back() {
    return static_cast<node<T>*>(fake_node.left)->data;
}

template <typename T>
const T& list<T>::back()  const {
    return static_cast<node<T>*>(fake_node.left)->data;
}

template <typename T>
T list<T>::pop_back() {
    node<T> *cur_node = static_cast<node<T>*>(fake_node.left);
    T data(cur_node->data);
    fake_node.left = cur_node->left;
    cur_node->left->right = &fake_node;
    delete cur_node;

    return data;
}

template <typename T>
void list<T>::push_front(const T &value) {
    node<T> *new_node = new node<T>(value, &fake_node, fake_node.right);
    fake_node.right->left = new_node;
    fake_node.right = new_node;
}

template <typename T>
T& list<T>::front() {
    return static_cast<node<T> *>(fake_node.right)->data;
}

template <typename T>
const T& list<T>::front() const {
    return static_cast<node<T>*>(fake_node.right)->data;
}

template <typename T>
T list<T>::pop_front() {
    node<T> *cur_node = static_cast<node<T>*>(fake_node.right);
    T data(cur_node->data);
    fake_node.right = cur_node->right;
    cur_node->right->left = &fake_node;
    delete cur_node;

    return data;
}

template <typename TT>
void swap(list<TT> &first, list<TT> &second) {
    bool f_empty = first.empty(), s_empty = second.empty();

    node_without_data
            *f_l = first.fake_node.left,
            *f_r = first.fake_node.right,
            *s_l = second.fake_node.left,
            *s_r = second.fake_node.right;

    if (!f_empty) {
        first.fake_node.left->right = &second.fake_node;
        first.fake_node.right->left = &second.fake_node;
    }
    if (!s_empty) {
        second.fake_node.left->right = &first.fake_node;
        second.fake_node.right->left = &first.fake_node;

    }
    if (f_empty) {
        second.fake_node.left = second.fake_node.right = &second.fake_node;
    } else {
        second.fake_node.left = f_l;
        second.fake_node.right = f_r;
    }
    if (s_empty) {
        first.fake_node.left = first.fake_node.right = &first.fake_node;
    } else {
        first.fake_node.left = s_l;
        first.fake_node.right = s_r;
    }
}

#endif //LIST_MY_LIST_H
