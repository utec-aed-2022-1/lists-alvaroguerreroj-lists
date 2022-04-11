#pragma once

#include <iostream>
#include <stdexcept>

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
        this->clear();
        delete m_head;
    }

    void clear()
    {
        node* it = m_head->next;

        while (it != m_head)
        {
            node* next = it->next;
            delete it;
            it = next;
        }

        m_head->next = m_head;
        m_head->prev = m_head;

        m_size = 0;
    }

private:
    void verify_required_size(size_type n)
    {
        if (n > m_size)
        {
            throw std::runtime_error("Insufficient size");
        }
    }
};
