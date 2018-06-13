#ifndef LIST_NODES_H
#define LIST_NODES_H

struct node_without_data {
    node_without_data *left;

    node_without_data *right;

    node_without_data() : left(nullptr), right(nullptr) {}

    node_without_data(const node_without_data &other) : left(other.left), right(other.right) {}

    node_without_data(node_without_data *left, node_without_data *right) : left(left), right(right) {}

    virtual ~node_without_data() {}
};

template <typename T>
struct node : node_without_data {
    T data;

    node(const T &value, node_without_data *left, node_without_data *right): node_without_data(left, right), data(value) {}

    node(const node& other) : data(other.data), node_without_data(static_cast<node_without_data&>(other)) {}

    ~node() {}
};

#endif //LIST_NODES_H
