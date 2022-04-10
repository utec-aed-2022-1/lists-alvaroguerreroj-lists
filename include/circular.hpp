#pragma once

#include <iostream>

#include "list.hpp"

// TODO: Implement all methods
template<typename T>
class CircularList : public List<T>
{
public:
    using typename List<T>::size_type;

private:
    using node = Node<T>;

private:
    node* head; // sentinel
    size_type nodes;

public:
    CircularList()
        : List<T>()
    {
    }

    ~CircularList()
    {
        // TODO
    }
};
