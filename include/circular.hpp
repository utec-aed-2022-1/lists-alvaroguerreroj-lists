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
    node* m_head; // sentinel
    size_type m_size;

public:
    // TODO: Check whether `m_head` can be initialized passing `m_head` as an argument.
    CircularList()
        : m_head(new node(T())),
          m_size(0)
    {
        m_head->next = m_head;
        m_head->prev = m_head;
    }

    ~CircularList()
    {
        // TODO
    }
};
