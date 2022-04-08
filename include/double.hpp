#pragma once

#include <iostream>
#include <stdexcept>

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
    node* m_head;
    node* m_tail;
    size_type m_size;

public:
    DoubleList()
        : m_head(new node(T(), nullptr, nullptr)),
          m_tail(new node(T(), nullptr, m_head)),
          m_size(0)
    {
        // NOTE: Not sure if it's necessary to set `m_head->next`. When `m_head` is initialized
        // `m_tail` has not been defined yet so it may be erroneous.
        m_head->next = m_tail;
    }

    ~DoubleList()
    {
        this->clear();

        delete m_head;
        delete m_tail;
    }

    T front()
    {
        this->verify_required_size(1);

        return m_head->next->data;
    }

    T back()
    {
        this->verify_required_size(1);

        return m_tail->prev->data;
    }

    void clear()
    {
        node* it = m_head->next;

        while (it != m_tail)
        {
            node* next = it->next;
            delete it;
            it = next;
        }

        m_head->next = m_tail;
        m_tail->prev = m_head;

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
