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

    T front()
    {
        this->verify_required_size(1);

        return m_head->next->data;
    }

    T back()
    {
        this->verify_required_size(1);

        return m_head->prev->data;
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

    void insert(T data, node* left, node* right)
    {
        node* new_element = new node(data, right, left);
        left->next = new_element;
        right->prev = new_element;

        m_size++;
    }
};
