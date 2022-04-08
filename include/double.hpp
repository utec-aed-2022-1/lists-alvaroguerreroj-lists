#pragma once

#include <iostream>

#include "list.hpp"

// TODO: Implement all methods
template<typename T>
class DoubleList : public List<T>
{
public:
    using typename List<T>::size_type;

private:
    using node = Node<T>;

private:
    node* head;
    node* tail;
    int nodes;

public:
    DoubleList()
        : List<T>()
    {
    }

    ~DoubleList()
    {
        // TODO
    }
};
