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
    size_type size;

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
